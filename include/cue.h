#ifndef __CUE_H_
#define __CUE_H_

#ifndef PI
	#define PI 3.1415926535897932
#endif

#include <GL/glut.h>
#include "object.h"
#include "ball.h"
#include <math.h>

class Cue : public Object {
private:
	//TODO: cue stick has no "lids"
	//TODO: add texture
	GLfloat color[3];

	//determine cylinder format
	GLUquadric* qobj;
	GLfloat baseRadius; //radius at z=0
	GLfloat topRadius; //radius at z=height
	GLfloat height;
	GLfloat slices; //subdvisions around z axis (alter circle smoothness)
	GLfloat stacks; //subdvision along z axis (along height)

	//determine cylinder position
	Ball* ball; //cue ball
	GLfloat target[3]; //target point
	GLfloat angle;

	bool visible; //set to false while balls are moving
	GLfloat force; //force to be applied to cue ball

public:
	//overrides virtual methods
	void move() override;
	bool checkCollision(Object* obj) override; //TODO: check neutrino effect?
	void draw() override;

	void setDirection(GLfloat _angle);

	//constructors and destructors
	Cue(GLfloat _color[3], GLfloat _baseRadius, GLfloat _topRadius, GLfloat _height,
			GLfloat _slices, GLfloat _stacks, Ball* _ball);
	~Cue(); //destroy quadric object

	//gets and set
	void setForce(GLfloat _force);
	GLfloat getForce();
	void setVisible(bool _visible);
	bool getVisible();
	void setAngle(GLfloat _angle);
	GLfloat getAngle();
	void setTarget(GLfloat _target[3]);
	//getTarget not implemented

	//moves cue ball and cue stick disappears
	void shoot();

	//overrides operators
	void operator=(const Cue &cue);

	//TODO: verify table borders to not pass through them
};

#endif
