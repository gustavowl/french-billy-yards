#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "ball.h"
#include "table.h"
#include "cue.h"

#define PI 3.1415926535897932
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

GLfloat posicaoLuz[4]={0.0, 0.0, 50.0, 1.0};

GLfloat posWhite[3] = {0, BALL_RADIUS, 0};
GLfloat posRed[3] = {1, BALL_RADIUS, 1.5};
GLfloat posYellow[3] = {-1.5, BALL_RADIUS, -1};
GLfloat posTable[3] = {0, 0, 0};

Ball whiteBall(colorWhite, posWhite, BALL_RADIUS),
	 redBall(colorRed, posRed, BALL_RADIUS),
	 yellowBall(colorYellow, posYellow, BALL_RADIUS);

Table table(colorTable, posTable, BALL_RADIUS*2, TABLELENGTH, TABLEWIDTH);

Cue cue(colorCue, 0.021, 0.042, 5.35, 50, 20, &whiteBall);

//https://freestocktextures.com/texture/liquid-orange-marbled-pattern,1012.html
unsigned char* data;
int width, height;
GLuint* tex_v;


void loadPPM(char *filename) {
    FILE *arq = fopen(filename, "r");
    char format[3];
    int max;
    fscanf(arq, "%s %d %d %d\n", format, &width, &height, &max);
    data = (unsigned char *) malloc(sizeof(unsigned char)*width*height*3);
    fread(data, sizeof(unsigned char), width*height*3, arq);
    fclose(arq);
}

float randomf() {
	return ((float)rand())/RAND_MAX;
}

double degress_to_rad(int degrees) {
	return degrees * PI / 180.0;
}
void inicializacao() {
	//TODO
	GLfloat diffspec[4] = {1, 1, 1, 1};
	GLfloat ambient[4] = {0, 0, 0, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffspec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, diffspec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE);
	glShadeModel(GL_SMOOTH);

	//cor de fundo eh cinza
	glClearColor(0.8, 0.8, 0.8, 0.0);

	glMatrixMode(GL_PROJECTION);
	//alterne e altere as projecoes para alcancar os resultados desejados
	glFrustum(-1, 1, -1, 1, 1.5, 20.0);

	//alters cue force TODO: dynamically
	cue.setForce(0.25);
}

void funcaoDisplay() {
	//limpa a tela com a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camera_eye[0], camera_eye[1], camera_eye[2],
		0, 0, 0, 0, 1, 0);
	
	table.draw();
	whiteBall.draw();
	redBall.draw();
	yellowBall.draw();
	cue.draw();

	glFlush();
	glutSwapBuffers();
}

void funcaoKeyboard(unsigned char key, int x, int y) {

	if(key == 'q')
		exit(-1);

	//go left and right
	if(key == 'd')
		camera_eye[0] += 0.1;
	if(key == 'a')
		camera_eye[0] -= 0.1;

	//go up and down
	if(key == 'w')
		camera_eye[1] += 0.1;
	if(key == 's')
		camera_eye[1] -= 0.1;

	//go back and forward
	if(key == 'k')
		camera_eye[2] += 0.1;
	if(key == 'i')
		camera_eye[2] -= 0.1;

	//cue controls
	if (key == ' ')
		cue.shoot();


	glutPostRedisplay();
}

int t = 0;

void temporizador() {
	t++;
	if (t == 2112 * 73) {
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
