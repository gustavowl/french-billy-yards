#include "ball.h"

Ball::Ball() {
	GLfloat c[4] = {1, 1, 1, 1};
	GLfloat p[3] = {0, 0, 0};
	*this = Ball(c, p, 1);
}

Ball::Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius) {
	*this = Ball(_color, _position, _radius, 100, 100);
}

Ball::Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius,
		GLint _longitude, GLint _latitude) {

	object(_position);
	//copies parameters (not reference)
	for (int i = 0; i < 4; i++)
		this->color[i] = _color[i];

	for (int i = 0; i < 3; i++)
		this->position[i] = _position[i];

	this->radius = _radius;
	this->linesOfLongitude = _longitude;
	this->linesOfLatitude = _latitude;
}

void Ball::move() {
}

bool Ball::checkCollision(Object* obj) {
	return false;
}

void Ball::draw() {
	glPushMatrix();

	//float g[4] = {0.1, 0.1, 0.1, 1};
	//glMaterialfv(GL_FRONT, GL_SPECULAR, g);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->color);
	glColor4fv(this->color);
	//glColorMaterial(GL_FRONT, GL_SPECULAR);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, this->color);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, g);
	//float ambient[4] = {0, 0, 0, 1};
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glutSolidSphere(this->radius, this->linesOfLongitude, this->linesOfLongitude);
	
	glPopMatrix();
}


//Operators

void Ball::operator=(const Ball &ball) {
	object(ball.position);

	for (int i = 0; i < 4; i++)
		this->color[i] = ball.color[i];
	
	for (int i = 0; i < 3; i++)
		this->position[i] = ball.position[i];

	this->radius = ball.radius;
	this->linesOfLongitude = ball.linesOfLongitude;
	this->linesOfLatitude = ball.linesOfLatitude;
	
}
