#include "stdafx.h"
#include "GameObject.h"
using namespace std;



GameObject::~GameObject()
{
}

void GameObject::Update(float elapsedTime)
{
	float elapsedTimeInSecond=elapsedTime / 1000.f;

	posX = posX + dir * speedX * elapsedTimeInSecond;
	posY = posY + dir * speedY * elapsedTimeInSecond;

	if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
		if (posX != posY)
			dir *= -1;
		else
			dir *= -1;
	

	lifeTime -= 0.5f;
}