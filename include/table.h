#ifndef __TABLE_H__
#define __TABLE_H__

#include <GL/glut.h>
#include "object.h"
#include "border.h"
#include "texture.h"
class Table : public Object {
private:
	GLfloat color[3];
	GLfloat length; //along x-axis
	GLfloat width; //along z-axis
	Border borders[4];
	Texture tex;

public:
	Table();
	Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness);
	Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness,
			GLfloat _length, GLfloat _width);

	void move() override;

	//returns *this' point closest to the *obj's centre
	//REMEMBER: remember to dealocate memory (delete[])
	virtual GLfloat* getClosestPoint(Object* obj) override;

	//TODO; check Neutrino effect?
	bool checkCollision(Object* obj) override;

	//interacts with *obj. Responsible for detecting collision and calculating
	//*obj's direction vector according to *this collision behaviour
	virtual void interact(Object* obj) override;

	//TODO draw texture
	void draw() override;

	//overrides operator
	void operator=(const Table &table);
};

#endif
