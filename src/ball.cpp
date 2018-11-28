#include "ball.h"

Ball::Ball() {
	GLfloat p[3] = {2112, 2, 3};
	object(p);
}

Ball::Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius) {
	object(_position);
	//copies parameters (not reference)
	for (int i = 0; i < 4; i++)
		this->color[i] = _color[i];

	for (int i = 0; i < 3; i++)
		this->position[i] = _position[i];

	this->radius = _radius;
}

void Ball::move() {
}

bool Ball::checkCollision(Object* obj) {
	return false;
}
