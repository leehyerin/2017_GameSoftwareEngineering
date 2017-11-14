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

	
	m_objects[0] = new GameObject(0, 0, 0, 50, 1, 1, 0, 0, OBJECT_BUILDING);   //������Ʈ 0���� ����
	objectNum = 1;   // ���� �����ϴ� ������Ʈ ����
	arrowNum = 0;

	for (int i = 1; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;

	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
		m_bullets[i] = NULL;
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
		m_arrows[i] = NULL;
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
		for (int i = 1; i < MAX_OBJECTS_COUNT; ++i)  //�� ���� ã�� ����
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


void SceneMgr::CreateBullet()   //�ҷ� ���� ���� �Լ�
{
	if (m_objects[0] != NULL)
	{
		float posX, posY;
		posX = m_objects[0]->getposX();
		posY = m_objects[0]->getposY();

		if (bulletNum < MAX_BULLETS_COUNT)
		{
			for (int i = 0; i < MAX_BULLETS_COUNT; ++i)  //�� ���� ã�� ����
			{
				if (m_bullets[i] == NULL)
				{
					m_bullets[i] = new GameObject(posX, posY, 0, 2, 1, 0, 0, 0, OBJECT_BULLET);
					++bulletNum;
					break;
				}
			}
		}
	}
}


void SceneMgr::CreateArrow(GameObject& object)
{
	float posX, posY;
	posX = object.getposX();
	posY = object.getposY();

	if (arrowNum < MAX_ARROWS_COUNT)
	{
		for (int i = 0; i < MAX_ARROWS_COUNT; ++i)  //�� ���� ã�� ����
		{
			if (m_arrows[i] == NULL)
			{
				m_arrows[i] = new GameObject(posX, posY, 0, 2, 0, 5, 0, 0, OBJECT_ARROW);
				++arrowNum;
				break;
			}
		}
	}
}


void SceneMgr::DrawGameObject()
{
	auto m_texCharacter = g_Renderer->CreatePngTexture("./Resources/Slime.png");
	if (m_objects[0] != NULL)
		g_Renderer->DrawTexturedRect(m_objects[0]->getposX(), m_objects[0]->getposY(), m_objects[0]->getposZ(), m_objects[0]->getSize(),
			m_objects[0]->getR(), m_objects[0]->getG(), m_objects[0]->getB(), m_objects[0]->getAlpha(), m_texCharacter);


	for (int i = 1; i < MAX_OBJECTS_COUNT; ++i)  
	{
		if (m_objects[i] != NULL)
			g_Renderer->DrawSolidRect(getObject(i)->getposX(), getObject(i)->getposY(), getObject(i)->getposZ(),
				getObject(i)->getSize(), getObject(i)->getR(), getObject(i)->getG(), getObject(i)->getB(), 1);

	}

	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
	{
		if (m_bullets[i] != NULL)
			g_Renderer->DrawSolidRect(getBullet(i)->getposX(), getBullet(i)->getposY(), getBullet(i)->getposZ(),
				getBullet(i)->getSize(), getBullet(i)->getR(), getBullet(i)->getG(), getBullet(i)->getB(), 1);
	}

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

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)    // ������ ���ӿ�����Ʈ ������Ʈ
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->getLife() <= 0 || m_objects[i]->getLifeTIme() < 0.f)   //life�� �� ��ų� lifetime�� �� ������ �Ҹ�
			{																		 //����,ĳ���� �ش�
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

	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)   //�ҷ� ������Ʈ
	{
		if (m_bullets[i] != NULL)
		{
			if (m_bullets[i]->getLife() <= 0 || m_bullets[i]->getLifeTIme() < 0.f)
			{
				delete m_bullets[i];
				m_bullets[i] = NULL;			
				--bulletNum;         
			}
			else
				m_bullets[i]->Update(elapsedTime, OBJECT_BULLET);
		}
	}

	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)   //�ַο� ������Ʈ
	{
		if (m_arrows[i] != NULL)
		{
			if (m_arrows[i]->getLife() <= 0 || m_arrows[i]->getLifeTIme() < 0.f)
			{
				delete m_arrows[i];
				m_arrows[i] = NULL;				
				--arrowNum;		
			}
			else
				m_arrows[i]->Update(elapsedTime, OBJECT_ARROW);
		}
	}
	  //������Ʈ�� �����ϴ� �� �������� �� �� ���� �� ����


	if (timeGetTime() - g_Timer > 500)  // 1000�� 1��
	{
		g_Timer = timeGetTime();		
		CreateBullet();                //�ҷ� ����

		for (int i = 1; i < MAX_OBJECTS_COUNT; ++i)
		{
			if (m_objects[i] != NULL)
				CreateArrow(*m_objects[i]); //�ַο� ����
		}
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
				{   //������ ������Ʈ �浹üũ
					m_objects[0]->minusLife(m_objects[i]->getLife());
					m_objects[i]->minusLife(m_objects[i]->getLife());
					std::cout <<  "���� ü��:"<< m_objects[0]->getLife()<<"\n";
				}

				for (int j = 0; j < MAX_BULLETS_COUNT; ++j)
				{   //������Ʈ�� �ҷ� �浹üũ
					if (m_bullets[j] != NULL)
					{
						if (CollisionBox(Xi, m_bullets[j]->getposX(), Yi, m_bullets[j]->getposY(), sizei, m_bullets[j]->getSize()))
						{
							m_objects[i]->minusLife(m_bullets[j]->getLife());
							m_bullets[j]->setLife(0);
						}
					}
				}
			
				for (int j = 0; j < MAX_ARROWS_COUNT; ++j)
				{   //������Ʈ�� �ַο� �浹üũ
					if (m_arrows[j] != NULL)
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
	}

	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{	//������ �ַο� �浹üũ
		if (m_arrows[i] != NULL)
		{
			Xi = m_arrows[i]->getposX();
			Yi = m_arrows[i]->getposY();
			sizei = m_arrows[i]->getSize();
			if (CollisionBox(Xi, m_objects[0]->getposX(), Yi, m_objects[0]->getposY(), sizei, m_objects[0]->getSize()))
			{
				m_objects[0]->minusLife(m_arrows[i]->getLife());
				m_arrows[i]->setLife(0);
				std::cout << "���� ü��:" << m_objects[0]->getLife() << "\n";

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