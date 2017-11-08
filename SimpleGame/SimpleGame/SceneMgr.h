#pragma once
#include "Renderer.h"
#include "GameObject.h"
#define MAX_OBJECTS_COUNT 20
#define MAX_BULLETS_COUNT 50

class SceneMgr
{
	GameObject* m_objects[MAX_OBJECTS_COUNT];
	GameObject* m_bullets[MAX_BULLETS_COUNT];
	int objectNum;
	int bulletNum;
public:
	SceneMgr();
	~SceneMgr();

	void DrawGameObject(void);

	void CreateGameObject(float x, float y);
	void CreateBullet();
	void CollisionTest();
	bool CollisionBox(float Xi, float Xj, float Yi, float Yj, float size, float sizej);

	void Update(float currTime);
	GameObject* getObject(int n) const{ return m_objects[n]; }
	GameObject* getBullet(int n) const { return m_bullets[n]; }

};

