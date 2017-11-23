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
DWORD g_clickTime = 0;
#define COOLTIME 3000.f

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
		if (y < WINDOW_HEIGHT / 2)
		{
			std::cout << "※북쪽은 적 진영입니다.\n"; return;
		}

		if (timeGetTime() - g_clickTime >= COOLTIME)
		{
			g_clickTime = timeGetTime();
			g_SceneMgr->CreateGameObject(x - WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - y, TEAM_ALLY);
		}
		else
			std::cout << "※쿨타임:"<<(int)(COOLTIME - (timeGetTime() - g_clickTime ))/1000 <<"초 남았씁니다.\n"; return;
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
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
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

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_SceneMgr = new SceneMgr();

	g_startTime = timeGetTime();
	g_clickTime = timeGetTime();

	glutMainLoop();

	delete g_SceneMgr;

    return 0;
}


