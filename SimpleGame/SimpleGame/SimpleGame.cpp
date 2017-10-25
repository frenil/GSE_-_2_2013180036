/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "GameObject.h"
#include "SceneMgr.h"

#include <vector>

Renderer *g_Renderer = nullptr;
SceneMgr *Scene = nullptr;
vector<CGameObject> objs;
static DWORD frameCount = 0;            //프레임 카운트수
static float timeElapsed = 0.0f;            //흐른 시간
static DWORD lastTime = timeGetTime();   //마지막 시간(temp변수)

void UpdateFPS()
{
	
	DWORD curTime = timeGetTime();      //현재 시간
	float timeDelta = (curTime - lastTime)*0.001f;        //timeDelta(1번생성후 흐른 시간) 1초단위로 바꿔준다.

	timeElapsed = timeDelta;

	lastTime = curTime;
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	Scene->Render();
	glutSwapBuffers();
}

void Idle(void)
{
	UpdateFPS();
	Scene->Update(timeElapsed);
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN) {
	}
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP) {

		CGameObject ob(Vector(x - (WINW / 2), (WINH / 2) - y, 0), 30, Vector(1, 1, 1), 1);
		Scene->AddObject(&ob, g_Renderer);
	}
	if (button == GLUT_RIGHT_BUTTON&&state == GLUT_DOWN) {
	}
	if (button == GLUT_RIGHT_BUTTON&&state == GLUT_UP) {
		{
		}
	}
			RenderScene();
}
void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINW, WINH);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(WINW, WINH);
	Scene = new SceneMgr();
	for (int i = 0; i < 20; ++i) {
	Scene->AddObject(new CGameObject(Vector(-350+rand()%700, -250 + rand() % 500,0), 30, Vector (1,1,1), 1)
				, g_Renderer);
	}

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete Scene;

	return 0;
}

