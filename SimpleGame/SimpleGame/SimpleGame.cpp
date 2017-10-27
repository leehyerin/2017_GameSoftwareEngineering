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

#include "GameObject.h"
#include "SceneMgr.h"


SceneMgr *g_SceneMgr = NULL;

DWORD g_startTime = 0;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	DWORD endTime = timeGetTime();
	DWORD elapedTIme = endTime - g_startTime;
	g_startTime = endTime;

	g_SceneMgr->Update(elapedTIme);
	g_SceneMgr->DrawGameObject();
	
	glutSwapBuffers();
}


void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	bool Flag;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_SceneMgr->CreateGameObject(x-250,250-y);
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
	glutInitWindowSize(500, 500);
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
	

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_SceneMgr = new SceneMgr();

	g_startTime = timeGetTime();

	glutMainLoop();

	delete g_SceneMgr;

    return 0;
}


