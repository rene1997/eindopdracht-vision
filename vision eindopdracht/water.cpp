#include "water.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

# define M_PI           3.14159265358979323846  /* pi */

water::water(float startx, float starty, float startz, float xdirection, float  ydirection):ObjModel("models/water/water4.obj")
{
	xpos = startx;
	ypos = starty;
	zpos = startz;
	yrot = ydirection;

	if (yrot > 90 || yrot < -90)
		xrot = -xdirection;
	else
		xrot = xdirection;

}

float toRadian(float degree) {
	return (degree / 180.0f) * (float)M_PI;
}


void water::update(float deltatime) {
	//ypos -= (sin(toRadian(xrot))) * 0.5f * deltatime;
	zpos += cos(toRadian(yrot))* 0.01f * deltatime;
	//if rotate on y as: 
	xpos += (sin(toRadian(yrot))) * 0.01f * deltatime;

	//gravity
	xrot += 0.1f * deltatime;

	if (ypos < -15)
	{
		//remove
	}
}



water::~water()
{
}
