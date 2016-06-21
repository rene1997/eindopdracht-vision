#pragma once
#include "ObjModel.h"
#include "KeyHandler.h"

class water;
class Camera;

class Extinguisher :
	public ObjModel
{
public:
	Extinguisher(KeyHandler * handler);
	~Extinguisher();
	water * FireWater(Camera * camera);
	void draw() override;
private:
	KeyHandler * handler;
	int firecounter = 0;
};

