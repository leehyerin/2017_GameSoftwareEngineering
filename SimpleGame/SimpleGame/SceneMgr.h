#pragma once
#include "Renderer.h"
#include "GameObject.h"
#define MAX_OBJECTS_COUNT 10


class SceneMgr
{
	GameObject* m_objects[MAX_OBJECTS_COUNT];
	int m_number;
public:
	SceneMgr();
	~SceneMgr();

	void DrawGameObject(void);

	void CreateGameObject(float x, float y);
	void CollisionTest();
	bool CollisionBox(float Xi, float Xj, float Yi, float Yj, float size);

	void Update(float currTime);
	GameObject* getObject(int n) const{ return m_objects[n]; }

};

