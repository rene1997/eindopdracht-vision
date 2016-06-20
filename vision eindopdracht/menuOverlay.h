#pragma once

#include <string>
#include <vector>
#include <utility>

class Camera;
class menuOverlay
{
public:
	menuOverlay(Camera * cam, std::vector<std::pair<std::string, bool>>* tasks);
	~menuOverlay();

	void drawMenuOverLay(int overlaystatus);
	
private:
	Camera * camera_;

	std::vector<std::pair<std::string, bool>>* tasks;
	void drawHealthBar(int overlaystatus);
	void drawInfo();

	
};

void initDrawing();
void stopDrawing();
void glutdrawstring(std::string str, int x, int y, void* style);

