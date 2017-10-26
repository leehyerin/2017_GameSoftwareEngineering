#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{	
	srand(time(NULL));
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = new GameObject (rand() % 500 - 250, rand() % 500 - 250, rand() % 500 - 250, 20, 1, 1, 1, 0);
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Update(float currTime)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{	
		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (i != j)
			{
				float Xi = m_objects[i]->getposX();
				float Yi = m_objects[i]->getposY();
				float Xj = m_objects[j]->getposX();
				float Yj = m_objects[j]->getposY();
				if (Xi - 5 <= Xj + 5 || Xi + 5 <= Xj - 5)
						if (Yi - 5 <= Yj + 5 || Yi + 5 <= Yj - 5)
							{
								m_objects[i]->setB(0);
								m_objects[i]->setG(0);
								m_objects[j]->setB(0);
								m_objects[j]->setG(0);
							}
			}

			m_objects[i]->Update(currTime);
		}
	}

}
