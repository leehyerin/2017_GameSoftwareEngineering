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