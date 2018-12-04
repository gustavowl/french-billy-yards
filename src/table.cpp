#include "table.h"
static void
drawBox(GLfloat size)
{
	GLenum type = GL_QUADS;
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
	if(i!=1){
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
  }
}

Table::Table() {
	GLfloat c[3] = {0, 1, 0};
	GLfloat p[3] = {0, 0, 0,};
	*this = Table(c, p, 1);
}


Table::Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness) {
	*this = Table(_color, _position, _borderThickness, 10.0, 5.0);
}

Table::Table(GLfloat _color[3], GLfloat _position[3], GLfloat _borderThickness,
		GLfloat _length, GLfloat _width) {

	object(_position);

	for (int i = 0; i < 3; i++) {
		this->color[i] = _color[i];
		this->position[i] = _position[i];
	}

	this->length = _length;
	this->width = _width;

	GLfloat borderPos[4][3] = {
		0, _borderThickness/2, -(this->width + _borderThickness) / 2, //top
		0, _borderThickness/2, (this->width + _borderThickness) / 2, //bottom
		(this->length + _borderThickness) / 2, _borderThickness/2, 0, //right
		-(this->length + _borderThickness) / 2, _borderThickness/2, 0 //left
	};

	GLfloat borderDim[4][3] = {
		this->length + _borderThickness*2, _borderThickness, _borderThickness, //top
		this->length + _borderThickness*2, _borderThickness, _borderThickness, //bottom
		_borderThickness, _borderThickness, this->width, //right
		_borderThickness, _borderThickness, this->width //left
	};

	for (int i = 0; i < 4; i++) {
		Border b = Border(_color, borderPos[i], borderDim[i][0],
				borderDim[i][1], borderDim[i][2]);
		this->borders[i] = b;
	}
}

void Table::move() {
}

GLfloat* Table::getClosestPoint(Object* obj) {
	GLfloat* g = new GLfloat(5.f);
	return g;
}

bool Table::checkCollision(Object* obj) {
	return false;
}

void Table::interact(Object *obj) {
	for (int i = 0; i < 4; i++)
		this->borders[i].interact(obj);
}

void Table::setSpeed(GLfloat _speed) {
	printf("TABLE SETSPEED\n");
	if (_speed <= 0.f) {
		this->ite = 0.f;
		_speed = 0.f;
	}
	this->speed = _speed;
}

void Table::draw() {

	//draw plane
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->color);
	glScalef(this->length, 0.2, this->width);
	glTranslatef(0, -0.5, 0);
	drawBox(1);
	glPopMatrix();
	
	//draw borders
	for (int i = 0; i < 4; i++) 
		this->borders[i].draw();

}

void Table::operator=(const Table &table) {
	object(table.position);

	for (int i = 0; i < 3; i++) {
		this->color[i] = table.color[i];
		this->position[i] = table.position[i];
	}

	this->length = table.length;
	this->width = table.width;

	for (int i = 0; i < 4; i++)
		this->borders[i] = table.borders[i];
}
