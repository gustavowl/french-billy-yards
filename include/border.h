#ifndef __BORDER_H__
#define __BORDER_H__

#include <GL/glut.h>
#include "object.h"

class Border : public Object {
	//TODO: add texture
private:
	GLfloat color[3];
	GLfloat length; //along x-axis
	GLfloat height; //along y-axis
	GLfloat width; //along z-axis

	enum class RelativePosition {NORTH, EAST, SOUTH, WEST, INVALID};

	//priority order: North, East, South, West, Invalid
	RelativePosition getRelativePosition(GLfloat _position[3]);

public:
	Border();
	Border(GLfloat _color[3], GLfloat _position[3],	GLfloat _length,
			GLfloat _height, GLfloat _width);

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

	//Overrides operators
	void operator=(const Border &border);
};

#endif
