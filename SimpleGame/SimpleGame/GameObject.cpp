#include "stdafx.h"
#include "GameObject.h"
using namespace std;

int dir = 1;
float time = 1.0;

GameObject::~GameObject()
{
}

void GameObject::Update(float x, float y)
{
	posX = posX + dir*x*time;
	posY = posY + dir*y*time;

	if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
		if (posX != posY)
			dir *= -1;
		else
			dir *= -1;
	
	
}