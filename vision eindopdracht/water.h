#pragma once
#include "ObjModel.h"
class water : public ObjModel
{
public:
	water(float startx, float starty, float startz, float xdirection, float ydirection);
	void update(float deltatime);
	~water();
private:

};
