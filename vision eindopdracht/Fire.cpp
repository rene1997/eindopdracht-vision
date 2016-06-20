#include "Fire.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>


Fire::Fire(float x, float y, float z)
{
	this->xpos = x;
	this->ypos = y;
	this->zpos = z;
	
	
	srand(time(0));
	for (int i = 1; i < health; i++) {
		addParticle(i);
	}
	
}

void Fire::addParticle(int i)
{
	struct FireParticle * item = new FireParticle;
	int randomb = rand() % 2;

	float xpart = float(rand() % i) / 100;
	float ypart = float(i) / 50;
	float zpart = float(rand() % i) / 100;

	if (randomb) {
		item->xpos = xpos + xpart;
		item->zpos = zpos + zpart;
	}
	else {
		item->xpos = xpos - xpart;
		item->zpos = zpos - zpart;
	}

	item->ypos = ypos + ypart;
	item->state = State::first;
	particles.push_back(item);
}

void Fire::removeHealth()
{
	health--;
}

void Fire::update(float deltatime) {
	for each(auto &m in particles) {
		m->ypos += 0.005 * deltatime * (rand() % 4);
		m->zpos += 0.005 * deltatime * (rand() % 4);
		m->xpos += 0.005 * deltatime * (rand() % 4);
	}

	std::vector<FireParticle*>::const_iterator iter;
	for (iter = particles.begin(); iter != particles.end(); ++iter ) {
		FireParticle * particle = dynamic_cast<FireParticle *>(*iter);
		if (particle->ypos > ypos + 2) {
			particle->state = State::second;
		}
		if (particle->ypos > ypos + 4) {
			try{
				particles.erase(iter);
			}
			catch(int e){
				
			}
			
		}
		
	}

	for (int i = 1; i <health / 20; i++) {
		int j = rand() %150;
		addParticle(j + 1);
		
	}

}

void Fire::draw() {
	glDisable(GL_TEXTURE_2D);
	float size = 0.05f;
	for each(auto &m in particles) {
		float tempx = m->xpos;
		float tempy = m->ypos;
		float tempz = m->zpos;
		glBegin(GL_TRIANGLES);
		//side 1
		glColor3f(0.5f, 0.5f, 0.0f); glVertex3d(tempx + 0.0f, tempy + size, tempz + 0.0f);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx - size, tempy - size, tempz + size);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx + size, tempy - size, tempz + size);

		//side 2
		glColor3f(0.5f, 0.5f, 0.0f); glVertex3d(tempx + 0.0f, tempy - size, tempz + 0.0f);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx - size, tempy - size, tempz + size);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx + 0.0f, tempy - size, tempz - size);

		//side 3
		glColor3f(0.5f, 0.5f, 0.0f); glVertex3d(tempx + 0.0f, tempy + size, tempz + 0.0f);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx + 0.0f, tempy - size, tempz - size);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx + size, tempy - size, tempz + size);

		//side 4
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx - size, tempy - size, tempz + size);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx + 0.0f, tempy - size, tempz - size);
		glColor3f(0.5f, 0.2f, 0.0f); glVertex3d(tempx + size, tempy - size, tempz + size);

		glEnd();

	}
	glColor3f(1, 1, 1);
}

Fire::~Fire()
{
}
