#include "stdafx.h"
#include "SceneMgr.h"

Renderer *g_Renderer = NULL;
DWORD g_Timer_Unit = 0;
DWORD g_Timer_Arrow = 0;

SceneMgr::SceneMgr()
{	
	g_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	  
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
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)  //�� ���� ã�� ����
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


void SceneMgr::CreateBullet()   //�ҷ� ���� ���� �Լ�
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_buildings[i] != NULL)
		{
			POS pos;
			pos.x = m_buildings[i]->getposX();
			pos.y = m_buildings[i]->getposY();

			if (bulletNum < MAX_BULLETS_COUNT)
			{
				for (int j = 0; j < MAX_BULLETS_COUNT; ++j)  //�� ���� ã�� ����
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
		for (int i = 0; i < MAX_ARROWS_COUNT; ++i)  //�� ���� ã�� ����
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

	m_buildings[0] = new GameObject({ -X, -Y, 0 } , OBJECT_BUILDING, TEAM_ALLY);  //0~2 ��  ...�Ʊ�
	m_buildings[1] = new GameObject({ 0, -Y-25, 0 }, OBJECT_BUILDING, TEAM_ALLY);
	m_buildings[2] = new GameObject({ X, -Y, 0 }, OBJECT_BUILDING, TEAM_ALLY);
	m_buildings[3] = new GameObject({ -X, Y, 0 }, OBJECT_BUILDING, TEAM_ENEMY);     //3~5 ��
	m_buildings[4] = new GameObject({ 0, Y+25, 0 }, OBJECT_BUILDING, TEAM_ENEMY);
	m_buildings[5] = new GameObject({ X, Y, 0 }, OBJECT_BUILDING, TEAM_ENEMY);
	
	buldingNum = 6;
	objectNum = 0;   // ���� �����ϴ� ������Ʈ ����
	arrowNum = 0;
	bulletNum = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
		m_bullets[i] = NULL;
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
		m_arrows[i] = NULL;
}

void SceneMgr::DrawGameObject(float fElapsedTimeinSecond)
{
	cumulativeTime += fElapsedTimeinSecond;

	GLuint texBuilding1 = g_Renderer->CreatePngTexture("./Resources/Blue_Slime.png");
	GLuint texBuilding2 = g_Renderer->CreatePngTexture("./Resources/Gold_Slime.png");
	GLuint texCharacter = g_Renderer->CreatePngTexture("./Resources/bird_sprite.png");
	GLuint texParticle = g_Renderer->CreatePngTexture("./Resources/particle.png");
	GLuint bg_Texture = g_Renderer->CreatePngTexture("./Resources/Background.png");

	RGBA Red{ 1,0,0,1 };
	RGBA Blue{ 0,0,1,1 };
	RGBA Color;

	GLuint currtexBuilding = texBuilding1;

	//��� �׸���
	g_Renderer->DrawTexturedRect(0, 0, 0, 500, 1, 1, 1, 1, bg_Texture, BG_LEVEL);

	//���� ������ �׸���
	for (int i = 0; i < 6; ++i)
	{
		if (m_buildings[i] != NULL)
		{
			if (m_buildings[i]->getTeam() == TEAM_ALLY) Color = Blue; else Color = Red;
			auto ob = m_buildings[i];
			float gauge = (float)(ob->getLife()) / (float)(ob->getMaxLife());
			g_Renderer->DrawSolidRectGauge(ob->getposX(), ob->getposY() + ob->getSize()*0.65f, 0, ob->getSize(), HPBAR_HEIGHT,
				Color.R, Color.G, Color.B, Color.A, gauge, ob->getLevel());
		}
	}
	//���� png �׸���
	for (int i = 0; i < 6; ++i)
	{
		if (i > 2) currtexBuilding = texBuilding2;

		if (m_buildings[i] != NULL)
			g_Renderer->DrawTexturedRect(m_buildings[i]->getposX(), m_buildings[i]->getposY(), m_buildings[i]->getposZ(), m_buildings[i]->getSize(),
				m_buildings[i]->getR(), m_buildings[i]->getG(), m_buildings[i]->getB(), m_buildings[i]->getAlpha(), currtexBuilding, m_buildings[i]->getLevel());
	}
	//ĳ����, ������ �׸���
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			//��������
			auto ob= getObject(i); 
			float gauge = (float)(ob->getLife()) / (float)(ob->getMaxLife());

			g_Renderer->DrawSolidRectGauge(ob->getposX(), ob->getposY() + ob->getSize()*0.75f, 0, ob->getSize(), ob->getSize()*0.25f,
				ob->getR(), ob->getG(), ob->getB(), ob->getAlpha(), gauge, ob->getLevel());

			g_Renderer->DrawTexturedRectSeq(ob->getposX(), ob->getposY(), ob->getposZ(),
				ob->getSize(), ob->getR(), ob->getG(), ob->getB(), 1, texCharacter,
				 ob->getCurrImg(),0,4,4,getObject(i)->getLevel());
		}
	}
	
	//�ҷ� �׸���
	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
	{
		if (m_bullets[i] != NULL)
		{
			auto ob = getBullet(i);

			g_Renderer->DrawParticle(ob->getposX(), ob->getposY(), ob->getposZ(), ob->getSize(), ob->getR(), ob->getG(), ob->getB(), ob->getAlpha(),
				0, 1, texParticle, cumulativeTime);
		}
	}
	//�ַο� �׸���
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{
		if (m_arrows[i] != NULL)
			g_Renderer->DrawSolidRect(getArrow(i)->getposX(), getArrow(i)->getposY(), getArrow(i)->getposZ(),
				getArrow(i)->getSize(), getArrow(i)->getR(), getArrow(i)->getG(), getArrow(i)->getB(), 1, getArrow(i)->getLevel());
	}
}


