#include "ball.h"
#include <stdio.h>

Ball::Ball() {
	GLfloat c[3] = {1, 1, 1};
	GLfloat p[3] = {0, 0, 0};
	*this = Ball(c, p, 1);
}

Ball::Ball(GLfloat _color[3], GLfloat _position[3], GLfloat _radius) {
	*this = Ball(_color, _position, _radius, 100, 100);
}

Ball::Ball(GLfloat _color[3], GLfloat _position[3], GLfloat _radius,
		GLint _longitude, GLint _latitude) {

	object(_position);
	//copies parameters (not reference)
	for (int i = 0; i < 3; i++) {
		this->color[i] = _color[i];
		this->position[i] = _position[i];
	}

	this->radius = _radius;
	this->linesOfLongitude = _longitude;
	this->linesOfLatitude = _latitude;
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
	if (this->speed != 0) {
		for (int i = 0; i < 3; i++) {
			this->position[i] += this->direction[i] * this->speed;
		}
	}
}

bool Ball::checkCollision(Object* obj) {
	return false;
}

void Ball::draw() {
	this->move();

	glPushMatrix();

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
	
}
