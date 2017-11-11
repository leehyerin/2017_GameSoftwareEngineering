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
		posX = posX + dir * speedX * 300 * elapsedTimeInSecond;   //(rand() % 1000 )
		posY = posY + dir * speedY * 300 * elapsedTimeInSecond;

		if (posX < -250 || posX > 250 || posY < -250 || posY > 250)
			if (posX != posY)
				dir *= -1;
			else
				dir *= -1;

		lifeTime -= 1.f;

		/*if (arrowNum != 0)
		{
			for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
				m_arrows[i]->Update(elapsedTime);
		}*/
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

//
//ArrowObject::ArrowObject() 
//{
//	posX = posX;
//
//
//
//	int posX, posY;
//
//	posX = m_objects[index]->getposX();
//	posY = m_objects[index]->getposY();
//
//	if (m_objects[index]->getArrowNum() < MAX_ARROWS_COUNT)
//	{
//		for (int j = 0; j < MAX_ARROWS_COUNT; ++j)  //빈 공간 찾는 루프
//		{
//			if (m_objects[index]->m_arrows[j] == NULL)
//			{
//				m_objects[index]->m_arrows[j] = new GameObject(posX, posY, 0, 2, 0, 1, 0, 0, OBJECT_ARROW);
//				m_objects[index]->plusArrow(1);
//				break;
//			}
//		}
//	}
//
//
//}
//
//
//void ArrowObject::Update(float elapsedTIme)
//{
//	// 시간마다
//	posX = posX + dir * speedX * 100 * elapsedTimeInSecond;
//	posY = posY + dir * speedY * 100 * elapsedTimeInSecond;
//
//}