#include "object.h"

void Object::object() {
	GLfloat p[3] = {0, 0, 0};
	object(p);
}

void Object::object(const GLfloat _position[3]) {
	GLfloat s = 0;
	GLfloat d[3] = {0, 0, 0};
	object(_position, s, d);
}

void Object::object(const GLfloat _position[3], const GLfloat _speed,
		const GLfloat _direction[3]) {

	for (int i = 0; i < 3; i++) {
		this->position[i] = _position[i];
	}

	this->speed = _speed;

	for (int i = 0; i < 3; i++) {
		this->direction[i] = _direction[i];
	}
}

GLfloat* Object::getPosition() {
	GLfloat* p = new GLfloat[3];
	for (int i = 0; i < 3; i++)
		p[i] = this->position[i];
	return p;
}

GLfloat Object::getSpeed() {
	return this->speed;
}

void Object::setSpeed(GLfloat _speed) {
	this->speed = _speed;
}

GLfloat* Object::getDirection() {
	GLfloat* d = new GLfloat[3];
	for (int i = 0; i < 3; i++)
		d[i] = this->direction[i];
	return d;
}

void Object::setDirection(GLfloat _direction[3]) {
	for (int i = 0; i < 3; i++)
		this->direction[i] = _direction[i];
}
