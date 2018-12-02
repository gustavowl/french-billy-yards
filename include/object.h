#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

#ifndef PI
	#define PI 3.1415926535897932
#endif


class Object {
protected:
	GLfloat position[3];
	GLfloat speed;
	GLfloat direction[3];
	GLfloat collisionRadius;
	int ite = 0; //TODO: DELETE ME

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

	GLfloat* getPosition(); //REMEMBER: remember to dealocate memory (delete[])
	GLfloat getSpeed();
	void setSpeed(GLfloat _speed);
	GLfloat* getDirection(); //REMEMBER: remember to dealocate memory (delete[])
	void setDirection(GLfloat _direction[3]);
	//void setCollisionRadius(GLfloat _radius);
	GLfloat getCollisionRadius();

	//TODO: should be in a separated file
	//self implemented naive linear algebra functions
	GLfloat innerProduct(GLfloat vectora[3], GLfloat vectorb[3]);
	//REMEMBER: remember to dealocate memory (delete[])
	//pointb - pointa
	GLfloat* calculateVector(GLfloat pointa[3], GLfloat pointb[3]);
	void normalizeVector(GLfloat vec[3]);
};

#endif
