#include "water.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

# define M_PI           3.14159265358979323846  /* pi */

water::water(float startx, float starty, float startz, float xdirection, float  ydirection):ObjModel("models/water/water7.obj")
{
	xpos = startx;
	ypos = 2;
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


bool water::update(float deltatime) {
	ypos -= (sin(toRadian(xrot))) * 0.1f * deltatime;
	zpos += cos(toRadian(yrot))* 0.1f * deltatime;
	//if rotate on y as: 
	xpos += (sin(toRadian(yrot))) * 0.1f * deltatime;

	//gravity
	xrot += 1 * deltatime;

	if (ypos < -0.5)
	{
		
		return 1;
	}

	return 0;
}



water::~water()
{
}
