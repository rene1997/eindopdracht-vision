#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "ObjModel.h"
#include "Extinguisher.h"
#include "Player.h"
#include <vector>
#include <utility>

class menuOverlay;

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
		void drawCube(int x0, int x1, int z0, int z1);
		virtual void preDraw() override;
		virtual void checkMovementCollission() override;
	private:
		GameStateManager *manager;
		Camera * camera;
		KeyHandler * key_handler;
		vector<ObjModel*>  models;
		Extinguisher * extinguisher_;
		Player * player_;
		menuOverlay * overlay_;
		std::vector<std::pair<std::string, bool>>* tasks;
		int fire = 250;
};

#endif
