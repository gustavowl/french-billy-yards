#ifndef __BALL_H__
#define __BALL_H__

#include <GL/glut.h>
//#include <GL/glu.h>
#include "object.h"

class Ball : public Object {

private:
	GLfloat color[4];
	GLfloat radius;
	GLint linesOfLongitude;
	GLint linesOfLatitude;

public:
	//Constructors
	Ball();
	Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius);
	Ball(GLfloat _color[4], GLfloat _position[3], GLfloat _radius,
			GLint _longitude, GLint _latitude);

	void move() override;
	//TODO; check Neutrino effect?
	bool checkCollision(Object* obj) override;

	void draw() override;

	//Overrides operators
	void operator=(const Ball &ball);	

};

#endif
