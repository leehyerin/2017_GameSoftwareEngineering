#include "stdafx.h"
#include "GameObject.h"
using namespace std;



GameObject::~GameObject()
{
}

void GameObject::Update()
{
	posX = posX + dir*speedX*t_time;
	posY = posY + dir*speedY*t_time;

	if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
		if (posX != posY)
			dir *= -1;
		else
			dir *= -1;
	
	
}