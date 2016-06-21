#pragma once
#include "ObjModel.h"
#include "fire.h"

class FireItem :
	public ObjModel
{
public:
	FireItem(string fileName, float xpos, float ypos, float zpos);
	~FireItem();
	bool update(float deltatime) override;
	void draw() override;
	bool checkCollision(float x, float z);
	int getFireHealth();
	void removeFireHealth() {
		fire->removeHealth();
	}
private:
	Fire * fire;
	int health = 100;
	float width;
	float depth;
	
};

