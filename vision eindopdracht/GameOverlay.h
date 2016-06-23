#pragma once

class Camera;

class GameOverlay
{
public:
	GameOverlay(Camera * cam);
	~GameOverlay();

private:
	Camera * camera_;
};

void drawGameOverLay(Camera * camera);

