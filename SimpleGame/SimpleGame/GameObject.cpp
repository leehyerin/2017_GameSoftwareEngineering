#include "stdafx.h"
#include "GameObject.h"
using namespace std;


GameObject::~GameObject()
{
}

void GameObject::Update(float elapsedTime, int type)
{		
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	switch (type)
	{

	case OBJECT_CHARACTER:
		posX = posX + dir * speedX * (rand() % 1000 ) * elapsedTimeInSecond;
		posY = posY + dir * speedY * (rand() % 1000 ) * elapsedTimeInSecond;

		if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
			if (posX != posY)
				dir *= -1;
			else
				dir *= -1;

		lifeTime -= 1.f;

		break;

	case OBJECT_BUILDING:
		break;

	case OBJECT_BULLET:
		posX = posX + dir * speedX * 300 * elapsedTimeInSecond;
		posY = posY + dir * speedY * 300 * elapsedTimeInSecond;

		if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
			if (posX != posY)
				dir *= -1;
			else
				dir *= -1;

		lifeTime -= 0.5f;
		break;
	}

}