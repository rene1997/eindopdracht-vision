#pragma once

#include <string>
#include <vector>
#include <utility>

class Camera;
class Level2Overlay
{
public:
	Level2Overlay(Camera * cam, std::vector<std::pair<std::string, bool>>* tasks);
	~Level2Overlay();

	void drawMenuOverLay(int overlaystatus);
	void initDrawing();
	void stopDrawing();
	void glutdrawstring(std::string str, int x, int y, void* style);

private:
	Camera * camera_;
	int counterinfo = 0;
	std::vector<std::pair<std::string, bool>>* tasks;
	void drawHealthBar(int overlaystatus);
	void drawInfo();


};



