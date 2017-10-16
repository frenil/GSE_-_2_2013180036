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

#include <vector>

Renderer *g_Renderer = nullptr;
VerticalObject obj1(Vector(0, 0, 0), 20, Vector(1, 1, 0), 1);
CGameObject obj2(Vector(-250,50,0),20,Vector(1,1,0),1);
vector<CGameObject> objs;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	obj1.Render();
	obj2.Render();
	for (auto i = objs.begin(); i != objs.end(); ++i) {
		i->Render();
	}
	glutSwapBuffers();
}

void Idle(void)
{
	obj1.Update();
	obj2.Update();
	for (auto i = objs.begin(); i != objs.end(); ++i) {
		i->Update();
	}
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	CGameObject ob(Vector(x - (WINW / 2), (WINH / 2) - y, 0), 10, Vector(1, 0, 0), 1);
	ob.SetRenderer(g_Renderer);
	objs.push_back(ob);
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
	glutInitWindowSize(WINW,WINH);
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
	g_Renderer = new Renderer(WINW,WINH);
	obj1.SetRenderer(g_Renderer);
	obj2.SetRenderer(g_Renderer);

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

    return 0;
}