void SceneMgr::Update(float elapsedTimeInSecond)
{
	CollisionTest();
	// ���� ������Ʈ
	for (int i = 0; i < MAX_BUILDING_COUNT; ++i)
	{
		if (m_buildings[i] != NULL)
		{
			if (m_buildings[i]->getLife() <= 0)   //life�� �� ��� �Ҹ�
			{
				delete m_buildings[i];
				m_buildings[i] = NULL;

				--buldingNum;
			}
			else
			{
				m_buildings[i]->Update(elapsedTimeInSecond, m_buildings[i]->getType());
			}
		}
	}

	// ĳ���� ������Ʈ
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->getLife() <= 0 || m_objects[i]->getLifeTIme() <= 0.f)  //life�� �� ��ų� lifetime�� �� ������ �Ҹ�
			{																		 //ĳ����
				delete m_objects[i];
				m_objects[i] = NULL;

				--objectNum;
			}
			else
			{
				m_objects[i]->Update(elapsedTimeInSecond, m_objects[i]->getType());
			}
		}
	}
	//�ҷ� ������Ʈ
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
				m_bullets[i]->Update(elapsedTimeInSecond, OBJECT_BULLET);
		}
	}
	//�ַο� ������Ʈ
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
				m_arrows[i]->Update(elapsedTimeInSecond, OBJECT_ARROW);
		}
	}


	// ĳ���� ����
	if (timeGetTime() - g_Timer_Unit > 3000.f)
	{
		g_Timer_Unit = timeGetTime();
		POS pos = { rand() % 500 - WINDOW_WIDTH / 2, max(rand() % 400,0) ,0 };
		CreateGameObject(pos.x, pos.y, TEAM_ENEMY);
	}

	//�ַο� ����
	if (timeGetTime() - g_Timer_Arrow > 3000.f)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			g_Timer_Arrow = timeGetTime();
			if (m_objects[i] != NULL)
				CreateArrow(*m_objects[i]);
		}
	}

	// �ҷ� ����
	if (timeGetTime() - g_Timer_Unit > 1000.f)
	{
		g_Timer_Unit = timeGetTime();
		CreateBullet();
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
				if ((m_buildings[k] != NULL) && (m_buildings[k]->getTeam() != m_objects[i]->getTeam())) //������� �ƴϸ鼭 ���� �ٸ� ��
				{
					if (CollisionBox(Xi, m_buildings[k]->getposX(), Yi, m_buildings[k]->getposY(), sizei, m_buildings[k]->getSize()))
					{   //������ ĳ���� �浹üũ
						m_buildings[k]->minusLife(m_objects[i]->getLife());
						m_objects[i]->setLife(0);
						std::cout << k << "�� ���� ü��:" << m_buildings[k]->getLife() << "\n";
					}
				}
			}

			for (int j = 0; j < MAX_BULLETS_COUNT; ++j)
			{   //ĳ���Ϳ� �ҷ� �浹üũ
				if (m_bullets[j] != NULL && m_bullets[j]->getTeam() != m_objects[i]->getTeam())
				{
					if (CollisionBox(Xi, m_bullets[j]->getposX(), Yi, m_bullets[j]->getposY(), sizei, m_bullets[j]->getSize()))
					{
						m_objects[i]->minusLife(m_bullets[j]->getLife());
						m_bullets[j]->setLife(0);
						std::cout<<"�ҷ�-ĳ���� �浹 ĳ���� ü��"<<m_objects[i]->getLife()<<"\n";
					}
				}
			}

			for (int j = 0; j < MAX_ARROWS_COUNT; ++j)
			{   //ĳ���Ϳ� �ַο� �浹üũ
				if (m_arrows[j] != NULL&&m_arrows[j]->getTeam() != m_objects[i]->getTeam())
				{
					if (CollisionBox(Xi, m_arrows[j]->getposX(), Yi, m_arrows[j]->getposY(), sizei, m_arrows[j]->getSize()))
					{
						if (m_arrows[j]->getLifeTIme() < 9998.f)
						{
							m_objects[i]->minusLife(m_arrows[j]->getLife());
							m_arrows[j]->setLife(0);
							std::cout << "�ҷ�-�ַο� �浹 ĳ���� ü��" << m_objects[i]->getLife() << "\n";

						}
					}
				}
			}
		}
	}

	for (int k = 0; k < MAX_BUILDING_COUNT; ++k)
	{	//������ �ַο� �浹üũ	
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
						std::cout << k << "�� ���� ü��:" << m_buildings[k]->getLife() << "\n";
					}
				}
			}


			//������ �ҷ� �浹üũ
			for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
			{
				if ((m_bullets[i] != NULL) && (m_bullets[i]->getTeam() != m_buildings[k]->getTeam())) //������� �ƴϸ鼭 ���� �ٸ� ��
				{
					if (CollisionBox(Xi, m_bullets[i]->getposX(), Yi, m_bullets[i]->getposY(), sizei, m_bullets[i]->getSize()))
					{
						m_buildings[k]->minusLife(m_bullets[i]->getLife());
						m_bullets[i]->setLife(0);
						std::cout << k << "�� ���� ü��:" << m_buildings[k]->getLife() << "\n";

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