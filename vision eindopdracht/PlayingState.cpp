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

void PlayingState::Init(GameStateManager *game, Camera *cam, KeyHandler * hand) {
    this->manager = game;
	this->camera = cam;
	this->key_handler = hand;
	
	vector<ObjModel*> temp;

	models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/extinguisher/Fireextinguisher_BI.obj")));

	/*bow = new AnimatedBowModel(models); */
	


	//make bloem and push to models vector
//	ObjModel *bloem = new ObjModel("models/bloemetje/PrimroseP.obj");
//	bloem->xpos = 4;
//    models.push_back(pair<int, ObjModel*>(1,bloem));

	//make bloem and push to models vector


	

//	make baksteen and push to models vector
//    ObjModel *baksteen = new ObjModel("models/cube/cube-textures.obj");
//    baksteen->xpos = 2;
//    models.push_back(pair<int, ObjModel *>(1, baksteen));
//
//    ObjModel *bak = new StationaryObjModel("models/cube/cube-textures.obj");
//    bak->xpos = 0;
//    models.push_back(pair<int, ObjModel *>(1, bak));
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update() {
	
    bool collides = false;
	for (auto &obj1 : models) {
		obj1.second->update(0);
	}
}


void PlayingState::Draw() {
    for( auto &m : models) {
        m.second->draw();
    }

}

void PlayingState::preDraw()
{
	//bow->getModel()->draw();
}

void PlayingState::checkMovementCollission()
{
}

void PlayingState::HandleEvents() {
   
}


















