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
#define COOLTIME 500.f
int CHAR_KIND = CHAR_KIND_Purple_TANK;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.56f, 0.55f, 0.188f, 1.f);   
	DWORD endTime = timeGetTime();
	DWORD elapedTIme = endTime - g_startTime;
	g_startTime = endTime;
	
	float elapsedTimeInSecond = elapedTIme / 1000.f;

	g_SceneMgr->Update(elapsedTimeInSecond);
	g_SceneMgr->DrawGameObject(elapsedTimeInSecond);
	

	glutSwapBuffers();
}


void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if (y > WINDOW_HEIGHT / 2 + 300)
		{
			if (x >=  285)			CHAR_KIND = CHAR_KIND_BLUE_SPEEDY;
			else if (x >=235 )		CHAR_KIND = CHAR_KIND_Purple_TANK;
			else if (x >= 185)		CHAR_KIND = CHAR_KIND_YELLOW_BIG;
			else if (x >=  135)		CHAR_KIND = CHAR_KIND_Orange_DOZEN;
		}

		if (y < WINDOW_HEIGHT / 2 - 50 || y > WINDOW_HEIGHT / 2 +300)
		{
			std::cout << "¡ØCREATE_ERROR\n"; return;
		}

		if (timeGetTime() - g_clickTime >= COOLTIME)
		{
			g_clickTime = timeGetTime();
			g_SceneMgr->CreateGameObject(x - WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - y, TEAM_ALLY, CHAR_KIND);
		}
		else
			std::cout << "¡ØCOOLTIME:" << (int)(COOLTIME - (timeGetTime() - g_clickTime)) / 1000 << "sec.\n"; return;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	if (key == VK_ESCAPE)
		PostQuitMessage(0);
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


