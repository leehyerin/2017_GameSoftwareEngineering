#include "stdafx.h"
#include "SceneMgr.h"

Renderer *g_Renderer = NULL;


SceneMgr::SceneMgr()
{	
	g_Renderer = new Renderer(500, 500);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	srand(time(NULL));
	m_number = 1;
	m_objects[0] = new GameObject (rand() % 500 - 250, rand() % 500 - 250, rand() % 500 - 250, 10, 1, 1, 1, 0);
	
	for (int i = 1 ; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
}


SceneMgr::~SceneMgr()
{
	delete g_Renderer;

}

void SceneMgr::CreateGameObject(float x, float y)
{
	if (m_number < MAX_OBJECTS_COUNT)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)  //빈 공간 찾는 루프
		{
			if (m_objects[i] == NULL)
			{
				m_objects[i] = new GameObject(x, y, 0, 10, 1, 1, 1, 0);
				++m_number;
				break;
			}
		}
	}
}

void SceneMgr::DrawGameObject()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (m_objects[i] != NULL)
			g_Renderer->DrawSolidRect(getObject(i)->getposX(), getObject(i)->getposY(), getObject(i)->getposZ(),
				getObject(i)->getSize(), getObject(i)->getR(), getObject(i)->getG(), getObject(i)->getB(), 0);
}

void SceneMgr::Update(float elapsedTime)
{
	CollisionTest();

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->getLife() == 0 || m_objects[i]->getLifeTIme() < 0.f)
			{
				delete m_objects[i];
				m_objects[i] = NULL;;
				
				--m_number;
			}
			else
				m_objects[i]->Update(elapsedTime);

		}
	}
}


void SceneMgr::CollisionTest()
{
	
	float Xi, Yi, Xj, Yj;
	float size;
	int isCollision = 0;

	for (int i = 0; i < m_number; ++i)
	{
		if (m_objects[i] != NULL)
		{
			Xi = m_objects[i]->getposX();
			Yi = m_objects[i]->getposY();
			size = m_objects[i]->getSize();
			isCollision = 0;

			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
			{
				if (m_objects[j] != NULL)
				{
					if (i != j)
					{
						Xj = m_objects[j]->getposX();
						Yj = m_objects[j]->getposY();

						if (CollisionBox(Xi, Xj, Yi, Yj, size))
							isCollision++;
					}
				}
			}
			if (isCollision > 0)
			{
				m_objects[i]->setB(0);
				m_objects[i]->setG(0);
				m_objects[i]->minusLife();
			}
			else
			{
				m_objects[i]->setB(1);
				m_objects[i]->setG(1);
			}
		}
	}
}


bool SceneMgr::CollisionBox(float Xi, float Xj, float Yi, float Yj, float size)
{
	if (Xi + size/2 < Xj - size/2)
		return false;
	if (Xi - size/2 > Xj + size/2)		
		return false;
	if (Yi + size/2 < Yj - size/2)		
		return false;
	if (Yi - size/2 > Yj + size/2)		
		return false;

	return true;

}