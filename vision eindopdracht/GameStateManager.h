#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "Camera.h"
#include "KeyHandler.h"

class GameState;

class GameStateManager {
public:
	void Init(Camera * cam, KeyHandler * keyHand);
	void Cleanup();

	/*void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();*/
	void nextState();
	void previousState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	void preDraw();
private:
	// the stack of states
	std::vector<GameState*> states;
	short currentState;
	bool m_running;
	Camera * camera;
	KeyHandler * keyhandler;
};
#endif
