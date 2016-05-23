#include "Extinguisher.h"
#include "KeyHandler.h"



Extinguisher::Extinguisher(KeyHandler * hand):ObjModel("models/bow/bow_01.obj")
{
	this->handler = hand;
	xpos = ypos = zpos = xrot = yrot = zrot = 0;
	zpos = -0.75;
	ypos = -1.25;
	xpos = 0.75;
	yrot = -80;
}


Extinguisher::~Extinguisher()
{
}

void Extinguisher::draw()
{
	ObjModel::draw();
}



