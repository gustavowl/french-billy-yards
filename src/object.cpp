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
	this->collisionRadius = 0.f;

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

GLfloat Object::getCollisionRadius() {
	return this->collisionRadius;
}

GLfloat Object::innerProduct(GLfloat vectora[3], GLfloat vectorb[3]) {
	GLfloat ip = 0.f;
	for (int i = 0; i < 3; i++)
		ip += vectora[i] * vectorb[i];
	return ip;
}

GLfloat* Object::calculateVector(GLfloat pointa[3], GLfloat pointb[3]) {
	GLfloat* ret = new GLfloat[3];
	for (int i = 0; i < 3; i++)
		ret[i] = pointb[i] - pointa[i];
	return ret;
}

void Object::normalizeVector(GLfloat vec[3]) {
	GLfloat norm = sqrt(this->innerProduct(vec, vec));
	for (int i = 0; i < 3; i++)
		vec[i] /= norm;
}
