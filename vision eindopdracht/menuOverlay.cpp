#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<string>
#include <vector>
#include <utility>

#include "Camera.h"
#include "menuOverlay.h"

menuOverlay::menuOverlay(Camera * cam, std::vector<std::pair<std::string, bool>>* tasks)
{
	this->camera_ = cam;
	this->tasks = tasks;
}


menuOverlay::~menuOverlay()
{
}



void menuOverlay::drawInfo() {
	//draw walk info
	int x0 = camera_->width / 2 - (28*7);
	int y0 = 100;
	glColor3f(0, 0, 0.8);
	glutdrawstring("Use W,A,S,D for walking walk", x0, y0, GLUT_BITMAP_TIMES_ROMAN_24);

	//draw look info
	y0 += 50;
	x0 = camera_->width / 2 - (28 * 7);
	glutdrawstring("Use the mouse to look around", x0, y0, GLUT_BITMAP_TIMES_ROMAN_24);

	//draw task

	glColor3f(1, 1, 0);
	y0 = 50;
	x0 = camera_->width - 250;
	
	for (int i = 0; i < tasks->size(); i++) {
		glColor3f(!tasks->at(i).second, 1, 0);
		glutdrawstring(tasks->at(i).first, x0, y0, GLUT_BITMAP_TIMES_ROMAN_24);
		y0 += 50;

	}
	




}

void menuOverlay::drawMenuOverLay(int overlaystate)
{
	initDrawing();

	drawHealthBar(overlaystate);
	drawInfo();
		

	stopDrawing();
}

void menuOverlay::drawHealthBar(int overlaystate) {

	int margin = 25;

	int x0 = 0 + margin;
	int x1 = 50 + margin;
	int y0 = 0 + margin;
	int y1 = camera_->height -margin;

	//xpbarbackground:
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(x1, y0);
	glVertex2f(x0, y0);

	glColor3f(0, 1, 0);
	glVertex2f(x0, y1);
	glVertex2f(x1, y1);
	glEnd();

	//drawindicator:
	float indicatorpos = ((y1 - y0) * overlaystate) / 250;

	int indicatorx0 = x0 - 10;
	int indicatory0 = camera_->height - indicatorpos - margin;
	int indicatorx1 = x1 + 10;
	int indicatory1 = indicatory0 + 10;

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(indicatorx1, indicatory0);
	glVertex2f(indicatorx0, indicatory0);
	glVertex2f(indicatorx0, indicatory1);
	glVertex2f(indicatorx1, indicatory1);
	glEnd();

	glColor3f(0, 0, 0.8);
	glutdrawstring("<- fire indicator", indicatorx1 + 10, indicatory0 + 10, GLUT_BITMAP_TIMES_ROMAN_24);
	


	
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
	//glEnable(GL_LIGHTING);
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