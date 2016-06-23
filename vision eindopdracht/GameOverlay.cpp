#include "GameOverlay.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<string>
#include <vector>
#include <utility>
#include <sstream>
#include "Camera.h"


GameOverlay::GameOverlay(Camera * cam)
{
	this->camera_ = cam;
}


GameOverlay::~GameOverlay()
{
}

void initDrawing() {
	//Ortho:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1920, 1080, 0, -10, 10);

	//disable light, depth and textures:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void stopDrawing() {
	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void glutdrawstring(std::string str, int x, int y, void* style)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(style, str[i]);
	}
}


void drawGameOverLay(Camera * camera) {
	initDrawing();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, (GLfloat)0.55);
	
	//drawBackground:
	glBegin(GL_QUADS);
	glVertex2f((GLfloat)camera->width/2 - 300, 20);
	glVertex2f((GLfloat)camera->width / 2 - 300, 340);
	glVertex2f((GLfloat)camera->width / 2 + 300, 340);
	glVertex2f((GLfloat)camera->width / 2 + 300, 20);
	glEnd();


	glColor3f(0, 1, 0);
	glutdrawstring("game finished", camera->width / 2 - 75, 150, GLUT_BITMAP_TIMES_ROMAN_24);
	glutdrawstring("press esc to exit", camera->width / 2 - 85, 200, GLUT_BITMAP_TIMES_ROMAN_24);
	stopDrawing();
}
