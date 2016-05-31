#include "KeyHandler.h"
#include <cstring>
#include <cstdlib>


KeyHandler::KeyHandler()
{
	memset(keys, 0, sizeof(keys));

}

void KeyHandler::onKeyboard(unsigned char key, int, int)
{
	keys[key] = true;
	checkKey(key);
}

void KeyHandler::onKeyboardUp(unsigned char key, int, int)
{
	keys[key] = false;
}

void KeyHandler::Update()
{

}

void KeyHandler::checkKey(char key)
{

	
}


KeyHandler::~KeyHandler()
{
}
