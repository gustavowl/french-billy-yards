/*private:
	GLfloat color[3];
	GLfloat length; //along x-axis
	GLfloat width; //along z-axis

public:
	Border();
	Border(GLfloat _color[3], GLfloat _position[3],
			GLfloat _length, GLfloat _width);

	void move() override;
	//TODO: check neutrino effect?
	bool checkCollision(Object* obj) override;
	void draw() override;

	//Overrides operators
	void operator=(const Border &border);
*/

#include "border.h"

Border::Border() {
}

Border::Border(GLfloat _color[3], GLfloat _position[3],
			GLfloat _length, GLfloat _width) {

	object(_position);
	//copies parameters (not reference)
	for (int i = 0; i < 3; i++) {
		this->color[i] = _color[i];
		this->position[i] = _position[i];
	}

	this->length = _length;
	this->width = _width;
}

void Border::move() {
}

bool Border::checkCollision(Object* obj) {
	return false;
}

void Border::draw() {

}

//Operators

void Border::operator=(const Border &border) {
	object(border.position);

	for (int i = 0; i < 3; i++) {
		this->color[i] = border.color[i];
		this->position[i] = border.position[i];
	}

	this->length = border.length;
	this->width = border.width;
}
