#pragma once

#define OBJECT_BUILDING		0
#define OBJECT_CHARACTER	1	
#define OBJECT_BULLET		2
#define OBJECT_ARROW		3

#define MAX_ARROWS_COUNT 30

class GameObject
{
private:
	float posX;
	float posY;
	float posZ;
	float size;
	float R, G, B;
	float Alpha;
	float speedX;
	float speedY;
	int dir;
	int life;
	int lifeTime;
	int type;

public:
	float getposX() { return posX; }
	float getposY() { return posY; }
	float getposZ() { return posZ; }
	float getSize() { return size; }
	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float getAlpha() { return Alpha; }
	void minusLife(int minusValue) { life -= minusValue; }
	int getType() { return type; }
	int getLife() { return life; }
	int getLifeTIme() { return lifeTime; }
	
	
	/*ArrowObject* m_arrows[MAX_ARROWS_COUNT];*/

public:
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a, int type) 
		: posX(x), posY(y), posZ(z), size(size), R(r), G(g), B(b), Alpha(a) ,type(type)
	{
		
		speedX = (float)((rand() %100) - 50.f)/100.f;
		speedY = (float)((rand() %100) - 50.f)/100.f;
		

		dir = 1;		
		lifeTime = 10000.f;
		int arrowNum = 0;

		//라이프 정하기
		if (type == OBJECT_BUILDING)
			life = 600;
		else if (type == OBJECT_CHARACTER)
			life = 60;
		else
			life = 20;

		/*for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
			m_arrows[i] = NULL;*/

	}

	void Update(float elapsedTIme,int type);
	~GameObject();

};

//
//class ArrowObject :public GameObject
//{
//public:
//	int arrowNum;
//	int getArrowNum() { return arrowNum; }
//	void plusArrow(int plusValue) { arrowNum += plusValue; }
//
//	ArrowObject();
//	void Update(float elapsedTIme);
//};