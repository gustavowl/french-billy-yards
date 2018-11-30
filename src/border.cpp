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

bool Border::checkCollision(Object* obj) {
	return false;
}

void Border::draw() {

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
