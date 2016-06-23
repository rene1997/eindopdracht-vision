#include "MenuState.h"
#include "Camera.h"
#include "menuOverlay.h"

#include <utility>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "stb_image.h"
#include "FireItem.h"
#include "Fire.h"
#include "water.h"


//int crosshairX, crosshairY;

void MenuState::Init(GameStateManager * game, Camera * cam, KeyHandler * hand)
{
	this->manager = game;
	this->camera = cam;
	camera->rotY += 90;
	this->key_handler = hand;
	this->player_ = new Player(key_handler, camera, this);

	item = new FireItem("models/garbage_bin/untitled1.obj", 11,0,15);

	glColor3f(0, 0, 0);
	ObjModel * truck = new ObjModel("models/faun3500/untitled2.obj");
	truck->xpos = -5; truck->zpos = -8; truck->ypos = 0;// truck->yrot = 45;
	models.push_back(truck);

	tasks = new vector<pair<std::string, bool>>;
	tasks->push_back(pair<std::string, bool>("1) Walk to the container!", false));
	tasks->push_back(pair<std::string, bool>("2) Extinguish the fire", false));

	LoadGround();
	Loadskybox();
	qobj = gluNewQuadric();
	this->overlay_ = new menuOverlay(camera, tasks);
}

void MenuState::Cleanup()
{
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::HandleEvents()
{

}

void MenuState::Update()
{
	//handle extuingishing
	if (key_handler->keys['l']) {
		counter++;
		if (counter > 3) {
			watermodels.push_back(extinguisher_->FireWater(camera));
			counter = 0;
		}
		
	}

	if (item->getFireHealth() <= 0) {
		manager->nextState();
	}
	
	//task one:
	if (!tasks->at(0).second) {
		if (item->getFireHealth() < 100) {
			tasks->at(0).second = 1;
		}
	}

	//task two:
	if (!tasks->at(1).second) {
		if (item->getFireHealth() <= 0 ) {
			tasks->at(1).second = 1;
		}
	}


	player_->update();
	item->update(1);
	


	std::vector<water *>::const_iterator iter;
	for (iter = watermodels.begin(); iter != watermodels.end(); ++iter) {
		water * particle = dynamic_cast<water *>(*iter);

		if (item->checkCollision(particle->xpos, particle->zpos)) {
			item->removeFireHealth(); 
			watermodels.erase(iter);
			if (watermodels.size() > 0) {
				iter = watermodels.begin();
			}
			else {
				break;
			}
		}


		try {
			if (particle->update(1)) {
				watermodels.erase(iter);
				if (watermodels.size() > 0) {
					iter = watermodels.begin();
				}
				else {
					break;
				}			 
			}
		}
		catch (int e) {
			
		}
	}
}



void MenuState::DrawGround() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTexture);

	glColor3f(1, 1, 1);
	glPushMatrix();
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(-50, 0, -50);
	glTexCoord2f(8, 0); glVertex3f(50, 0, -50);
	glTexCoord2f(8, 8); glVertex3f(50, 0, 50);
	glTexCoord2f(0, 8); glVertex3f(-50, 0, 50);
	glEnd();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
}

void MenuState::DrawOverLay()
{

}


void MenuState::Draw()
{
	glColor3f(1, 1, 1);
	gluQuadricDrawStyle(qobj, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	gluSphere(qobj, 200, 50, 50);


	glColor3f(1, 1, 1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat positions[4] = { 11,3,15, 0.5 };
	glLightfv(GL_LIGHT0, GL_POSITION, positions);

	DrawGround();

	for (auto &m : watermodels) {
		m->draw();
	}

	item->draw();
	
	for each(auto &m in models) {
		m->draw();
	}

	overlay_->drawMenuOverLay(item->getFireHealth());


}

void MenuState::preDraw()
{
	//extinguisher_->draw();
	player_->getItem()->draw();
}

void MenuState::checkMovementCollission()
{


}

void MenuState::LoadGround(){
	int width, height, bpp;
	unsigned char* data = stbi_load("textures/grass.png", &width, &height, &bpp, 4);
	glGenTextures(1, &groundTexture);
	glBindTexture(GL_TEXTURE_2D, groundTexture);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		data);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(data);

}

void MenuState::Loadskybox() {
	int width, height, bpp;
	unsigned char* data = stbi_load("textures/sky1.jpg", &width, &height, &bpp, 4);
	glGenTextures(1, &skyboxTexture);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width,		//width
		height,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		data);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(data);

}


