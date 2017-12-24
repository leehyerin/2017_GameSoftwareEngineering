#pragma once
#include "Renderer.h"
#include "GameObject.h"
#include "Sound.h"

#define MAX_BUILDING_COUNT 6
#define MAX_OBJECTS_COUNT 20
#define MAX_BULLETS_COUNT 50
#define MAX_ARROWS_COUNT 20000


class SceneMgr
{
	GameObject* m_buildings[6];
	GameObject* m_objects[MAX_OBJECTS_COUNT];
	GameObject* m_bullets[MAX_BULLETS_COUNT];
	GameObject* m_arrows[MAX_ARROWS_COUNT];

	int buldingNum;
	int objectNum;
	int bulletNum;
	int arrowNum;
	
	int ALLYbuildingActive = KING_INACT;
	int ENEMYbuildingActive = KING_INACT;
	float cumulatedTime = 0.f;
	int currImg = 0;
	float coolTimer = 0;
	int Energy = 0;

	int ImgIdx = 0;
	int widthImg = 0;
	int heightImg = 0;

	Sound* m_BG = new Sound();
	Sound* m_Coll = new Sound();
	int soundBG;
	int soundCollision;

	float ETimer=0;
	int fever=0;
	
	GLuint texBuildingALLY;
	GLuint texBuildingKINGALLY;
	GLuint texBuildingENEMY;
	GLuint texBuildingKINGENEMY;


	GLuint texYellowSprite, texBlueSprite, texOrangeSprite, texPurpleSprite;  //스프라이트
	GLuint texYellow, texBlue,texOrange, texPurple; //덱
	GLuint texParticle, texBullet;
	GLuint bg_Texture;


public:
	SceneMgr();
	~SceneMgr();

	void InitGameField();
	void DrawGameObject(float fElapsedTimeinSecond);

	void CreateGameObject(float x, float y, int type, int kind);
	void CreateBullet();
	void CreateArrow( GameObject& const);
	void CollisionTest();
	bool CollisionBox(float Xi, float Xj, float Yi, float Yj, float size, float sizej);

	void Update(float currTime);

	GameObject* getObject(int n) const{ return m_objects[n]; }
	GameObject* getBullet(int n) const { return m_bullets[n]; }
	GameObject* getArrow(int n) const { return m_arrows[n]; }
};