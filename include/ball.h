#ifndef __BALL_H__
#define __BALL_H__

#include <GL/glut.h>
#include "object.h"

class Ball : public Object {

private:
	GLfloat color[3];
	GLfloat radius;
	GLint linesOfLongitude;
	GLint linesOfLatitude;

	GLfloat friction; //speed decrease: speed -= friction

public:
	//Constructors
	Ball();
	Ball(GLfloat _color[3], GLfloat _position[3], GLfloat _radius);
	Ball(GLfloat _color[3], GLfloat _position[3], GLfloat _radius,
			GLint _longitude, GLint _latitude, GLfloat _friction);

	//sets and gets
	void setRadius(GLfloat _radius);
	GLfloat getRadius();

	void move() override;
	//TODO; check Neutrino effect?
	bool checkCollision(Object* obj) override;

	void draw() override;

	//Overrides operators
	void operator=(const Ball &ball);	

};

#endif
