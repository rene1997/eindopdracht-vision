#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "ObjModel.h"
#include "Extinguisher.h"
#include "Player.h"
#include "FireItem.h"
#include <vector>
#include <utility>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class menuOverlay;
class water;

class MenuState : public GameState  {
	// Inherited via GameState
	public:
		//int crosshairX, crosshairY;
		virtual void Init(GameStateManager * game, Camera * camera, KeyHandler * hand) override;
		virtual void Cleanup() override;
		virtual void Pause() override;
		virtual void Resume() override;
		virtual void HandleEvents() override;
		virtual void Update() override;
		void DrawGround();
		void DrawOverLay();
		virtual void Draw() override;
		virtual void preDraw() override;
		virtual void checkMovementCollission() override;
		void LoadGround();
		void Loadskybox();
	private:
		short counter = 0;
		GameStateManager *manager;
		Camera * camera;
		GLUquadricObj *qobj;
		KeyHandler * key_handler;
		vector<water*>  watermodels;
		vector<ObjModel *> models;
		FireItem * item;
		Extinguisher * extinguisher_;
		Player * player_;
		menuOverlay * overlay_;
		std::vector<std::pair<std::string, bool>>* tasks;
		GLuint  groundTexture;
		GLuint skyboxTexture;
};

#endif
