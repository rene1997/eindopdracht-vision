//
// 
//

#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H


#include "GameState.h"
#include "ObjModel.h"
#include "Camera.h"

class PlayingState : public GameState {
    // Inherited via GameState
    public:
        virtual void Init(GameStateManager * game, Camera * camera, KeyHandler * hand) override;
        virtual void Cleanup() override;
        virtual void Pause() override;
        virtual void Resume() override;
        virtual void HandleEvents() override;
        virtual void Update() override;
        virtual void Draw() override;
		virtual void preDraw() override;
		virtual void checkMovementCollission() override;
    private:
        GameStateManager *manager;
        vector<pair<int, ObjModel*> > models; //Models to be drawn by the Draw() function
		KeyHandler * key_handler;
		Camera * camera;
		
};


#endif //SHIRO_BOUGYO_PLAYINGSTATE_H
