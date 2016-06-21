//
// Created by Yorick Rommers on 20/05/16.
//

#ifndef SHIRO_BOUGYO_ARROWMODEL_H
#define SHIRO_BOUGYO_ARROWMODEL_H

#include "GameState.h"
#include "ObjModel.h"

class Player;
class GameState;

class ArrowModel : public ObjModel {
public:
    //ArrowModel( float x, float y, float z);

	ArrowModel(float startx, float starty, float startz, float xdirection, float ydirection, GameState * state);
	~ArrowModel(void);

	float toRadian(float degree);
    void update(float deltatime) override;
private:
	GameState * state;
};


#endif //SHIRO_BOUGYO_ARROWMODEL_H
