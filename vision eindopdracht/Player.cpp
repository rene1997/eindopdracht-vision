#include "Player.h"
#include "Extinguisher.h"
#include <stdio.h>




Player::Player(KeyHandler * keys, Camera * cam, GameState * state)
{
	this->keyhand_ = keys;
	this->camera_ = cam;
	this->state_ = state;
	this->item_ = new Extinguisher(keys);
}

void Player::update()
{
	checkKeys();
}

void Player::checkKeys()
{
	if (keyhand_->keys['w'] || keyhand_->keys['a'] || keyhand_->keys['s'] || keyhand_->keys['d']) {
		walk(keyhand_->keys['w'], keyhand_->keys['d'], keyhand_->keys['a'], keyhand_->keys['s']);
		state_->checkMovementCollission();
		
	}
}

Player::~Player()
{
}

void Player::walk(bool forward, bool right, bool left, bool back)
{
	
	if (forward) move(90, speed);
	if (speed  != 5) {
		if (right) move(180, speed);

		if (left) move(0, speed);
	}
	
	
	
	if (back) move(270, speed);

	counter++;

	
}

void Player::move(float angle, float multiplier)
{
	camera_->posX += (float)cos((camera_->rotY + angle) / 180 * 3.14) * multiplier / 10;
	camera_->posZ += (float)sin((camera_->rotY + angle) / 180 * 3.14) * multiplier / 10;
	
}

ObjModel * Player::getItem()
{
	return item_;
}
