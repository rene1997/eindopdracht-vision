#include "MenuState.h"
#include "Camera.h"
#include "menuOverlay.h"

#include <utility>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "stb_image.h"
#include "FireItem.h"
#include "Fire.h"
#include "water.h"

//int crosshairX, crosshairY;

void MenuState::Init(GameStateManager * game, Camera * cam, KeyHandler * hand)
{
	this->manager = game;
	this->camera = cam;
	this->key_handler = hand;
	this->player_ = new Player(key_handler, camera, this);

	item = new FireItem("models/garbage_bin/untitled1.obj", 11,0,15);

	glColor3f(0, 0, 0);
	water * truck = new water(1,1,1,1,0);
	truck->xpos = 1; truck->zpos = 1; truck->ypos = 2;
	models.push_back(truck);

	tasks = new vector<pair<std::string, bool>>;
	tasks->push_back(pair<std::string, bool>("1) Walk to the cube!", false));

	LoadGround();

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
	
	item->update(1);
	


	//task one:
	if (!tasks->at(0).second) {
		if (item->checkCollision(camera->posX * -1, camera->posZ * -1)) {
			tasks->push_back(pair<std::string, bool>("2) Click to extinguish", false));
			tasks->at(0).second = true;
		}
	}
	

	//task 2:
	if (tasks->size() == 2 && !tasks->at(1).second) {

		if (item->checkCollision(camera->posX*-1, camera->posZ*-1) &&key_handler->keys['l']) {
			
			item->removeFireHealth();
		}
		if (item->getFireHealth() == 0) {

			tasks->at(1).second = true;
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


	for each (auto &m in models) {
		m->update(1);
	}


}



void MenuState::DrawGround() {



	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTexture);

	glColor3f(1, 1, 1);
	glPushMatrix();
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(-50, 0, -50);
	glTexCoord2f(8, 0); glVertex3f(50, 0, -50);
	glTexCoord2f(8, 8); glVertex3f(50, 0, 50);
	glTexCoord2f(0, 8); glVertex3f(-50, 0, 50);
	glEnd();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void MenuState::DrawOverLay()
{

}


void MenuState::Draw()
{
	glColor3f(1, 1, 1);
	//GLUquadricObj * sphere = gluNewQuadric();
	//gluSphere(sphere, 0.025, 15, 15);

	

	

	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.5);
	//glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat positions[4] = { 1,1,1, 0.5 };
	glLightfv(GL_LIGHT0, GL_POSITION, positions);

	DrawGround();

	
	
	for (auto &m : models) {
		m->draw();
	}
	


	item->draw();


	

	overlay_->drawMenuOverLay(item->getFireHealth());
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

void MenuState::LoadGround(){
	int width, height, bpp;
	unsigned char* data = stbi_load("textures/grass.png", &width, &height, &bpp, 4);
	glGenTextures(1, &groundTexture);
	glBindTexture(GL_TEXTURE_2D, groundTexture);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		data);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(data);

}


