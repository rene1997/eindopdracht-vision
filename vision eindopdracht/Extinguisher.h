#pragma once
#include "ObjModel.h"
#include "KeyHandler.h"

class Extinguisher :
	public ObjModel
{
public:
	Extinguisher(KeyHandler * handler);
	~Extinguisher();
	void draw() override;
private:
	KeyHandler * handler;
};

