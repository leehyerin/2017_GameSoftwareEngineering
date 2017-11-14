#include "stdafx.h"
#include "GameObject.h"
using namespace std;


void GameObject::Update(float elapsedTime, int type)
{		
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	switch (type)
	{
	case OBJECT_CHARACTER:
		posX = posX + dir * speedX * 300 * elapsedTimeInSecond;   //(rand() % 1000 )
		posY = posY + dir * speedY * 300 * elapsedTimeInSecond;

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
			life = 0.f; //¼Ò¸ê

		lifeTime -= 1.f;
		break;
	case OBJECT_ARROW:
		posX = posX + dir * speedX * 100 * elapsedTimeInSecond;
		posY = posY + dir * speedY * 100 * elapsedTimeInSecond;

		if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
			life = 0.f; //¼Ò¸ê

		lifeTime -= 1.f;

		break;
	default:
		break;
	}

}
