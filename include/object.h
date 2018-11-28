#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <GL/glut.h>
#include <GL/glu.h>

class Object {
protected:
	GLfloat position[3];
	GLfloat speed;
	GLfloat direction;

public:
	virtual void move() = 0;
	//TODO: check Neutrino effect?
	virtual bool checkCollision(Object* obj) = 0;
};

#endif
