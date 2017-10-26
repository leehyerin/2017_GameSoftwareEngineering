#include "stdafx.h"
#include "GameObject.h"
using namespace std;



GameObject::~GameObject()
{
}

void GameObject::Update(float elapsedTime)
{
	float elapsedTimeinSecond=elapsedTime / 1000.f;

	posX = posX + dir*speedX*elapsedTimeinSecond;
	posY = posY + dir*speedY*elapsedTimeinSecond;

	if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
		if (posX != posY)
			dir *= -1;
		else
			dir *= -1;

	
}