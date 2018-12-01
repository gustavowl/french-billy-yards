#include "cue.h"

void Cue::move() {
	GLfloat* ballPos = this->ball->getPosition();
	for (int i = 0; i < 3; i++)
		this->position[i] = ballPos[i];
	delete[] ballPos;
}

//TODO: check neutrino effect?
bool Cue::checkCollision(Object* obj) {
	return false;
}

void Cue:: draw() {
	if (this->visible) {
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, this->color);

		//TODO: calculate rotation vector (along y-axis)
		glTranslatef(this->position[0], ball->getRadius(), this->position[2]);
		glRotatef(this->angle, 0, 1, 0);
		glTranslatef(0, 0, ball->getRadius() + this->force);

		gluCylinder(this->qobj, this->baseRadius, this->topRadius, this->height,
				this->slices, this->stacks);

		glPopMatrix();
	}
}

void Cue::setDirection(GLfloat _angle) {
	//angle 0 = [0, -1]
	//angle 90 = [-1, 0]
	//angle 180 = [0, 1]
	//angle 270 = [1, 0]
	this->direction[0] = - sin(_angle * PI / 180.0);
	this->direction[2] = - cos(_angle * PI / 180.0);
}

//constructors and destructors
Cue::Cue(GLfloat _color[3], GLfloat _baseRadius, GLfloat _topRadius, GLfloat _height,
		GLfloat _slices, GLfloat _stacks, Ball* _ball) {
	object();

	for (int i = 0; i < 3; i++)
		this->color[i] = _color[i];

	this->qobj = gluNewQuadric();
	gluQuadricNormals(this->qobj, GLU_SMOOTH);
	this->baseRadius = _baseRadius;
	this->topRadius = _topRadius;
	this->height = _height;
	this->slices = _slices;
	this->stacks = _stacks;

	this->ball = _ball;
	this->move();
	this->setAngle(0.f);

	GLfloat* ballPos = this->ball->getPosition();
	for (int i = 0; i < 3; i++)
		this->target[i] = ballPos[i] + this->direction[i];
	delete[] ballPos;

	visible = true;
	force = 0.f;

}

Cue::~Cue() {
	gluDeleteQuadric(this->qobj);
}	

//gets and set
void Cue::setForce(GLfloat _force) {
	this->force = _force;
}
GLfloat Cue::getForce() {
	return this->force;
}

void Cue::setVisible(bool _visible) {
	if (_visible && this->ball->getSpeed() == 0.f)
		this->visible = true;
	else
		this->visible = false;
}

bool Cue::getVisible() {
	return this->visible;
}

void Cue::setAngle(GLfloat _angle) {
	//TODO: calculate target or direction (WATCH OUT: avoid recursion)
	while (_angle >= 360)
		_angle -= 360;
	while (_angle < 0)
		_angle += 360;

	this->angle = _angle;
	this->setDirection(_angle);
}

GLfloat Cue::getAngle() {
	return this->angle;
}

void Cue::setTarget(GLfloat _target[3]) {
	//TODO: calculate angle (WATCH OUT: avoid recursion)
	for (int i = 0; i < 3; i++)
		this->target[i] = _target[i];
}
//moves cue ball and cue stick disappears
void Cue::shoot() {
	//TODO: calculate lots of stuff
	//TODO: calculate mass and acceleration
	//TODO: calculate shot direction
	if (this->visible) {
		this->ball->setDirection(this->direction);
		this->ball->setSpeed(this->force);
		this->visible = false;
	}
}

//Overrides operators
void Cue::operator=(const Cue &cue) {
	for (int i = 0; i < 3; i++)
		this->color[i] = cue.color[i];

	//supposes =operator is overriden by glut
	this->qobj = cue.qobj; 

	this->baseRadius = cue.baseRadius;
	this->topRadius = cue.topRadius;
	this->height = cue.height;
	this->slices = cue.slices;
	this->stacks = cue.stacks;

	//copies cue ball.
	//would it be better to copy the reference to the ball?
	this->ball = cue.ball; 

	this->angle = cue.angle;
	for (int i = 0; i < 3; i++) {
		this->direction[i] = cue.direction[i];
		this->target[i] = cue.target[i];
	}

	this->visible = cue.visible;
	this->force = cue.force;
}
