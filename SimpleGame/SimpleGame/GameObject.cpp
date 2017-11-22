#include "stdafx.h"
#include "GameObject.h"
//#include "Defines.cpp"
using namespace std;


GameObject::GameObject(POS pos, int type, int team)
{
		posX = pos.x;
		posY = pos.y;
		posZ = pos.z;
		Type = type;
		Team = team;

		//방향는 랜덤으로 하고싶었어..
		vX = (float)((rand() % 100) - 50.f) / 100.f;
		vY = (float)((rand() % 100) - 50.f) / 100.f;

		dir = 1;
		lifeTime = 500.f;   //라이프타임을 넣음
		 
		//타입에 따른 초기화
		switch (type)
		{
		case OBJECT_BUILDING:
			life = 500;
			Size = 100;
			Speed = 0;
			break;
		case OBJECT_CHARACTER:
			life = 20;
			Size = 10;
			Speed = 300;
			if (team == TEAM_ALLY)
				R = 0, G = 0, B = 1.f, Alpha = 1.f;
			else
				R = 1.f, G = 0, B = 0, Alpha = 1.f;
			break;
		case OBJECT_BULLET:
			life = 10;
			Size = 2;
			Speed = 600;
			if (team == TEAM_ALLY)
				R = 0, G = 0, B = 1.f, Alpha = 1.f;
			else
				R = 1.f, G = 0, B = 0, Alpha = 1.f;
			break;
		case OBJECT_ARROW:
			life = 10;
			Size = 2;
			Speed = 100;
			if (team == TEAM_ALLY)
				R = 1.f, G = 1.f, B = 0, Alpha = 1.f;
			else
				R = 0.5f, G = 0.2f, B = 0.7f, Alpha = 1.f;
			break;
		default:
			break;
		}
}

void GameObject::Update(float elapsedTime, int type)
{		
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	posX = posX + dir * vX * Speed * elapsedTimeInSecond;   
	posY = posY + dir * vY * Speed * elapsedTimeInSecond;
		
	lifeTime -= elapsedTimeInSecond;

	switch (type)
	{
	case OBJECT_CHARACTER:
		if (posX < -WINDOW_WIDTH / 2 || posX > WINDOW_WIDTH / 2 || posY < -WINDOW_HEIGHT / 2 || posY> WINDOW_HEIGHT / 2)
		{
			if (posX != posY)
				dir *= -1;
			else
				dir *= -1; 
		}
		break;
	case OBJECT_BULLET:
		if (posX < -WINDOW_WIDTH / 2 || posX > WINDOW_WIDTH / 2 || posY < -WINDOW_HEIGHT / 2 || posY> WINDOW_HEIGHT / 2)
			life = 0.f; //소멸
		break;
	case OBJECT_ARROW:
		if (posX < -WINDOW_WIDTH / 2 || posX > WINDOW_WIDTH / 2 || posY < -WINDOW_HEIGHT / 2 || posY> WINDOW_HEIGHT / 2)
			life = 0.f; //소멸
		break;
	default:
		break;
	}

}
