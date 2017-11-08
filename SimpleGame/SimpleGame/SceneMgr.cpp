#include "stdafx.h"
#include "SceneMgr.h"

Renderer *g_Renderer = NULL;
DWORD g_Timer = 0;

SceneMgr::SceneMgr()
{	
	g_Renderer = new Renderer(500, 500);
	g_Timer = timeGetTime();

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	
	m_objects[0] = new GameObject(0, 0, 0, 50, 1, 1, 0, 0, OBJECT_BUILDING);   //오브젝트 0번은 빌딩
	objectNum = 1;   // 현재 존재하는 오브젝트 개수

	for (int i = 1; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;

	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
		m_bullets[i] = NULL;
	
	//CreateBullet();

}


SceneMgr::~SceneMgr()
{
	delete g_Renderer;
	g_Renderer = NULL;

}


void SceneMgr::CreateGameObject(float x, float y)
{
	if (objectNum < MAX_OBJECTS_COUNT)
	{
		for (int i = 1; i < MAX_OBJECTS_COUNT; ++i)  //빈 공간 찾는 루프
		{
			if (m_objects[i] == NULL)
			{
				m_objects[i] = new GameObject(x, y, 0, 10, 1, 1, 1, 0, OBJECT_CHARACTER);
				++objectNum;
				break;
			}
		}
	}
}


void SceneMgr::CreateBullet()   //불렛 랜덤 생성 함수
{
	if (m_objects[0] != NULL)
	{
		float posX, posY;
		posX = m_objects[0]->getposX();
		posY = m_objects[0]->getposY();

		if (bulletNum < MAX_BULLETS_COUNT)
		{
			for (int i = 0; i < MAX_BULLETS_COUNT; ++i)  //빈 공간 찾는 루프
			{
				if (m_bullets[i] == NULL)
				{
					m_bullets[i] = new GameObject(posX, posY, 0, 5, 1, 0, 0, 0, OBJECT_BULLET);
					++bulletNum;
					break;
				}
			}
		}
	}

}


void SceneMgr::DrawGameObject()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			g_Renderer->DrawSolidRect(getObject(i)->getposX(), getObject(i)->getposY(), getObject(i)->getposZ(),
				getObject(i)->getSize(), getObject(i)->getR(), getObject(i)->getG(), getObject(i)->getB(), 0);
	}

	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
	{
		if (m_bullets[i] != NULL)
			g_Renderer->DrawSolidRect(getBullet(i)->getposX(), getBullet(i)->getposY(), getBullet(i)->getposZ(),
				getBullet(i)->getSize(), getBullet(i)->getR(), getBullet(i)->getG(), getBullet(i)->getB(), 0);
	}
}


void SceneMgr::Update(float elapsedTime)
{
	CollisionTest();

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)    // 빌딩과 게임오브젝트 업데이트
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->getLife() == 0 || m_objects[i]->getLifeTIme() < 0.f)   //life가 다 닳거나 lifetime이 다 지나면 소멸
			{
				delete m_objects[i];
				m_objects[i] = NULL;

				--objectNum;
			}
			else
			{
				m_objects[i]->Update(elapsedTime, m_objects[i]->getType());

			}
		}
	}

	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)   //불렛 업데이트
	{
		if (m_bullets[i] != NULL)
		{
			m_bullets[i]->Update(elapsedTime, m_bullets[i]->getType());
		}
	}

	if (timeGetTime() - g_Timer > 500)  // 1000이 1초
	{
		g_Timer = timeGetTime();		
		CreateBullet();
	}
}


void SceneMgr::CollisionTest()
{
	
	float Xi, Yi, Xj, Yj;
	float sizei;
	int isCollision = 0;

	for (int i = 1; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			Xi = m_objects[i]->getposX();
			Yi = m_objects[i]->getposY();
			sizei = m_objects[i]->getSize();

			if (m_objects[0] != NULL)
			{
				if (CollisionBox(Xi, m_objects[0]->getposX(), Yi, m_objects[0]->getposY(), sizei, m_objects[0]->getSize()))
				{   //빌딩과 오브젝트 충돌체크
					m_objects[0]->minusLife(m_objects[i]->getLife());
					m_objects[i]->minusLife(m_objects[i]->getLife());
				}

				for (int j = 0; j < MAX_BULLETS_COUNT; ++j)
				{   //오브젝트와 불렛 충돌체크
					if (m_bullets[j] != NULL)
					{
						if (CollisionBox(Xi, m_bullets[j]->getposX(), Yi, m_bullets[j]->getposY(), sizei, m_bullets[j]->getSize()))
						{
							m_objects[i]->minusLife(m_bullets[j]->getLife());
							//m_bullets[j]->minusLife(m_objects[j]->getLife());   //불렛 소멸
							
							delete m_bullets[j];
							m_bullets[j] = NULL;
						}
					}
				}
			}
		}
	}


}


bool SceneMgr::CollisionBox(float Xi, float Xj, float Yi, float Yj, float sizei, float sizej)
{
	if (Xi + sizei/2 < Xj - sizej/2)
		return false;
	if (Xi - sizei/2 > Xj + sizej/2)		
		return false;
	if (Yi + sizei/2 < Yj - sizej/2)		
		return false;
	if (Yi - sizei/2 > Yj + sizej/2)		
		return false;

	return true;

}