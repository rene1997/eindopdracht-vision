#include "GL/freeglut.h"
#include <cstdio>
#include "Camera.h"
#include "GameStateManager.h"
#include "KeyHandler.h"

KeyHandler key_handler;
Camera camera;
GameStateManager manager;

void Display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)camera.width / camera.height, 0.1, 500);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//predraw
	manager.preDraw();

	
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, -camera.posY, camera.posZ);



	manager.Draw();


	glFlush();
	glutSwapBuffers();

}

void onIdle()
{
	glutPostRedisplay();
	
}

void onTimer(int id) {
	key_handler.Update();
	manager.Update();
	
	glutTimerFunc(1000/60, onTimer, 1);
	
}

void onKeyboard(unsigned char key, int one, int two)
{
	key_handler.onKeyboard(key, one, two);
	if (key == ']') {
		manager.nextState();
	}
	if (key == 27) {
		exit(0);
	}
}

void onKeyboardUp(unsigned char key, int one, int two)
{
	key_handler.onKeyboardUp(key, one, two);
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && !state) {
		key_handler.onKeyboard('l', x, y);
	}else if(button == GLUT_LEFT_BUTTON){
		key_handler.onKeyboardUp('l', x, y);
	}

}

void mousePassiveMotion(int x, int y) {

	int dx = x - camera.width / 2;
	int dy = y - camera.height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotX += dy / 10.0f;
		if (camera.rotX > 30) {
			camera.rotX = 30;
		}
		else if (camera.rotX < -30) {
			camera.rotX = -30;
		}
		camera.rotY += dx / 10.0f;
		glutWarpPointer(camera.width / 2, camera.height / 2);
	}
}

int main(int argc, char* argv[])
{
	key_handler = KeyHandler();
	
	
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Mooi");

	glEnable(GL_DEPTH_TEST);
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutIdleFunc(onIdle);
	glutDisplayFunc(Display);
	glutReshapeFunc([](int w, int h) { camera.width = w; camera.height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(onKeyboard);
	glutTimerFunc(1000 / 60, onTimer, 1);
	glutKeyboardUpFunc(onKeyboardUp);

	glutMouseFunc(mouseFunc);

	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(camera.width / 2, camera.height / 2);

	manager.Init(&camera, &key_handler);

	glutMainLoop();


}
