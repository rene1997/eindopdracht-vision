#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "ObjModel.h"
#include "Extinguisher.h"

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
		virtual void Draw() override;
		virtual void preDraw() override;
		//void DrawCrosshair(int x, int y);
	private:
		GameStateManager *manager;
		Camera * camera;
		KeyHandler * key_handler;
		vector<ObjModel*>  models;
		Extinguisher * extinguisher_;

};

#endif