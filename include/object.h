#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <GL/glut.h>
#include <GL/glu.h>

class Object {
protected:
	GLfloat position[3];
	GLfloat speed;
	GLfloat direction[3];

	void object();
	void object(const GLfloat _position[3]);
	void object(const GLfloat _position[3], const GLfloat _speed,
			const GLfloat _direction[3]);

public:
	virtual void move() = 0;
	//TODO: check Neutrino effect?
	virtual bool checkCollision(Object* obj) = 0;

	virtual void draw() = 0;

	GLfloat* getPosition(); //REMEMBER: remember to dealoacte memory (delete[])
	GLfloat getSpeed();
	void setSpeed(GLfloat _speed);
	GLfloat* getDirection(); //REMEMBER: remember to dealoacte memory (delete[])
	void setDirection(GLfloat _direction[3]);


};

#endif
