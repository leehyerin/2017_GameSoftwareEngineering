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

#define CHAR_KIND_YELLOW_BIG 0
#define CHAR_KIND_BLUE_SPEEDY 1
#define CHAR_KIND_Orange_DOZEN 2
#define CHAR_KIND_Purple_TANK 3

#define CHAR_UP 0
#define CHAR_DOWN 2
#define CHAR_LEFT 3
#define CHAR_RIGHT 1


#define BG_LEVEL 0.99f
#define BULLET_LEVEL  0.2f

#define HPBAR_HEIGHT 5.f

#define KING_ACT 0
#define KING_INACT	1

