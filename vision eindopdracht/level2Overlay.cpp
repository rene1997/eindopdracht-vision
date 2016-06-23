#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<string>
#include <vector>
#include <utility>
#include <sstream>
#include "Camera.h"
#include "level2Overlay.h"

void initDrawing();
void stopDrawing();
void glutdrawstring(std::string str, int x, int y, void* style);

Level2Overlay::Level2Overlay(Camera * cam, std::vector<std::pair<std::string, bool>>* tasks)
{
	this->camera_ = cam;
	this->tasks = tasks;
}


Level2Overlay::~Level2Overlay()
{
}



void Level2Overlay::drawInfo() {
	//draw main info
	if (counterinfo < 60 * 5) {
		counterinfo++;
		glColor3f(1, 0, 0);
		glutdrawstring("press e to exit the vehicle", camera_->width / 2 - 40 + 200, 100, GLUT_BITMAP_TIMES_ROMAN_24);
		glutdrawstring("when walking press ^E again to get in the vehicle", camera_->width / 2 - 150 + 200, 150, GLUT_BITMAP_TIMES_ROMAN_24);
	}


	//draw task
	glColor3f(1, 1, 0);
	int y0 = 50;
	int x0 = camera_->width - 250;

	for (int i = 0; i < tasks->size(); i++) {
		glColor3f(!tasks->at(i).second, 1, 0);
		glutdrawstring(tasks->at(i).first, x0 + 400, y0, GLUT_BITMAP_TIMES_ROMAN_24);
		y0 += 50;

	}

	glColor3f(0, 0, 0);
	std::ostringstream oss;
	oss << "x: " << camera_->posX << " z: " << camera_->posZ;
	std::string string = oss.str();
	glutdrawstring(string, 0, 15, GLUT_BITMAP_HELVETICA_10);


	glColor3f(0, 0, 1);
	glutdrawstring("Level 2", camera_->width - 75 + 425, camera_->height - 10 + 260, GLUT_BITMAP_TIMES_ROMAN_24);
	 
}

void Level2Overlay::drawMenuOverLay(int overlaystate)
{
	initDrawing();

	drawHealthBar(overlaystate);
	drawInfo();


	stopDrawing();
}

void Level2Overlay::drawHealthBar(int overlaystate) {

	int margin = 25;

	int x0 = 0 + margin;
	int x1 = 50 + margin;
	int y0 = 0 + margin;
	int y1 = camera_->height - margin;

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
	float indicatorpos = ((y1 - y0) * overlaystate) / 100;

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
}

void Level2Overlay::initDrawing() {
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

void Level2Overlay::stopDrawing() {
	glColor3f(1, 1, 1);
	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void Level2Overlay::glutdrawstring(std::string str, int x, int y, void* style)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(style, str[i]);
	}
}

