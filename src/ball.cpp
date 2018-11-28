#include "ball.h"

Ball::Ball() {
}

Ball::Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius) {
	//copies parameters (not reference)
	for (int i = 0; i < 4; i++)
		this->color[i] = _color[i];

	for (int i = 0; i < 3; i++)
		this->position[i] = _position[i];

	this->radius = _radius;
}
