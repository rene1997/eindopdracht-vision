#include "Extinguisher.h"
#include "KeyHandler.h"
#include "GL/freeglut.h"




Extinguisher::Extinguisher(KeyHandler * hand):ObjModel(/*"models/blusser/blusser.obj"*/"models/extinguisher/Fireextinguisher_BI.obj")
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
	glColor3f(1, 0, 0);
	ObjModel::draw();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
}



