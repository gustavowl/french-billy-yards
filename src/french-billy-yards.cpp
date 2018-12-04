#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "object.h"
#include "ball.h"
#include "table.h"
#include "cue.h"
#include "texture.h"
#include <vector>

#ifndef PI
	#define PI 3.1415926535897932
#endif
//#define BALL_RADIUS 0.2165492957746479
#define BALL_RADIUS 0.217
#define CM 0.035 //centimeters

#define TABLEWIDTH 5
#define TABLELENGTH 10

double camera_eye[3] = {0, 8, 1};
double radius = 5.5;
int angle_xz = 0, angle_y = 0;

GLfloat colorWhite[3] = {1, 1, 1};
GLfloat colorRed[3] = {1, 0, 0};
GLfloat colorYellow[3] = {1, 1, 0};
GLfloat colorTable[4] = {0, 0.1, 0, 1};
GLfloat colorCue[3] = {0.4, 0.2, 0.0};

GLfloat posicaoLuz[4]={0.0, 5.0, 3.0, 1.0};
GLfloat diff[4] = {1, 1, 1, 1};
GLfloat ambient[4] = {0, 0, 0.01, 1};

/*GLfloat posWhite[3] = {0, BALL_RADIUS, 0};
GLfloat posRed[3] = {1.5, BALL_RADIUS, 1};
GLfloat posYellow[3] = {-1.5, BALL_RADIUS, -1};*/
GLfloat posWhite[3] = {1.774145, BALL_RADIUS, 0.659731};
GLfloat posRed[3] = {-4.555485, BALL_RADIUS, 0.802723};
GLfloat posYellow[3] = {-2.471037, BALL_RADIUS, -1.997582};
GLfloat posTable[3] = {0, 0, 0};

Ball whiteBall(colorWhite, posWhite, BALL_RADIUS),
	 redBall(colorRed, posRed, BALL_RADIUS),
	 yellowBall(colorYellow, posYellow, BALL_RADIUS);

Table table(colorTable, posTable, BALL_RADIUS*2, TABLELENGTH, TABLEWIDTH);

Cue cue(colorCue, 0.021, 0.042, 5.35, 50, 20, &whiteBall);
//Cue cue(colorCue, 0.021, 0.042, 5.35, 50, 20, &yellowBall);

bool ballsMoving = false; //draws cue only if all balss stopped moving

std::vector<Object*> objs = {&table, &whiteBall, &redBall,
	&yellowBall, &cue};

//https://freestocktextures.com/texture/liquid-orange-marbled-pattern,1012.html
Texture tex;

float randomf() {
	return ((float)rand())/RAND_MAX;
}

double degress_to_rad(int degrees) {
	return degrees * PI / 180.0;
}
void inicializacao() {
	//LIGHTING 
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	//TEXTURE
	tex.setFileName("imgs/photos_2017_11_3_fst_moss-texture.ppm");

	//cor de fundo eh cinza
	glClearColor(0.8, 0.8, 0.8, 0.0);

	glMatrixMode(GL_PROJECTION);
	//alterne e altere as projecoes para alcancar os resultados desejados
	glFrustum(-1, 1, -1, 1, 1.5, 20.0);

	//back-facing culling
	glEnable(GL_CULL_FACE);

	//alters cue force TODO: dynamically
	cue.setForce(0.25); //max
	//cue.setForce(0.05); //min
	cue.setAngle(53);
}

void moveObjects() {
	//computes collisions
	for (unsigned int i = 0; i < objs.size(); i++) {
		
		if (objs[i] == &cue)
			continue; //cue is not interacting with any object.
			//TODO: check collision during shot animation

		for (unsigned int j = i + 1; j < objs.size(); j++) {
			if (objs[j] == &cue || objs[j] == &table) 
				continue; //table and cue do not move

			//i will change j direction if collision happened
			objs[i]->interact(objs[j]);
		}
	}

	//Moves objects
	ballsMoving = false;

	for (unsigned int i = 0; i < objs.size(); i++) {
		objs[i]->move();
		if (!ballsMoving && objs[i]->getSpeed() != 0)
			ballsMoving = true;
	}

	cue.setVisible(!ballsMoving);
}

