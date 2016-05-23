#include "MenuState.h"
#include "Camera.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//int crosshairX, crosshairY;

void MenuState::Init(GameStateManager * game, Camera * cam, KeyHandler * hand)
{
	this->manager = game;
	this->camera = cam;
	this->key_handler = hand;
	extinguisher_ = new Extinguisher(hand);

}

void MenuState::Cleanup()
{
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::HandleEvents()
{

}

void MenuState::Update()
{
	//DrawCrosshair(camera->width/2,camera->height/2);
}

//void MenuState::DrawCrosshair(int x, int y){
//
//	glPushMatrix();
//	glTranslatef((float)3, 0.0f, (float)3);
//	glPointSize(10);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glBegin(GL_POINTS);
//	glVertex2f(crosshairX, crosshairY);
//	glEnd();
//	glPopMatrix();
//}

void MenuState::Draw()
{
	glPushMatrix();
	glTranslatef((float)3, 0.0f, (float)3);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);

	glColor3f(1, 1, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);

	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);

	glColor3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	glColor3f(0, 1, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();
	glPopMatrix();



	//DrawCrosshair(camera->width/2,camera->height/2);
}

void MenuState::preDraw()
{
	extinguisher_->draw();

}
