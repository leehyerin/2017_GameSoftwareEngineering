#include "stdafx.h"
#include "GameObject.h"
using namespace std;

GameObject::GameObject(POS pos, int type, int team, int kind)
{
		posX = pos.x;
		posY = pos.y;
		posZ = pos.z;
		Type = type;
		Team = team;
		Kind = kind;

		vX = 0.f;

		if (type == TEAM_ALLY)
			vY = 1.f;
		else
			vY = -1.f;


		LifeTime = 5000.f;   //라이프타임을 넣음
		 
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
			if (Kind == CHAR_KIND_Purple_TANK)
			{
				MaxLife = 100;
				Life = 100;
			}
			else
			{
				MaxLife = 20;
				Life = 20;
			}

			if (Kind == CHAR_KIND_YELLOW_BIG)		 Size = 60;
			else if (Kind == CHAR_KIND_Purple_TANK) Size = 45;
			else Size = 30;


			if(Kind== CHAR_KIND_BLUE_SPEEDY)			Speed = 200;
			else Speed = 100;

			Level = 0.2f;
			dir = 1;
			if (vX > 0.f)
			{
				float gradient = vY / vX;
				if (gradient > 1.25f || gradient < -1.25f)   //기울기
					charDIR = CHAR_UP;
				else
					charDIR = CHAR_RIGHT;
				printf("%f\n",gradient);
			}
			else
			{
				float gradient = vY / vX;
				if (gradient > 1.25f || gradient < -1.25f)  //기울기
					charDIR = CHAR_DOWN;
				else
					charDIR = CHAR_LEFT;
				printf("%f\n", gradient);
			}
			if (team == TEAM_ALLY)
				R = 0, G = 0, B = 1.f, Alpha = 1.f, dir = -1;
			else
				R = 1.f, G = 1.f, B = 0, Alpha = 1.f, dir = 1;
			break;
		case OBJECT_BULLET:
			MaxLife = 10;
			Life = 10;
			Size = 50;
			Speed = 300;
			Level = 0.3f;
			if (team == TEAM_ALLY)
			{
				R = 0, G = 0, B = 1.f, Alpha = 1.f;
				dir = -1.f;				
				vY = -1.f;
			}
			else
			{
				R = 1.f, G = 1.f, B = 0, Alpha = 1.f;
				dir = 1.f;
				vY = -1.f;
			}
			break;
		case OBJECT_ARROW:
			MaxLife = 10;
			Life = 10;

			if (Kind == CHAR_KIND_YELLOW_BIG)  Size = 20;
			else Size = 5;

			Speed = 500;
			Level = 0.3f;
			dir = 1;
			if (team == TEAM_ALLY)
				R = 0.f, G = 0, B = 1, Alpha = 1.f,dir=-1;
			else
				R = 1.f, G = 1.f, B = 0.f, Alpha = 1.f,dir=1;
			break;
		default:
			break;
		}
}

void GameObject::Update(float elapsedTimeInSecond, int type)
{			
	LifeTime -= elapsedTimeInSecond;
	cumulatedTime += elapsedTimeInSecond;

	switch (type)
	{
	case OBJECT_CHARACTER:
		posX = posX + dir * vX * Speed * elapsedTimeInSecond;
		posY = posY + dir * vY * Speed * elapsedTimeInSecond;

		if (posX < -WINDOW_WIDTH / 2 || posX > WINDOW_WIDTH / 2 || posY < -WINDOW_HEIGHT / 2 +100 || posY> WINDOW_HEIGHT / 2)
		{
			if (posX != posY)
				dir *= -1;
			else
				dir *= -1;

			switch (charDIR)
			{
			case CHAR_LEFT:
				charDIR = CHAR_RIGHT;
				break;
			case CHAR_RIGHT:
				charDIR = CHAR_LEFT;
				break;
			case CHAR_UP:
				charDIR = CHAR_DOWN;
				break;
			case CHAR_DOWN:
				charDIR = CHAR_UP;
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_BULLET:
		posX = posX + dir * vX * Speed * elapsedTimeInSecond;
		posY = posY + dir * vY * Speed * elapsedTimeInSecond;

		if (posX < -WINDOW_WIDTH / 2 || posX > WINDOW_WIDTH / 2 || posY < -WINDOW_HEIGHT / 2 + 100 || posY> WINDOW_HEIGHT / 2 + 100)
			Life = 0.f; //소멸
		Alpha -= 0.001*cumulatedTime;
		if (Alpha <= 0)
			Life = 0.f;
		break;
	case OBJECT_ARROW:
		posX = posX + dir * vX * Speed * elapsedTimeInSecond;
		posY = posY + dir * vY * Speed * elapsedTimeInSecond;
		if (posX < -WINDOW_WIDTH / 2 || posX > WINDOW_WIDTH / 2 || posY < -WINDOW_HEIGHT / 2 + 100 || posY> WINDOW_HEIGHT / 2 + 100)
			Life = 0.f; //소멸
		break;
	default:
		break;
	}
}
