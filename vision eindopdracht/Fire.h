#pragma once

#include <vector>

enum State {
	first,second, third
};

struct FireParticle {

	float xpos;
	float ypos;
	float zpos;
	State state;
};

class Fire
{
public:
	Fire(float x, float y, float z);

	void addParticle(int i);
	
	void removeHealth();
	
	int getHealth() {
		return health;
	}

	void update(float deltatime);
	
	void draw();

	~Fire();
private:
	std::vector<FireParticle *> particles;
	float xpos, ypos, zpos;
	float health = 100;
};

