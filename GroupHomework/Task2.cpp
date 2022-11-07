#include "stdafx.h"
#include "Scene.h"

//Scene Manager
SceneManager scene;

//Functions
void Initialize()
{
	//Set Random Seed
	Util::Set_Random_Seed();
	//Initialize the Scene
	scene.Initialize();
	//Pre-processing the Sphere
	Shader::initBall();
}

void SetRC()
{
	Shader::Initialize();
}

void myDisplay(void)
{
	scene.Render();
}

void myReshape(int w, int h)
{
	scene.Window_Resize(w, h);
}

void Update_View(int val)
{
	scene.Update_State();
	myDisplay();
	glutTimerFunc(10, Update_View, 0);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	SceneManager::Keyboard_Detect(key, 1);
	scene.Keyboard_Events_Down(key);
}

void myKeyboardUpFunc(unsigned char key, int x, int y)
{
	SceneManager::Keyboard_Detect(key, 0);
}

void myKeyboardFunc_Special(int key, int x, int y)
{
	SceneManager::Keyboard_Detect_Special(key, 1);
	scene.Keyboard_Events_Down_Special(key);
}

void myKeyboardUpFunc_Special(int key, int x, int y)
{
	SceneManager::Keyboard_Detect_Special(key, 0);
}

void myMouse_Func(int button, int state, int x, int y) {
	switch (state) {
		case GLUT_DOWN:
			switch (button)
			{
				case GLUT_LEFT_BUTTON:
					scene.Mouse_Clicking_Events(x, y);
					break;
			}
			break;
	}
}

Err_Code Task2_main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	Initialize();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(scene.global_window_width, scene.global_window_height);
	glutCreateWindow("Group Homework");
	glutDisplayFunc(&myDisplay);
	glutTimerFunc(10, Update_View, 0);
	//Set Keyboard/Mouse Functions
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(myKeyboardFunc);
	glutKeyboardUpFunc(myKeyboardUpFunc);
	glutSpecialFunc(myKeyboardFunc_Special);
	glutSpecialUpFunc(myKeyboardUpFunc_Special);
	glutMouseFunc(myMouse_Func);
	//Set Rendering Configuration
	SetRC();
	//Main Loop
	glutMainLoop();
	return NO_ERR;
}