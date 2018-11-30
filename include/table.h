#ifndef __TABLE_H__
#define __TABLE_H__

#include <GL/glut.h>
#include "object.h"
#include "table-border.h"

class Table : public Object {
	//TODO: add texture
private:
	GLfloat color[3];
	GLfloat length; //along x-axis
	GLfloat width; //along z-axis
	Border borders[4];
};

#endif
