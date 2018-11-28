#ifndef __BALL_H__
#define __BALL_H__

#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

class Ball {

private:
	GLfloat color[4];
	GLfloat position[3];
	GLfloat radius;
	GLfloat speed;
	GLfloat direction;

public:
	Ball();
	Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius);


};

#endif
