#include "MenuState.h"
#include "Camera.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//int crosshairX, crosshairY;

void MenuState::Init(GameStateManager * game, Camera * cam, KeyHandler * hand)
{
	this->manager = game;
	this->camera = cam;
	this->key_handler = hand;
	this->player_ = new Player(key_handler, camera, this);

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
	player_->update();
}






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


	//extinguisher_->draw();
	//DrawCrosshair(camera->width/2,camera->height/2);
}

void MenuState::preDraw()
{
	//extinguisher_->draw();
	player_->getItem()->draw();
}

void MenuState::checkMovementCollission()
{


}
