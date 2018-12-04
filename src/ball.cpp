#include "ball.h"

Ball::Ball() {
	GLfloat c[3] = {1, 1, 1};
	GLfloat p[3] = {0, 0, 0};
	*this = Ball(c, p, 1);
}

Ball::Ball(GLfloat _color[3], GLfloat _position[3], GLfloat _radius) {
	*this = Ball(_color, _position, _radius, 100, 100, 0.00075);
}

Ball::Ball(GLfloat _color[3], GLfloat _position[3], GLfloat _radius,
		GLint _longitude, GLint _latitude, GLfloat _friction) {

	object(_position);
	//copies parameters (not reference)
	for (int i = 0; i < 3; i++) {
		this->color[i] = _color[i];
		this->position[i] = _position[i];
	}

	this->radius = _radius;
	this->collisionRadius = _radius;
	this->linesOfLongitude = _longitude;
	this->linesOfLatitude = _latitude;
	this->friction = _friction;
}

//gets and sets
void Ball::setRadius(GLfloat _radius) {
	if (_radius > 0)
		this->radius = _radius;
}

GLfloat Ball::getRadius() {
	return this->radius;
}

void Ball::move() {
	//TODO: floating-point error
	if (this->speed > 0.f) {
		for (int i = 0; i < 3; i++) {
			this->position[i] += this->direction[i] * this->speed;
		}

		this->setSpeed(this->speed - friction);
	}
}

GLfloat* Ball::getClosestPoint(Object* obj) {
	GLfloat* objPos = obj->getPosition();

	GLfloat* ret = this->calculateVector(this->position, objPos);
	this->normalizeVector(ret);
	
	//calculates closest surface point
	for (int i = 0; i < 3; i++)
		ret[i] = this->position[i] + this->radius * ret[i];

	delete[] objPos;
	return ret;
}

bool Ball::checkCollision(Object* obj) {
	GLfloat* objClosest = obj->getClosestPoint(this);
	GLfloat* distVec = this->calculateVector(this->position, objClosest);
	GLfloat distance = sqrt(this->innerProduct(distVec, distVec));
	delete[] distVec;
	delete[] objClosest;
	return distance < this->collisionRadius;
}

void Ball::interact(Object *obj) {
	if (this->checkCollision(obj)) {
		GLfloat* objDir = obj->getDirection();

		//backtracks collision (to remove overlaping), i.e. time regression
		GLfloat* objPos = obj->getPosition();
		GLfloat* thisPos = this->getPosition();
		GLfloat objSpeed = obj->getSpeed();
		for (int i = 0; i < 3; i++) {
			objPos[i] -= objDir[i] * objSpeed;
			thisPos[i] -= this->direction[i] * this->speed;
		}
		//objPos and thisPos are now in the point equivalent to previous iteration
		//calculates previous distance.
		GLfloat* previousVec = this->calculateVector(objPos, thisPos);
		GLfloat dist = sqrt(this->innerProduct(previousVec, previousVec));
		dist = dist - this->collisionRadius - obj->getCollisionRadius(); //gap before collision
		delete[] previousVec;
		GLfloat delta = 0.f; //distance variation: from time0 to time1
		for (int i = 0; i < 3; i++)
			delta += pow(objDir[i] * objSpeed - this->direction[i] * this->speed, 2);
		delta = sqrt(delta); //diagonal variation
		GLfloat time = dist / delta;
		for (int i = 0; i < 3; i++) {
			objPos[i] += objDir[i] * objSpeed * time;
			thisPos[i] += this->direction[i] * this->speed * time; 
		}		

		//calculates collision vector (angle)
		//collisionVec simulates sine and cosine
		//(EASTER EGG: sine, sine, cosine, sine, 3.14159)
		GLfloat* collisionObj = this->getCollisionVector(obj, this);
		GLfloat* collisionThis = this->getCollisionVector(this, obj);
		GLfloat thetaObj = this->getCollisionAngle(objDir, collisionObj);
		GLfloat thetaThis = this->getCollisionAngle(this->direction, collisionThis);

		//changes object's speed depending on collision angle
		//obj->setSpeed(pow(sin(thetaObj),2) * objSpeed + pow(cos(thetaThis),2) * this->speed);
		obj->setSpeed(objSpeed + cos(thetaThis) * this->speed - cos(thetaObj) * objSpeed );

		//changes this' speed depending on collision angle
		//this->setSpeed(pow(sin(thetaThis),2) * this->speed + pow(cos(thetaObj),2) * objSpeed);
		this->setSpeed(this->speed + cos(thetaObj) * objSpeed - cos(thetaThis) * this->speed);

		//copies objDir before changing it for future calculations
		GLfloat copyObjDir[3];
		for (int i = 0; i < 3; i++)
			copyObjDir[i] = objDir[i];

		//changes object's direction
		for (int i = 0; i < 3; i ++)
			//objDir[i] += collisionVec[i];
			objDir[i] += cos(thetaObj) * (- collisionObj[i]) + cos(thetaThis) * this->direction[i];
		this->normalizeVector(objDir);
		obj->setDirection(objDir);

		//changes this direction
		for (int i = 0; i < 3; i++)
			this->direction[i] += cos(thetaThis) * (- collisionThis[i]) +
				cos(thetaObj) * copyObjDir[i];
		this->normalizeVector(this->direction);

		//continues movement simulation. (time regression)
		for (int i = 0; i < 3; i++) {
			objPos[i] += objDir[i] * obj->getSpeed() * (1.f - time);
			thisPos[i] += this->direction[i] * this->getSpeed() * (1.f - time);
		}

		this->setPosition(thisPos);
		obj->setPosition(objPos);
		delete[] objPos;
		delete[] thisPos;
		delete[] collisionObj;
		delete[] collisionThis;
		delete[] objDir;
	}
}

GLfloat Ball::getCollisionAngle(GLfloat* veca, GLfloat* vecb) {
	GLfloat theta = 0.f;
	GLfloat norma = this->innerProduct(veca, veca);
	GLfloat normb = this->innerProduct(vecb, vecb);

	if (norma != 0.f && normb != 0.f ) {
		//collisionVec and dir are unitary
		theta = acos(this->innerProduct(veca, vecb));
		/*if (theta > PI/2)
			theta = PI - theta;*/
	}

	return theta;
}

GLfloat* Ball::getCollisionVector(Object* obja, Object* objb) {
	//objb - obja
	GLfloat* posa = obja->getPosition();
	GLfloat* posb = objb->getPosition();

	GLfloat* collisionVec = this->calculateVector(posa, posb);
	this->normalizeVector(collisionVec);

	delete[] posa;
	delete[] posb;

	return collisionVec;
}

void Ball::draw() {
	glPushMatrix();
	//glCullFace(GL_BACK);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, this->color);
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glutSolidSphere(this->radius, this->linesOfLongitude, this->linesOfLongitude);
	
	glPopMatrix();
}

void Ball::setSpeed(GLfloat _speed) {
	if (_speed < 0.f)
		_speed = 0.f;

	if (_speed == 0.f) {
		for (int i = 0; i < 3; i++)
			this->direction[i] = 0.f;
	}

	this->speed = _speed;
}

//Operators

void Ball::operator=(const Ball &ball) {
	object(ball.position);
	
	for (int i = 0; i < 3; i++) {
		this->color[i] = ball.color[i];
		this->position[i] = ball.position[i];
	}

	this->radius = ball.radius;
	this->linesOfLongitude = ball.linesOfLongitude;
	this->linesOfLatitude = ball.linesOfLatitude;
	this->friction = ball.friction;
	this->collisionRadius = ball.collisionRadius;
	
}
