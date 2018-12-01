/*class Table : public Object {
	//TODO: add texture
private:
	GLfloat color[3];
	GLfloat length; //along x-axis
	GLfloat width; //along z-axis
	Border borders[4];

};
*/

#include "table.h"

Table::Table() {
	GLfloat c[3] = {0, 1, 0};
	GLfloat p[3] = {0, 0, 0,};
	*this = Table(c, p, 1);
}


Table::Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness) {
	*this = Table(_color, _position, _borderThickness, 10.0, 5.0);
}

Table::Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness,
		GLfloat _length, GLfloat _width) {

	object(_position);

	for (int i = 0; i < 3; i++) {
		this->color[i] = _color[i];
		this->position[i] = _position[i];
	}

	this->length = _length;
	this->width = _width;

	GLfloat borderPos[4][3] = {
		0, _borderThickness/2, -(this->width + _borderThickness) / 2, //top
		0, _borderThickness/2, (this->width + _borderThickness) / 2, //bottom
		(this->length + _borderThickness) / 2, _borderThickness/2, 0, //right
		-(this->length + _borderThickness) / 2, _borderThickness/2, 0 //left
	};

	GLfloat borderDim[4][3] = {
		this->length + _borderThickness*2, _borderThickness, _borderThickness, //top
		this->length + _borderThickness*2, _borderThickness, _borderThickness, //bottom
		_borderThickness, _borderThickness, this->width, //right
		_borderThickness, _borderThickness, this->width //left
	};

	for (int i = 0; i < 4; i++) {
		Border b = Border(_color, borderPos[i], borderDim[i][0],
				borderDim[i][1], borderDim[i][2]);
		this->borders[i] = b;
	}
}

void Table::move() {
}

GLfloat* Table::getClosestPoint(Object* obj) {
	GLfloat* g = new GLfloat(5.f);
	return g;
}

bool Table::checkCollision(Object* obj) {
	return false;
}

void Table::interact(Object *obj) {
	printf("======================================\n");
	for (int i = 0; i < 4; i++) {
		//DELETE ME
		//DELETE STDIO from object.h
		printf("-----Border %d-----\n", i);
		this->borders[i].interact(obj);
	}
	printf("======================================\n\n");
}

void Table::draw() {
	//draw plane
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->color);
	glScalef(this->length, 0.2, this->width);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(1);
	glPopMatrix();
	
	//draw borders
	for (int i = 0; i < 4; i++) 
		this->borders[i].draw();

}

void Table::operator=(const Table &table) {
	object(table.position);

	for (int i = 0; i < 3; i++) {
		this->color[i] = table.color[i];
		this->position[i] = table.position[i];
	}

	this->length = table.length;
	this->width = table.width;

	for (int i = 0; i < 4; i++)
		this->borders[i] = table.borders[i];
}
