#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{	
	srand(time(NULL));
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = new GameObject (rand() % 500 - 250, rand() % 500 - 250, rand() % 500 - 250, 5, 1, 1, 1, 0);
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Update() 
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i]->Update();

}
