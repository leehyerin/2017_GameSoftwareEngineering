#pragma once
#include "Renderer.h"
#include "GameObject.h"
#define MAX_BUILDING_COUNT 6
#define MAX_OBJECTS_COUNT 20
#define MAX_BULLETS_COUNT 50
#define MAX_ARROWS_COUNT 200000

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
	
	float cumulativeTime = 0.f;
public:
	SceneMgr();
	~SceneMgr();

	void InitGameField();
	void DrawGameObject(float fElapsedTimeinSecond);

	void CreateGameObject(float x, float y, int type);
	void CreateBullet();
	void CreateArrow( GameObject& const);
	void CollisionTest();
	bool CollisionBox(float Xi, float Xj, float Yi, float Yj, float size, float sizej);

	void Update(float currTime);
	GameObject* getObject(int n) const{ return m_objects[n]; }
	GameObject* getBullet(int n) const { return m_bullets[n]; }
	GameObject* getArrow(int n) const { return m_arrows[n]; }

};

