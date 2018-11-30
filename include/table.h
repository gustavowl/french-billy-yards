#ifndef __TABLE_H__
#define __TABLE_H__

#include <GL/glut.h>
#include "object.h"
#include "border.h"

class Table : public Object {
	//TODO: add texture
private:
	GLfloat color[3];
	GLfloat length; //along x-axis
	GLfloat width; //along z-axis
	Border borders[4];

public:
	Table();
	Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness);
	Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness,
			GLfloat _length, GLfloat _width);

	void move() override;
	bool checkCollision(Object* obj);
	void draw() override;

	//overrides operator
	void operator=(const Table &table);

};

#endif
