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
	void object(GLfloat _position[3]);
	void object(GLfloat _position[3], GLfloat _speed, GLfloat _direction[3]);

public:
	virtual void move() = 0;
	//TODO: check Neutrino effect?
	virtual bool checkCollision(Object* obj) = 0;

	//REMEMBER: remember to dealoacte memory (delete[])
	GLfloat* getPosition();

};

#endif
