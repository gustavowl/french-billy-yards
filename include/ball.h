#ifndef __BALL_H__
#define __BALL_H__

#include <GL/glut.h>
//#include <GL/glu.h>
#include "object.h"

class Ball : Object {

private:
	GLfloat color[4];
	GLfloat radius;

public:
	//Constructors
	Ball();
	Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius);

	void move() override;
	//TODO; check Neutrino effect?
	bool checkCollision(Object* obj) override;
};

#endif
