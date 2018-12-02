#include "border.h"

Border::Border() {
	GLfloat c[3] = {0, 0, 0};
	GLfloat p[3] = {0, 0, 0};
	*this = Border(c, p, 1, 1, 1);
}

Border::Border(GLfloat _color[3], GLfloat _position[3], GLfloat _length,
		GLfloat _height, GLfloat _width) {

	object(_position);
	//copies parameters (not reference)
	for (int i = 0; i < 3; i++) {
		this->color[i] = _color[i];
		this->position[i] = _position[i];
	}

	this->length = _length;
	this->height = _height;
	this->width = _width;
}

void Border::move() {
}

GLfloat* Border::getClosestPoint(Object* obj) {
	//x-axis: left(-) to right(+). z-axis: top(-) to bottom(+)
	GLfloat* ret = new GLfloat[3];

	GLfloat* objPos = obj->getPosition();

	ret[1] = this->position[1];
	RelativePosition rel = this->getRelativePosition(objPos);
	switch (rel) {
		case RelativePosition::NORTH:
			ret[0] = objPos[0];
			ret[2] = this->position[2] - this->width / 2;
			break;
		case RelativePosition::SOUTH:
			ret[0] = objPos[0];
			ret[2] = this->position[2] + this->width / 2;
			break;
		case RelativePosition::EAST:
			ret[0] = this->position[0] + this->length / 2;
			ret[2] = objPos[2];
			break;
		case RelativePosition::WEST:
			ret[0] = this->position[0] - this->length / 2;
			ret[2] = objPos[2];
			break;
		default: //INVALID
			delete[] ret;
			delete[] objPos;
			return NULL;
	}

	delete[] objPos;
	return ret;
}

bool Border::checkCollision(Object* obj) {
	bool ret = false;
	GLfloat* closestPoint = this->getClosestPoint(obj);

	if (closestPoint != NULL) {
		GLfloat* objPos = obj->getPosition();
		RelativePosition rel = this->getRelativePosition(objPos);

		switch (rel) {
			case RelativePosition::NORTH:
				if (closestPoint[2] <= objPos[2] + obj->getCollisionRadius())
					ret = true;
				break;
			case RelativePosition::SOUTH:
				if (closestPoint[2] >= objPos[2] - obj->getCollisionRadius())
					ret = true;
				break;
			case RelativePosition::EAST:
				if (closestPoint[0] >= objPos[0] - obj->getCollisionRadius())
					ret = true;
				break;
			case RelativePosition::WEST:
				if (closestPoint[0] <= objPos[0] + obj->getCollisionRadius())
					ret = true;
				break;
			default: //INVALID
				break;
		}

		delete[] objPos;
		delete[] closestPoint;
	}

	return ret;
}

void Border::interact(Object *obj) {
	if (this->checkCollision(obj)) {
		GLfloat* objPos = obj->getPosition();
		RelativePosition rel = this->getRelativePosition(objPos);
		delete[] objPos;

		//change obj's direction
		GLfloat* objDir = obj->getDirection();

		//mirros z-axis
		if (rel == RelativePosition::NORTH && objDir[2] > 0.f)
			objDir[2] *= -1;

		//mirros z-axis
		else if	(rel == RelativePosition::SOUTH && objDir[2] < 0.f)
			objDir[2] *= -1;

		//mirros x-axis
		else if (rel == RelativePosition::EAST && objDir[0] < 0.f)
			objDir[0] *= -1;
		
		else if (rel == RelativePosition::WEST && objDir[0] > 0.f)
			objDir[0] *= -1;

		obj->setDirection(objDir);

		delete[] objDir;

	}
}

//priority: north, east, south, west
Border::RelativePosition Border::getRelativePosition(GLfloat _position[3]) {
	//x-axis: left(-) to right(+). z-axis: top(-) to bottom(+)
	if (_position[2] <= this->position[2] - this->width/2)
		return RelativePosition::NORTH;

	if (_position[0] >= this->position[0] + this->length/2)
		return RelativePosition::EAST;

	if (_position[2] >= this->position[2] + this->width/2)
		return RelativePosition::SOUTH;

	if (_position[0] <= this->position[0] - this->length/2)
		return RelativePosition::WEST;

	return RelativePosition::INVALID;
}

void Border::setSpeed(GLfloat _speed) {
	printf("BORDER SET SPEED\n");
	if (_speed <= 0.f) {
		this->ite = 0;
		_speed = 0.f;
	}
	this->speed = _speed;
}

void Border::draw() {
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->color);
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	glScalef(this->length, this->height, this->width);
	glutSolidCube(1);
	glPopMatrix();
}

//Operators

void Border::operator=(const Border &border) {
	object(border.position);

	for (int i = 0; i < 3; i++) {
		this->color[i] = border.color[i];
		this->position[i] = border.position[i];
	}

	this->length = border.length;
	this->height = border.height;
	this->width = border.width;
}
