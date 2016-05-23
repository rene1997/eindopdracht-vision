#pragma once
class KeyHandler
{
public:
	KeyHandler();
	void onKeyboard(unsigned char key, int, int);
	void onKeyboardUp(unsigned char key, int, int);
	void Update();
	void checkKey(char key);
	~KeyHandler();
	bool keys[255];
	
};

