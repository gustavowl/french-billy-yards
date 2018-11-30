#ifndef __BORDER_H__
#define __BORDER_H__

#include <GL/glut.h>
#include "object.h"

class Border : public Object {
	//TODO: add texture
private:
	GLfloat color[3];
	GLfloat length; //along x-axis
	GLfloat width; //along z-axis

public:
	Border();
	Border(GLfloat _color[3], GLfloat _position[3],
			GLfloat _length, GLfloat _width);

	void move() override;
	//TODO: check neutrino effect?
	bool checkCollision(Object* obj) override;
	void draw() override;

	//Overrides operators
	void operator=(const Border &border);
};

#endif
