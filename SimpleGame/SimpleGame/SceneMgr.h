#pragma once
#include "GameObject.h"
#define MAX_OBJECTS_COUNT 50

class SceneMgr
{
	GameObject* m_objects[MAX_OBJECTS_COUNT];

public:
	SceneMgr();
	~SceneMgr();

	void Update();
	GameObject* getObject(int n) const{ return m_objects[n]; }

};

