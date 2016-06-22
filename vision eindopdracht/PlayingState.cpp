//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "Player.h"
#include "stb_image.h"
#include "Extinguisher.h"
#include "FireItem.h"
#include "level2Overlay.h"
#include "water.h"

GLuint LoadGround();
void DrawGround(int groundTexture);

void PlayingState::Init(GameStateManager *game, Camera *cam, KeyHandler * hand) {
    this->manager = game;
	this->camera = cam;
	this->key_handler = hand;
	this->player_ = new Player(hand, cam, this);


	tasks = new vector<pair<std::string, bool>>;
	tasks->push_back(pair<std::string, bool>("1) Find the fire", false));
	tasks->push_back(pair<std::string, bool>("2) Extinguish the fire", false));
	this->overlay_ = new Level2Overlay(cam, tasks);
	
	//set car as item
	truck_ = new ObjModel("models/faun3500/untitled2.obj");
	truck_->ypos = -2.5; truck_->zpos = 4.1; truck_->xpos = 0.5; truck_->yrot = 90;
	player_->item_ = truck_;
	player_->speed = 5;


	//set camera:
	camera->posY = 6;

	this->groundTexture = LoadGround();
	vector<ObjModel*> temp;

	item_ = new FireItem("models/garbage_bin/untitled1.obj", -150, 0, -150);

}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update() {
	//check if changing vehicle to foot
	if (key_handler->keys['e'] && playerstate_ == PlayerStates::car) {
		camera->posY = 2;
		playerstate_ = PlayerStates::walking;
		player_->item_ = new Extinguisher(key_handler);
		player_->speed = 1;
		truck_->xpos = 3 + camera->posX * -1;
		truck_->zpos = 4 + camera->posZ * -1;
		truck_->ypos = 0;
		
		


	}
	//go back in vehicle
	if (key_handler->keys['E'] && playerstate_ == PlayerStates::walking) {
		//set camera back:
		camera->posX = truck_->xpos * -1;
		camera->posZ = truck_->zpos * -1;
		camera->posY = 6;

		//set truck on correct position
		truck_->ypos = -2.5; truck_->zpos = 4.1; truck_->xpos = 0.5; truck_->yrot = 90;

		//player settting correct
		playerstate_ = PlayerStates::car;
		player_->item_ = truck_;
		player_->speed = 5;
	}
	
	//task one:
	if (!tasks->at(0).second) {
		if (item_->getFireHealth() < 100) {
			tasks->at(0).second = 1;
		}
	}

	//task two:
	if (!tasks->at(1).second) {
		if (item_->getFireHealth() <= 0) {
			tasks->at(1).second = 1;
		}
	}

	//handle extuingishing
	if (key_handler->keys['l'] && playerstate_ == PlayerStates::walking) {
		counter++;
		if (counter > 3) {
			Extinguisher * ex = dynamic_cast<Extinguisher*>(player_->item_);
			if (ex != 0) {
				watermodels.push_back(ex->FireWater(camera));
			}
			counter = 0;
		}

	}

	UpdatWaterModels();
	if (item_->getFireHealth() <= 0) {
		//TODO Finish game
		exit(0);
	}

	item_->update(1);
	player_->update();
}


void PlayingState::UpdatWaterModels() {
	std::vector<water *>::const_iterator iter;
	for (iter = watermodels.begin(); iter != watermodels.end(); ++iter) {
		water * particle = dynamic_cast<water *>(*iter);

		if (item_->checkCollision(particle->xpos, particle->zpos)) {
			item_->removeFireHealth();
			watermodels.erase(iter);
			if (watermodels.size() > 0) {
				iter = watermodels.begin();
			}
			else {
				break;
			}
		}
		try {
			if (particle->update(1)) {
				watermodels.erase(iter);
				if (watermodels.size() > 0) {
					iter = watermodels.begin();
				}
				else {
					break;
				}
			}
		}
		catch (int e) {

		}
	}
}

void PlayingState::Draw() {
	DrawGround(groundTexture);
    for( auto &m : models) {
        m.second->draw();
    }

	for (auto &m : watermodels) {
		m->draw();
	}

	if (playerstate_ == PlayerStates::walking) {
		truck_->draw();
	}

	item_->draw();
	
	overlay_->drawMenuOverLay(item_->getFireHealth());
	
}

void PlayingState::preDraw()
{
	player_->getItem()->draw();
}

void PlayingState::checkMovementCollission()
{
}

void PlayingState::HandleEvents() {
   
}


void DrawGround(int groundTexture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTexture);

	glColor3f(1, 1, 1);
	glPushMatrix();
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(-200, 0, -200);
	glTexCoord2f(8, 0); glVertex3f(200, 0, -200);
	glTexCoord2f(8, 8); glVertex3f(200, 0, 200);
	glTexCoord2f(0, 8); glVertex3f(-200, 0, 200);
	glEnd();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
}

GLuint LoadGround() {
	GLuint groundTexture;
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
	return groundTexture;
}


















