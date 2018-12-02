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

	//returns *this' point closest to the *obj's centre
	//REMEMBER: remember to dealocate memory (delete[])
	virtual GLfloat* getClosestPoint(Object* obj) override;

	//TODO; check Neutrino effect?
	bool checkCollision(Object* obj) override;

	//interacts with *obj. Responsible for detecting collision and calculating
	//*obj's direction vector according to *this collision behaviour
	virtual void interact(Object* obj) override;

	void draw() override;

	void setSpeed(GLfloat _speed) override;

	//Overrides operators
	void operator=(const Ball &ball);	

};

#endif
