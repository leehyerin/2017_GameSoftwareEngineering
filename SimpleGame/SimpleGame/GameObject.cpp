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
		LifeTime = 500.f;   //라이프타임을 넣음
		 
		//타입에 따른 초기화
		switch (type)
		{
		case OBJECT_BUILDING:
			MaxLife = 500;
			Life = 500;
			Size = 100;
			Speed = 0;
			Level = 0.1f;
			R = 1.f, G = 1.f, B = 1.f, Alpha = 1.f;
			break;
		case OBJECT_CHARACTER:
			MaxLife = 20;
			Life = 20;
			Size = 30;
			Speed = 300;
			Level = 0.2f;
			if (team == TEAM_ALLY)
				R = 0, G = 0, B = 1.f, Alpha = 1.f;
			else
				R = 1.f, G = 0, B = 0, Alpha = 1.f;
			break;
		case OBJECT_BULLET:
			MaxLife = 10;
			Life = 10;
			Size = 10;
			Speed = 600;
			Level = 0.3f;
			if (team == TEAM_ALLY)
				R = 0, G = 0, B = 1.f, Alpha = 1.f;
			else
				R = 1.f, G = 0, B = 0, Alpha = 1.f;
			break;
		case OBJECT_ARROW:
			MaxLife = 10;
			Life = 10;
			Size = 4;
			Speed = 100;
			Level = 0.3f;
			if (team == TEAM_ALLY)
				R = 1.f, G = 1.f, B = 0, Alpha = 1.f;
			else
				R = 0.5f, G = 0.2f, B = 0.7f, Alpha = 1.f;
			break;
		default:
			break;
		}
}

void GameObject::Update(float elapsedTimeInSecond, int type)
{		
	posX = posX + dir * vX * Speed * elapsedTimeInSecond;   
	posY = posY + dir * vY * Speed * elapsedTimeInSecond;
		
	LifeTime -= elapsedTimeInSecond;
	Timer += elapsedTimeInSecond;

	++currImg;
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
			Life = 0.f; //소멸

		break;
	case OBJECT_ARROW:
		if (posX < -WINDOW_WIDTH / 2 || posX > WINDOW_WIDTH / 2 || posY < -WINDOW_HEIGHT / 2 || posY> WINDOW_HEIGHT / 2)
			Life = 0.f; //소멸
		break;
	default:
		break;
	}

}
