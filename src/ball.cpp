#include "ball.h"
#include <stdio.h>

Ball::Ball() {
	GLfloat c[3] = {1, 1, 1};
	GLfloat p[3] = {0, 0, 0};
	*this = Ball(c, p, 1);
}

Ball::Ball(GLfloat _color[3], GLfloat _position[3], GLfloat _radius) {
	*this = Ball(_color, _position, _radius, 100, 100, 0.001);
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
	if (this->speed > 0) {
		for (int i = 0; i < 3; i++) {
			this->position[i] += this->direction[i] * this->speed;
		}
		this->speed -= this->friction;
		if (this->speed < 0)
			this-> speed = 0;
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

		//change object's direction
		GLfloat* objDir = obj->getDirection();
		for (int i = 0; i < 3; i ++)
			objDir[i] += collisionVec[i];
		obj->setDirection(objDir);

		//changes object's speed
		obj->setSpeed(obj->getSpeed() + this->speed);

		//TODO: DELETE ME - RESET
		this->position[0] = this->position[2] = 0;
		for (int i = 0; i < 3; i++) {
			printf("this[%d] = %f | ", i, this->direction[i]);
			this->speed = 0;
		}
		printf("\n");
		for (int i = 0; i < 3; i++)
			printf("obj[%d] = %f | ", i, objDir[i]);
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
