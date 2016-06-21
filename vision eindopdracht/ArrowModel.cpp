//
// Created by Yorick Rommers on 20/05/16.
//

#include <cmath>
#include <iostream>
#include "ArrowModel.h"
#include "GameState.h"

# define M_PI           3.14159265358979323846  /* pi */

class Player;

ArrowModel::ArrowModel( float startx, float starty, float startz, float xdirection, float ydirection, GameState * state) : ObjModel(""/*water object*/) {



    //startpoint arrow:
	xpos = startx;
	ypos = starty;
	zpos = startz;
	yrot = ydirection;
	if (yrot > 90 || yrot < -90)
		xrot = -xdirection;
	else
		xrot = xdirection;
	

}

ArrowModel::~ArrowModel()
{
}


float ArrowModel::toRadian(float degree) {
	return (degree / 180.0f) * (float)M_PI;
}


void ArrowModel::update(float deltatime) {

	ypos -= (sin(toRadian(xrot))) * 0.1f * deltatime;
	zpos += cos(toRadian(yrot))* 0.1f * deltatime;
	//if rotate on y as: 
	xpos += (sin(toRadian(yrot))) * 0.1f * deltatime;
	
	//gravity
	xrot += 0.1f * deltatime ;

	if(ypos < -15 )
	{
		
	}
}














