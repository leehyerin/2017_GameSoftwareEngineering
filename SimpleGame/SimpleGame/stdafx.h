#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 800

typedef struct POS
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
}POS;

typedef struct RGBA
{
	float R = 0.f;
	float G = 0.f;
	float B = 0.f;
	float A = 0.0f;
}RGBA;

#define CHAR_UP 3
#define CHAR_DOWN 2
#define CHAR_LEFT 0
#define CHAR_RIGHT 1


#define BG_LEVEL 0.99f

#define HPBAR_HEIGHT 5.f
