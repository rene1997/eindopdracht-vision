#pragma once
#include "Camera.h"
#include "KeyHandler.h"
#include "GameState.h"
#include "ObjModel.h"
class Player
{
public:
	Player(KeyHandler * keys, Camera * cam, GameState * state);
	void update();
	void checkKeys();
	ObjModel* getItem();
	ObjModel * item_;
	int speed = 1;
	~Player();
private:
	KeyHandler * keyhand_;
	Camera * camera_;
	GameState * state_;
	int counter = 0;
	

	void walk(bool forward, bool right, bool left, bool back);
	void move(float angle, float multiplier);

};

