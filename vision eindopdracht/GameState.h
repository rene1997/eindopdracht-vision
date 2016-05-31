#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStateManager.h"
#include "Camera.h"

class GameState {
	public:
		virtual void Init(GameStateManager* game, Camera * camera, KeyHandler * key_handler) = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void preDraw() =0;
		virtual void checkMovementCollission() = 0;
	//void ChangeState(GameStateManager* game, GameState* state) { game->ChangeState(state); }

	protected: 
		GameState() { }
};
#endif
