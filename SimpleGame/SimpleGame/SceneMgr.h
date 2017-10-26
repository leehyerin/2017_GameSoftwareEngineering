#pragma once
#include "GameObject.h"
#define MAX_OBJECTS_COUNT 50

extern float g_prevTime = 0.f;

class SceneMgr
{
	GameObject* m_objects[MAX_OBJECTS_COUNT];

public:
	SceneMgr();
	~SceneMgr();

	void Update(float currTime);
	GameObject* getObject(int n) const{ return m_objects[n]; }

};

