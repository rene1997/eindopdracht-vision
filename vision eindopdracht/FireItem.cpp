#include "FireItem.h"



FireItem::FireItem(string fileName, float xpos, float ypos, float zpos):ObjModel(fileName)
{
	this->xpos = xpos;
	this->ypos = ypos;
	this->zpos = zpos;
	this->width = vertices_max->x - vertices_min->x;
	this->depth = vertices_max->z - vertices_min->z;
	this->fire = new Fire(xpos, vertices_max->y, zpos- (depth /2 ));
}


FireItem::~FireItem()
{
}

void FireItem::update(float deltatime) {
	fire->update(deltatime);
}

void FireItem::draw()
{
	fire->draw();
	ObjModel::draw();
}

bool FireItem::checkCollision(float x, float z)
{
	float maxX = this->xpos + vertices_max->x * 2.5;
	float maxZ = this->zpos + vertices_max->z * 2.5;
	float maxY = this->ypos + vertices_max->y * 2.5;
	float minX = this->xpos + vertices_min->x * 2.5;
	float minZ = this->zpos + vertices_min->z * 2.5;
	float minY = this->ypos + vertices_min->y * 2.5;
	
	bool hasCollision = 0;

	if (x > minX && x < maxX && z > minZ && z < maxZ) {
		//z > minZ && z < maxZ
		hasCollision = 1;
	}
	else if(x < minX && x > maxX && z < minZ && z > maxZ){
		hasCollision = 1;
	}

	
	return hasCollision;
}

int FireItem::getFireHealth()
{
	return fire->getHealth();;
}
