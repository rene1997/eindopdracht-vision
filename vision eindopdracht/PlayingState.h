//
// 
//

#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H


#include "GameState.h"
#include "ObjModel.h"
#include "Camera.h"

enum PlayerStates {car, walking};

class water;
class Player;
class Level2Overlay;
class FireItem;

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
		void UpdatWaterModels();
        GameStateManager *manager;
        vector<pair<int, ObjModel*> > models; //Models to be drawn by the Draw() function
		KeyHandler * key_handler;
		Camera * camera;
		PlayerStates playerstate_ = PlayerStates::car;
		GLuint  groundTexture;
		FireItem * item_;
		vector<water*>  watermodels;
		Player * player_;
		ObjModel * truck_;
		Level2Overlay * overlay_;
		std::vector<std::pair<std::string, bool>>* tasks;
		int counter = 0;
};


#endif //SHIRO_BOUGYO_PLAYINGSTATE_H
