#include "stdafx.h"
#include "SceneMgr.h"

Renderer *g_Renderer = NULL;
DWORD g_Timer = 0;
DWORD g_Timer_Unit = 0;
DWORD g_Timer_Arrow = 0;

SceneMgr::SceneMgr()
{	
	g_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	g_Timer = timeGetTime();
	g_Timer_Unit = timeGetTime();
	g_Timer_Arrow = timeGetTime();

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	InitGameField();
}


SceneMgr::~SceneMgr()
{
	delete g_Renderer;
	g_Renderer = NULL;
}


void SceneMgr::CreateGameObject(float x, float y, int type)
{
	if (objectNum < MAX_OBJECTS_COUNT)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)  //빈 공간 찾는 루프
		{
			if (m_objects[i] == NULL)
			{
				m_objects[i] = new GameObject({ x, y, 0 }, OBJECT_CHARACTER, type); 
				++objectNum;
				break;
			}
		}
	}
}


void SceneMgr::CreateBullet()   //불렛 랜덤 생성 함수
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_buildings[0] != NULL)
		{
			POS pos;
			pos.x = m_buildings[i]->getposX();
			pos.y = m_buildings[i]->getposY();

			if (bulletNum < MAX_BULLETS_COUNT)
			{
				for (int j = 0; j < MAX_BULLETS_COUNT; ++j)  //빈 공간 찾는 루프
				{
					if (m_bullets[j] == NULL)
					{
						m_bullets[j] = new GameObject(pos, OBJECT_BULLET, m_buildings[i]->getTeam());
						++bulletNum;
						break;
					}
				}
			}
		}
	}
}


void SceneMgr::CreateArrow(GameObject& const object)
{
	POS pos;
	pos.x = object.getposX();
	pos.y = object.getposY();

	if (arrowNum < MAX_ARROWS_COUNT)
	{
		for (int i = 0; i < MAX_ARROWS_COUNT; ++i)  //빈 공간 찾는 루프
		{
			if (m_arrows[i] == NULL)
			{
				m_arrows[i] = new GameObject(pos, OBJECT_ARROW, object.getTeam());
				++arrowNum;
				break;
			}
		}
	}
}


void SceneMgr::InitGameField()
{
	float X = WINDOW_WIDTH / 3.33f;
	float Y = WINDOW_HEIGHT *0.375;

	m_buildings[0] = new GameObject({ -X, -Y, 0 } , OBJECT_BUILDING, TEAM_ALLY);  //0~2 남  ...아군
	m_buildings[1] = new GameObject({ 0, -Y-50, 0 }, OBJECT_BUILDING, TEAM_ALLY);
	m_buildings[2] = new GameObject({ X, -Y, 0 }, OBJECT_BUILDING, TEAM_ALLY);
	m_buildings[3] = new GameObject({ -X, Y, 0 }, OBJECT_BUILDING, TEAM_ENEMY);     //3~5 북
	m_buildings[4] = new GameObject({ 0, Y+50, 0 }, OBJECT_BUILDING, TEAM_ENEMY);
	m_buildings[5] = new GameObject({ X, Y, 0 }, OBJECT_BUILDING, TEAM_ENEMY);
	
	buldingNum = 6;
	objectNum = 0;   // 현재 존재하는 오브젝트 개수
	arrowNum = 0;
	bulletNum = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
		m_bullets[i] = NULL;
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
		m_arrows[i] = NULL;
}

