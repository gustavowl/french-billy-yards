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
		//calculates collision vector (angle)
		//collisionVec simulates sine and cosine
		//(EASTER EGG: sine, sine, cosine, sine, 3.14159)
		GLfloat* objPos = obj->getPosition();
		//direction of obj will be changed, therefore
		//collision vector is OBJ - THIS
		GLfloat* collisionVec = this->calculateVector(this->position, objPos);
		this->normalizeVector(collisionVec);
		delete[] objPos;

		GLfloat* objDir = obj->getDirection();
		//sums direction vectors
		GLfloat dirSum[3] = {0.f, 0.f, 0.f};
		for (int i = 0; i < 3; i++)
			dirSum[i] = this->direction[i] + objDir[i];

		printf("\tBEFORE COLLISION\n");
		for (int i = 0; i < 3; i++) {
			printf("this[%d] = %f | ", i, this->direction[i]);
		}
		printf("speed = %f\n", this->getSpeed());
		//printf("\n");
		for (int i = 0; i < 3; i++)
			printf("obj[%d] = %f | ", i, objDir[i]);
		printf("speed = %f\n", obj->getSpeed());

		//changes object's speed depending on collision angle
		GLfloat objSpeed = obj->getSpeed();
		GLfloat theta = acos( this->innerProduct(collisionVec, dirSum) /
			( sqrt(this->innerProduct(collisionVec, collisionVec) *
			 this->innerProduct(dirSum, dirSum)) ) );
		/*GLfloat theta = acos( this->innerProduct(collisionVec, collisionVec) /
			( this->innerProduct(collisionVec, collisionVec) ));*/
		if (theta > PI/2)
			theta = PI - theta;
		obj->setSpeed(pow(sin(theta),2) * objSpeed + pow(cos(theta),2) * this->speed);
		printf("----------------------------%f-----------------------------\n", theta * 180.0 / PI);
		printf("----------------------------%f-----------------------------\n", obj->getSpeed());

		//changes this' speed depending on collision angle
		this->setSpeed(pow(sin(theta),2) * this->speed + pow(cos(theta),2) * objSpeed);

		//copies objDir before changing it for future calculations
		GLfloat copyObjDir[3];
		for (int i = 0; i < 3; i++)
			copyObjDir[i] = objDir[i];

		//change object's direction
		for (int i = 0; i < 3; i ++)
			//objDir[i] += collisionVec[i];
			objDir[i] += cos(theta) * (-objDir[i]) + cos(theta) * this->direction[i];
		this->normalizeVector(objDir);
		obj->setDirection(objDir);

		//change this direction
		for (int i = 0; i < 3; i++)
			this->direction[i] = cos(theta) * (-this->direction[i]) + cos(theta) * copyObjDir[i];
		this->normalizeVector(this->direction);

		//TODO: DELETE ME - RESET
		//this->position[0] = this->position[2] = 0;
		//this->position[1] = -2;
		printf("\tAFTER COLLISION\n");
		for (int i = 0; i < 3; i++) {
			printf("this[%d] = %f | ", i, this->direction[i]);
		}
		printf("speed = %f\n", this->getSpeed());
		for (int i = 0; i < 3; i++)
			printf("obj[%d] = %f | ", i, objDir[i]);
		printf("speed = %f\n", obj->getSpeed());
		for (int i = 0; i < 3; i++)
			printf("collisionVec[%d] = %f | ", i, collisionVec[i]);
		printf("\n");
		for (int i = 0; i < 3; i++)
			printf("dirSum[%d] = %f | ", i, dirSum[i]);
		printf("\n==========================\n\n");
		
		delete[] collisionVec;
		delete[] objDir;
	}
}

void Ball::draw() {
	glPushMatrix();
	//glCullFace(GL_BACK);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, this->color);
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glutSolidSphere(this->radius, this->linesOfLongitude, this->linesOfLongitude);
	
	glPopMatrix();

	if (this->speed != 0.f) {
		std::cout << "ite<" << this;
		printf(">: %d\n", ++(this->ite));
	}
}

void Ball::setSpeed(GLfloat _speed) {
	//printf("BALL SET SPEED\n");
	if (_speed < 0.f)
		_speed = 0.f;

	if (_speed == 0.f) {
		for (int i = 0; i < 3; i++)
			this->direction[i] = 0.f;
		this->ite = 0;
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
