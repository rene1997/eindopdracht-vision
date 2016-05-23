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
	for (int i = 0; i < 255; i++)
	{
		if (keys[i])
			checkKey(keys[i]);
			
	}
}

void KeyHandler::checkKey(char key)
{
	switch(key)
	{
	case 27:		//ESC: exit
		exit(0);
		break;

	default:
		break;
	}
	
}


KeyHandler::~KeyHandler()
{
}