void SceneMgr::DrawGameObject()
{
	GLuint m_texCharacter1 = g_Renderer->CreatePngTexture("./Resources/Blue_Slime.png");
	GLuint m_texCharacter2 = g_Renderer->CreatePngTexture("./Resources/Gold_Slime.png");
	GLuint texture = m_texCharacter1;
	//빌딩 png 그리기
	for (int i = 0; i < 6; ++i)
	{
		if (i > 2) texture = m_texCharacter2;

		if (m_buildings[i] != NULL)
		g_Renderer->DrawTexturedRect(m_buildings[i]->getposX(), m_buildings[i]->getposY(), m_buildings[i]->getposZ(), m_buildings[i]->getSize(),
			m_buildings[i]->getR(), m_buildings[i]->getG(), m_buildings[i]->getB(), m_buildings[i]->getAlpha(), texture);
	}
	//캐릭터 그리기
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)  
	{
		if (m_objects[i] != NULL)
			g_Renderer->DrawSolidRect(getObject(i)->getposX(), getObject(i)->getposY(), getObject(i)->getposZ(),
				getObject(i)->getSize(), getObject(i)->getR(), getObject(i)->getG(), getObject(i)->getB(), 1);

	}
	//불렛 그리기
	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
	{
		if (m_bullets[i] != NULL)
			g_Renderer->DrawSolidRect(getBullet(i)->getposX(), getBullet(i)->getposY(), getBullet(i)->getposZ(),
				getBullet(i)->getSize(), getBullet(i)->getR(), getBullet(i)->getG(), getBullet(i)->getB(), 1);
	}
	//애로우 그리기
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{
		if (m_arrows[i] != NULL)
			g_Renderer->DrawSolidRect(getArrow(i)->getposX(), getArrow(i)->getposY(), getArrow(i)->getposZ(),
				getArrow(i)->getSize(), getArrow(i)->getR(), getArrow(i)->getG(), getArrow(i)->getB(), 1);
	}
}


void SceneMgr::Update(float elapsedTime)
{
	CollisionTest();
    // 빌딩 업데이트
	for (int i = 0; i < MAX_BUILDING_COUNT; ++i)    
	{
		if (m_buildings[i] != NULL)
		{
			if (m_buildings[i]->getLife() <= 0 )   //life가 다 닳면 소멸
			{																		  
				delete m_buildings[i];
				m_buildings[i] = NULL;

				--buldingNum;
			}
			else
			{
				m_buildings[i]->Update(elapsedTime, m_buildings[i]->getType());
			}
		}
	}

	// 캐릭터 업데이트
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)    
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->getLife() <= 0 || m_objects[i]->getLifeTIme() <= 0.f)  //life가 다 닳거나 lifetime이 다 지나면 소멸
			{																		 //캐릭터
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
	//불렛 업데이트
	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)   
	{
		if (m_bullets[i] != NULL)
		{
			if (m_bullets[i]->getLife() <= 0 || m_bullets[i]->getLifeTIme() <= 0.f)
			{
				delete m_bullets[i];
				m_bullets[i] = NULL;			
				--bulletNum;  
			}
			else
				m_bullets[i]->Update(elapsedTime, OBJECT_BULLET);

		}
	}
	//애로우 업데이트
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)   
	{
		if (m_arrows[i] != NULL)
		{
			if (m_arrows[i]->getLife() <= 0 || m_arrows[i]->getLifeTIme() <= 0.f)
			{
				delete m_arrows[i];
				m_arrows[i] = NULL;				
				--arrowNum;		
			}
			else
				m_arrows[i]->Update(elapsedTime, OBJECT_ARROW);
		}
	}

	if (timeGetTime() - g_Timer > 10000.f)  // 1000이 1초
	{
		g_Timer = timeGetTime();		
		CreateBullet();                //불렛 생성
	}

	// 캐릭터 생성
	if (timeGetTime() - g_Timer_Unit > 5000.f)
	{
		g_Timer_Unit = timeGetTime();
		POS pos = { rand() % 500 - WINDOW_WIDTH / 2, max(rand() % 400,0) ,0 };
		CreateGameObject(pos.x, pos.y, TEAM_ENEMY);
	}

	if (timeGetTime() - g_Timer_Arrow > 3000.f)
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		g_Timer_Arrow = timeGetTime();
		if (m_objects[i] != NULL)
			CreateArrow(*m_objects[i]); //애로우 생성
	}
}


