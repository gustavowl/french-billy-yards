#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>

class Object {
protected:
	GLfloat position[3];
	GLfloat speed;
	GLfloat direction[3];
	GLfloat collisionRadius;

	void object();
	void object(const GLfloat _position[3]);
	void object(const GLfloat _position[3], const GLfloat _speed,
			const GLfloat _direction[3]);

public:
	virtual void move() = 0;

	//returns *this' point closest to the *obj's centre
	//REMEMBER: remember to dealocate memory (delete[])
	virtual GLfloat* getClosestPoint(Object* obj) = 0;

	//TODO: check Neutrino effect?
	virtual bool checkCollision(Object* obj) = 0;

	//interacts with *obj. Responsible for detecting collision and calculating
	//*obj's direction vector according to *this collision behaviour
	virtual void interact(Object* obj) = 0;

	virtual void draw() = 0;

	GLfloat* getPosition(); //REMEMBER: remember to dealoacte memory (delete[])
	GLfloat getSpeed();
	void setSpeed(GLfloat _speed);
	GLfloat* getDirection(); //REMEMBER: remember to dealoacte memory (delete[])
	void setDirection(GLfloat _direction[3]);
	//void setCollisionRadius(GLfloat _radius);
	GLfloat getCollisionRadius();
};

#endif