void drawObjects() {
	//TEXTURE 
	glPushAttrib(GL_LIGHTING_BIT);
		GLfloat teste[3]={1,1,1};
		tex.activeTex();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,teste);
		
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glPushMatrix();
			glScalef(5,0,2.8);
			glBegin(GL_QUADS);
			
			glTexCoord2f(0,1);glVertex3f(-1, 0.1, 1);
			glTexCoord2f(1,1);glVertex3f( 1, 0.1, 1);
			glTexCoord2f(1,0);glVertex3f( 1, 0.1, -1);
			glTexCoord2f(0,0);glVertex3f(-1, 0.1, -1);
			glEnd();
		glPopMatrix();
		glBindTexture( GL_TEXTURE_2D, 0 );
	glPopAttrib();
	for (unsigned int i = 0; i < objs.size(); i++) {
			glPushAttrib(GL_LIGHTING_BIT);
			objs[i]->draw();
			glPopAttrib();
	}
}

void funcaoDisplay() {
	//limpa a tela com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camera_eye[0], camera_eye[1], camera_eye[2],
		0, 0, 0, 0, 1, 0);

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, posicaoLuz);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	moveObjects();
	drawObjects();

	glFlush();
	glutSwapBuffers();
	//printf("\t\tLOOP\t\t\n");
}

void funcaoKeyboard(unsigned char key, int x, int y) {
	if(key == 'q' || key == 'Q')
		exit(-1);

	//go left and right
	else if(key == 'D')
		camera_eye[0] += 0.1;
	else if(key == 'A')
		camera_eye[0] -= 0.1;

	//go up and down
	else if(key == 'W')
		camera_eye[1] += 0.1;
	else if(key == 'S')
		camera_eye[1] -= 0.1;

	//go back and forward
	else if(key == 'K')
		camera_eye[2] += 0.1;
	else if(key == 'I')
		camera_eye[2] -= 0.1;

	//cue controls
	else if (cue.getVisible()) {
		if (key == ' ') {
			cue.shoot();
			printf("Shot angle: %f\n", cue.getAngle());
			printf("White ball = ");
			GLfloat* pos = whiteBall.getPosition();
			for (int i = 0; i < 3; i++)
				printf("[%d]: %f | ", i, pos[i]);
			delete[] pos;
			printf("\n");
			printf("Red ball = ");
			pos = redBall.getPosition();
			for (int i = 0; i < 3; i++)
				printf("[%d]: %f | ", i, pos[i]);
			delete[] pos;
			printf("\n");
			printf("Yellow ball = ");
			pos = yellowBall.getPosition();
			for (int i = 0; i < 3; i++)
				printf("[%d]: %f | ", i, pos[i]);
			delete[] pos;
			printf("\n\n");

		}
		else if (key == 'a' || key == 's')
			cue.setAngle(cue.getAngle() - 1); //rotate clockwise
		else if (key == 'd' || key == 'w')
			cue.setAngle(cue.getAngle() + 1); //rotate anti-clockwise
		else //no valid action
			return;
	}

	else //cue invisible
		return;

	glutPostRedisplay();
}

int t = 0;

void temporizador() {
	t++;
	//if (t == 2112) {
	if (t == 2112 * 15) {
	//if (t == 2112 * 500) {
		glutPostRedisplay();
		t = 0;
	}
}

int main(int argc, char **argv) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("French Billy-yards");
	glutKeyboardFunc(funcaoKeyboard);
	glutDisplayFunc(funcaoDisplay);
	glutIdleFunc(temporizador);
	inicializacao();

	glutMainLoop();

	return 0;
}