void SceneMgr::CollisionTest()
{
	float Xi, Yi, Xj, Yj;
	float sizei;
	int isCollision = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			Xi = m_objects[i]->getposX();
			Yi = m_objects[i]->getposY();
			sizei = m_objects[i]->getSize();

			for (int k = 0; k < MAX_BUILDING_COUNT; ++k)
			{
				if ((m_buildings[k] != NULL) && (m_buildings[k]->getTeam() != m_objects[i]->getTeam())) //빈공간이 아니면서 팀이 다를 때
				{
					if (CollisionBox(Xi, m_buildings[k]->getposX(), Yi, m_buildings[k]->getposY(), sizei, m_buildings[k]->getSize()))
					{   //빌딩과 캐릭터 충돌체크
						m_buildings[k]->minusLife(m_objects[i]->getLife());
						m_objects[i]->minusLife(m_objects[i]->getLife());
						std::cout << k << "번 빌딩 체력:" << m_buildings[k]->getLife() << "\n";
					}
				}
			}

			for (int j = 0; j < MAX_BULLETS_COUNT; ++j)
			{   //캐릭터와 불렛 충돌체크
				if (m_bullets[j] != NULL && m_bullets[j]->getTeam() != m_objects[i]->getTeam())
				{
					if (CollisionBox(Xi, m_bullets[j]->getposX(), Yi, m_bullets[j]->getposY(), sizei, m_bullets[j]->getSize()))
					{
						m_objects[i]->minusLife(m_bullets[j]->getLife());
						m_bullets[j]->setLife(0);
					}
				}
			}

			for (int j = 0; j < MAX_ARROWS_COUNT; ++j)
			{   //캐릭터와 애로우 충돌체크
				if (m_arrows[j] != NULL&&m_arrows[j]->getTeam() != m_objects[i]->getTeam())
				{
					if (CollisionBox(Xi, m_arrows[j]->getposX(), Yi, m_arrows[j]->getposY(), sizei, m_arrows[j]->getSize()))
					{
						if (m_arrows[j]->getLifeTIme() < 9998.f)
						{
							m_objects[i]->minusLife(m_arrows[j]->getLife());
							m_arrows[j]->setLife(0);
						}
					}
				}
			}
		}
	}

	for (int k = 0; k < MAX_BUILDING_COUNT; ++k)
	{	//빌딩과 애로우 충돌체크	
		if (m_buildings[k] != NULL)
		{
			Xi = m_buildings[k]->getposX();
			Yi = m_buildings[k]->getposY();
			sizei = m_buildings[k]->getSize();

			for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
			{
				if ((m_arrows[i] != NULL) && (m_arrows[i]->getTeam()!=m_buildings[k]->getTeam()))
				{
					

					if (CollisionBox(Xi, m_arrows[i]->getposX(), Yi, m_arrows[i]->getposY(), sizei, m_arrows[i]->getSize()))
					{
						m_buildings[k]->minusLife(m_arrows[i]->getLife());
						m_arrows[i]->setLife(0);
						std::cout << k << "번 빌딩 체력:" << m_buildings[k]->getLife() << "\n";
					}
				}
			}


			//빌딩과 불렛 충돌체크(PPT엔 없긴 함)
			for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
			{
				if ((m_bullets[i] != NULL) && (m_bullets[i]->getTeam() != m_buildings[k]->getTeam())) //빈공간이 아니면서 팀이 다를 때
				{
					if (CollisionBox(Xi, m_bullets[i]->getposX(), Yi, m_bullets[i]->getposY(), sizei, m_bullets[i]->getSize()))
					{
						m_buildings[k]->minusLife(m_bullets[i]->getLife());
						m_bullets[i]->setLife(0);
						std::cout << k << "번 빌딩 체력:" << m_buildings[k]->getLife() << "\n";

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