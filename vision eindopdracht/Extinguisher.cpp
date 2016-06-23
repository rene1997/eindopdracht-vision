#include "Extinguisher.h"
#include "KeyHandler.h"
#include "GL/freeglut.h"
#include "water.h"
#include "Camera.h"



Extinguisher::Extinguisher(KeyHandler * hand):ObjModel(/*"models/blusser/blusser.obj"*/"models/extinguisher/Fireextinguisher_BI.obj")
{
	this->handler = hand;
	xpos = ypos = zpos = xrot = yrot = zrot = 0;
	zpos = -0.75;
	ypos = -1.25;
	xpos = 0.4;
	yrot = -80;
}


Extinguisher::~Extinguisher()
{
}

water * Extinguisher::FireWater(Camera * camera) {
	float roty = camera->rotY;
	while (roty<0.0f) {
		roty += 360.0f;
	}
	roty = (float)(int(roty) % 360);
	water * waterparticle = new water(camera->posX * -1, camera->posY  , camera->posZ * -1, camera->rotX * -1.3, (roty * -1) - 180);
	return waterparticle;
}

void Extinguisher::draw()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	ObjModel::draw();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}



