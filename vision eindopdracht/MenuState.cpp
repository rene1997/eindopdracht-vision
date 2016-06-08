#include "MenuState.h"
#include "Camera.h"
#include "menuOverlay.h"

#include <utility>
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
	
	tasks = new vector<pair<std::string, bool>>;
	tasks->push_back(pair<std::string, bool>("1) Walk to the cube!", false));

	this->overlay_ = new menuOverlay(camera, tasks);
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


	//task one
	//if xpos player = correct
	if (camera->posX >= -12 && camera->posX <= -10) {
		//if zpos player = correct
		if (camera->posZ <= -14 && camera->posZ >= -16 && !tasks->at(0).second)  {
			tasks->push_back(pair<std::string, bool>("2) Click to extinguish", false));
			tasks->at(0).second = true;
		}
	}

	//task 2:
	if (tasks->at(0).second) {
		if (camera->posX >= -12 && camera->posX <= -10 && camera->posZ <= -14 && camera->posZ >= -16) {
			if (key_handler->keys['l'] && fire > 0) {
				fire--;

			}
			else if (fire == 0) {

				tasks->at(1).second = true;
			}
		}
		
	}


	bool done = true;
	for (int i = 0; i < tasks->size(); i++) {
		if ((!tasks->at(i).second) || (tasks->size() < 2)) {
			done = false;
		}
	}

	if(done){
		manager->nextState();
	}




}



void MenuState::DrawGround() {

	glColor3f(0, 0.5, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-50, 0, -50);
	glVertex3f(50, 0, -50);
	glVertex3f(50, 0, 50);
	glVertex3f(-50, 0, 50);
	glEnd();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void MenuState::DrawOverLay()
{

}


void MenuState::Draw()
{
	DrawGround();

	//Task one:
	drawCube(10, 12, 14, 16);
	

	overlay_->drawMenuOverLay(fire);
	//extinguisher_->draw();
	//DrawCrosshair(camera->width/2,camera->height/2);
}

void MenuState::drawCube(int x0, int x1, int z0, int z1) {
	glPushMatrix();

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(x0, -1, z0);
	glVertex3f(x1, -1, z0);
	glVertex3f(x1, 1, z0);
	glVertex3f(x0, 1, z0);

	glColor3f(1, 1, 0);
	glVertex3f(x0, -1, z1);
	glVertex3f(x1, -1, z1);
	glVertex3f(x1, 1, z1);
	glVertex3f(x0, 1, z1);

	glColor3f(0, 0, 1);
	glVertex3f(x0, -1, z0);
	glVertex3f(x0, 1, z0);
	glVertex3f(x0, 1, z1);
	glVertex3f(x0, -1, z1);

	glColor3f(1, -1, 1);
	glVertex3f(x1, -1, z0);
	glVertex3f(x1, 1, z0);
	glVertex3f(x1, 1, z1);
	glVertex3f(x1, -1, z1);

	glColor3f(0, 1, 0);
	glVertex3f(x0, -1, z0);
	glVertex3f(x1, -1, z0);
	glVertex3f(x1, -1, z1);
	glVertex3f(x0, -1, z1);

	glColor3f(1, 1, 0);
	glVertex3f(x0, 1, z0);
	glVertex3f(x1, 1, z0);
	glVertex3f(x1, 1, z1);
	glVertex3f(x0, 1, z1);
	glEnd();

	glPopMatrix();
}

void MenuState::preDraw()
{
	//extinguisher_->draw();
	player_->getItem()->draw();
}

void MenuState::checkMovementCollission()
{


}
