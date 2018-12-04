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
	RelativePosition rel = this->getRelativePosition(obj);
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
	GLfloat* objPos = obj->getPosition();
	GLfloat radius = obj->getCollisionRadius();
	bool ret = (objPos[0] - radius < this->position[0] + this->length/2) &&
		(objPos[0] + radius > this->position[0] - this->length/2) &&
		(objPos[2] + radius > this->position[2] - this->width/2) &&
		(objPos[2] - radius < this->position[2] + this->width/2);
	delete[] objPos;
	return ret;
}

void Border::interact(Object *obj) {
	if (this->checkCollision(obj)) {
		//backtracks obj (ball). DELOREAN TIME!
		GLfloat* objPos = obj->getPosition();
		GLfloat* objDir = obj->getDirection();
		GLfloat objSpeed = obj->getSpeed();
		for (int i = 0; i < 3; i++)
			objPos[i] -= objDir[i] * objSpeed;
		//object is now at previous iteration.
		//calculate collision position.
		GLfloat time = 0.f;
		RelativePosition rel = getRelativePosition(obj);
		if (rel == RelativePosition::NORTH || rel == RelativePosition::SOUTH) {
			//z-axis
			GLfloat delta = abs(objPos[2] - this->position[2]) -
				obj->getCollisionRadius() - this->width/2;
			time = delta / abs(objDir[2] * objSpeed);
		}
		else if (rel != RelativePosition::INVALID) {
			//x-axis: EAST or WEST
			GLfloat delta = abs(objPos[0] - this->position[0]) -
				obj->getCollisionRadius() - this->length/2;
			time = delta / abs(objDir[0] * objSpeed);
		}
		else {
			//TODO: exception
		}
		
		for (int i = 0; i < 3; i++)
			objPos[i] += objDir[i] * objSpeed * time;

		if (rel == RelativePosition::NORTH || rel == RelativePosition::SOUTH)
			objDir[2] *= -1;
		else if (rel != RelativePosition::INVALID)
			objDir[0] *= -1;
		else {
			//TODO: exception
		}

		for (int i = 0; i < 3; i++)
			objPos[i] += objDir[i] * objSpeed * (1.f - time);

		obj->setPosition(objPos);
		obj->setDirection(objDir);

		delete[] objPos;
		delete[] objDir;
	}
}

//priority: north, east, south, west
Border::RelativePosition Border::getRelativePosition(Object *obj) {
	//x-axis: left(-) to right(+). z-axis: top(-) to bottom(+)
	GLfloat* objPos = obj->getPosition();
	GLfloat colRadius = obj->getCollisionRadius();

	if (objPos[2] - colRadius <= this->position[2] - this->width/2 &&
			objPos[0] - colRadius <= this->position[0] + this->length/2 &&
			objPos[0] + colRadius >= this->position[0] - this->length/2 ) {
		delete[] objPos;
		return RelativePosition::NORTH;
	}

	if (objPos[0] + colRadius >= this->position[0] + this->length/2 &&
			objPos[2] + colRadius >= this->position[2] - this->width/2 &&
			objPos[2] - colRadius <= this->position[2] + this->width/2) {
		delete[] objPos;
		return RelativePosition::EAST;
	}

	if (objPos[2] + colRadius >= this->position[2] + this->width/2 &&
			objPos[0] - colRadius <= this->position[0] + this->length/2 &&
			objPos[0] + colRadius >= this->position[0] - this->length/2 ) {
		delete[] objPos;
		return RelativePosition::SOUTH;
	}

	if (objPos[0] - colRadius <= this->position[0] - this->length/2 &&
			objPos[0] - colRadius <= this->position[0] + this->length/2 &&
			objPos[0] + colRadius >= this->position[0] - this->length/2 ) {
		delete[] objPos;
		return RelativePosition::WEST;
	}

	delete[] objPos;
	return RelativePosition::INVALID;
}

void Border::setSpeed(GLfloat _speed) {
	if (_speed <= 0.f) {
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
