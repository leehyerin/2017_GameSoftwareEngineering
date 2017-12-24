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


void SceneMgr::CreateGameObject(float x, float y, int team, int kind)
{
	if (objectNum < MAX_OBJECTS_COUNT)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)  //빈 공간 찾는 루프
		{
			if (m_objects[i] == NULL)
			{
				//if(team==TEAM_ALLY)
				switch (kind)
				{
				case CHAR_KIND_Orange_DOZEN:
					if (Energy > 1)
					{
						m_objects[i] = new GameObject({ x + 30, y, 0 }, OBJECT_CHARACTER, team, kind);
						m_objects[i + 1] = new GameObject({ x, y, 0 }, OBJECT_CHARACTER, team, kind);
						m_objects[i + 2] = new GameObject({ x - 30, y, 0 }, OBJECT_CHARACTER, team, kind);

						objectNum += 3;
						Energy -= 1;
					}
					break;
				case CHAR_KIND_YELLOW_BIG:
					if (Energy > 2)
					{
						m_objects[i] = new GameObject({ x, y, 0 }, OBJECT_CHARACTER, team, kind);
						++objectNum;
						Energy -= 2;
					}
					break;
				case CHAR_KIND_Purple_TANK:
					if (Energy > 4)
					{
						m_objects[i] = new GameObject({ x, y, 0 }, OBJECT_CHARACTER, team, kind);
						++objectNum;
						Energy -= 4;
					}
					break;
				case CHAR_KIND_BLUE_SPEEDY:
					if (Energy > 3)
					{
						m_objects[i] = new GameObject({ x, y, 0 }, OBJECT_CHARACTER, team, kind);
						++objectNum;
						Energy -= 3;
					}
					break;
				default:
					break;
				}

			}
		}
	}
}


void SceneMgr::CreateBullet()   //불렛 랜덤 생성 함수
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_buildings[i] != NULL)
		{
			if (ALLYbuildingActive == KING_INACT) if (i == 1) continue;
			if (ENEMYbuildingActive == KING_INACT) if (i ==4 )  continue;

			POS pos;
			pos.x = m_buildings[i]->getposX();
			pos.y = m_buildings[i]->getposY();

			if (bulletNum < MAX_BULLETS_COUNT)
			{
				for (int j = 0; j < MAX_BULLETS_COUNT; ++j)  //빈 공간 찾는 루프
				{
					if (m_bullets[j] == NULL)
					{
						m_bullets[j] = new GameObject(pos, OBJECT_BULLET, m_buildings[i]->getTeam(), m_buildings[i]->getKind());
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
				m_arrows[i] = new GameObject(pos, OBJECT_ARROW, object.getTeam(), object.getKind());
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

	m_buildings[0] = new GameObject({ -X, -Y + 50, 0 }, OBJECT_BUILDING, TEAM_ALLY, 0);  //0~2 남  ...아군
	m_buildings[1] = new GameObject({ 0, -Y-25+50, 0 }, OBJECT_BUILDING, TEAM_ALLY, 0);
	m_buildings[2] = new GameObject({ X, -Y+50, 0 }, OBJECT_BUILDING, TEAM_ALLY, 0);
	m_buildings[3] = new GameObject({ -X, Y, 0 }, OBJECT_BUILDING, TEAM_ENEMY, 0);     //3~5 북
	m_buildings[4] = new GameObject({ 0, Y+25, 0 }, OBJECT_BUILDING, TEAM_ENEMY, 0);
	m_buildings[5] = new GameObject({ X, Y, 0 }, OBJECT_BUILDING, TEAM_ENEMY, 0);
	
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

	soundBG=m_BG->CreateSound("./Dependencies/SoundSamples/Town.mp3");
	m_BG->PlaySoundW(soundBG, true, 0.2f);
	soundCollision = m_Coll->CreateSound("./Dependencies/SoundSamples/bell.wav");

	 texBuildingALLY = g_Renderer->CreatePngTexture("./Resources/Blue_Slime.png");
	 texBuildingKINGALLY = g_Renderer->CreatePngTexture("./Resources/Blue_KingSlime.png");
	 texBuildingENEMY = g_Renderer->CreatePngTexture("./Resources/Gold_Slime.png");
	 texBuildingKINGENEMY = g_Renderer->CreatePngTexture("./Resources/Gold_KingSlime.png");


	 texYellowSprite = g_Renderer->CreatePngTexture("./Resources/Sprite_Yellow1.png");
	 texBlueSprite = g_Renderer->CreatePngTexture("./Resources/Sprite_Blue1.png");
	 texOrangeSprite = g_Renderer->CreatePngTexture("./Resources/Sprite_Orange1.png");
	 texPurpleSprite = g_Renderer->CreatePngTexture("./Resources/Sprite_Purple1.png");
	 
	 texYellow= g_Renderer->CreatePngTexture("./Resources/Yellow.png");
	 texBlue = g_Renderer->CreatePngTexture("./Resources/Blue.png");
	 texOrange = g_Renderer->CreatePngTexture("./Resources/Orange.png");
	 texPurple = g_Renderer->CreatePngTexture("./Resources/Purple.png");


	 texParticle = g_Renderer->CreatePngTexture("./Resources/particle.png");
	 texBullet = g_Renderer->CreatePngTexture("./Resources/light_004.png");
	 bg_Texture = g_Renderer->CreatePngTexture("./Resources/Background.png");

}

void SceneMgr::DrawGameObject(float fElapsedTimeinSecond)
{
	cumulatedTime += fElapsedTimeinSecond;

	if (cumulatedTime >= 0.2f)
	{
		cumulatedTime = 0;
		++currImg;

		++ImgIdx;
		widthImg = ImgIdx % 5;
		heightImg = ImgIdx / 5 ;
	}

	coolTimer += fElapsedTimeinSecond;
	if (ETimer >= 10.f)		
		fever = 1;

		if (coolTimer > 0.2)
		{
			if (fever==1)	Energy += 2;
			else					++Energy;
			
			coolTimer = 0;
		}


	char c_cooltime[10];
	_itoa_s(Energy, c_cooltime, 10);
	GLuint textmp;

	RGBA Yellow{ 1,1,0,1 };
;	RGBA Blue{ 0,0,1,1 };
	RGBA Color;

	GLuint currtexBuilding = texBuildingALLY;

	//배경 그리기
	g_Renderer->DrawTexturedRect(0, 0, 0, 500.f,800.f, 1.f, 1.f, 1.f, 1.f, bg_Texture, BG_LEVEL);

	//빌딩 라이프 그리기
	for (int i = 0; i < 6; ++i)
	{
		if (m_buildings[i] != NULL)
		{
			if (m_buildings[i]->getTeam() == TEAM_ALLY) Color = Blue; else Color = Yellow;

			auto ob = m_buildings[i];
			float gauge = (float)(ob->getLife()) / (float)(ob->getMaxLife());
			g_Renderer->DrawSolidRectGauge(ob->getposX(), ob->getposY() + ob->getSize()*0.65f, 0, ob->getSize(), HPBAR_HEIGHT,
				Color.R, Color.G, Color.B, Color.A, gauge, ob->getLevel());		
		}
	}
	//빌딩 png 그리기
	for (int i = 0; i < 6; ++i)
	{
		if (i == 1) currtexBuilding = texBuildingKINGALLY;
		else if (i == 0 || i == 2) currtexBuilding = texBuildingALLY;
		else if (i == 3 || i == 5) currtexBuilding = texBuildingENEMY;
		else currtexBuilding = texBuildingKINGENEMY;

		if (m_buildings[i] != NULL)
			g_Renderer->DrawTexturedRect(m_buildings[i]->getposX(), m_buildings[i]->getposY(), m_buildings[i]->getposZ(), m_buildings[i]->getSize(), m_buildings[i]->getSize(),
				m_buildings[i]->getR(), m_buildings[i]->getG(), m_buildings[i]->getB(), m_buildings[i]->getAlpha(), currtexBuilding, m_buildings[i]->getLevel());
	}
	//덱그리기
	g_Renderer->DrawTexturedRect(-WINDOW_WIDTH / 2 + 150, -WINDOW_HEIGHT / 2 + 50, 0, 30, 30, 1, 1, 1, 1, texOrange, 0.2f);
	g_Renderer->DrawTextW(-WINDOW_WIDTH / 2 + 150, -WINDOW_HEIGHT / 2 + 20, GLUT_BITMAP_TIMES_ROMAN_24, 1.f, 1.f, 1.f, "6");

	g_Renderer->DrawTexturedRect(-WINDOW_WIDTH / 2 + 200, -WINDOW_HEIGHT / 2 + 50, 0, 30, 30, 1, 1, 1, 1, texYellow, 0.2f);
	g_Renderer->DrawTextW(-WINDOW_WIDTH / 2 + 200, -WINDOW_HEIGHT / 2 + 20, GLUT_BITMAP_TIMES_ROMAN_24, 1, 1, 1, "2");

	g_Renderer->DrawTexturedRect(-WINDOW_WIDTH / 2 + 250, -WINDOW_HEIGHT / 2 + 50, 0, 30, 30, 1, 1, 1, 1, texPurple, 0.2f);
	g_Renderer->DrawTextW(-WINDOW_WIDTH / 2 + 250, -WINDOW_HEIGHT / 2 + 20, GLUT_BITMAP_TIMES_ROMAN_24, 1, 1, 1, "4");
	g_Renderer->DrawTexturedRect(-WINDOW_WIDTH / 2 + 300, -WINDOW_HEIGHT / 2 + 50, 0, 30, 30, 1, 1, 1, 1, texBlue, 0.2f);
	g_Renderer->DrawTextW(-WINDOW_WIDTH / 2 + 300, -WINDOW_HEIGHT / 2 + 20, GLUT_BITMAP_TIMES_ROMAN_24, 1, 1, 1, "3");

	g_Renderer->DrawTextW(-WINDOW_WIDTH / 2 + 50, -WINDOW_HEIGHT / 2 + 50, GLUT_BITMAP_TIMES_ROMAN_24, 0.f, 0.f, 0.f, c_cooltime);

	//캐릭터, 라이프 그리기
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			//라이프바
			auto ob = getObject(i);
			float gauge = (float)(ob->getLife()) / (float)(ob->getMaxLife());

			g_Renderer->DrawSolidRectGauge(ob->getposX(), ob->getposY() + ob->getSize()*0.75f, 0, ob->getSize(), ob->getSize()*0.25f,
				ob->getR(), ob->getG(), ob->getB(), ob->getAlpha(), gauge, ob->getLevel());
			//캐릭터
			auto tKind=ob->getKind();
			switch (tKind)
			{
			case CHAR_KIND_YELLOW_BIG:
				textmp = texYellowSprite;
				break;
			case CHAR_KIND_BLUE_SPEEDY:
				textmp = texBlueSprite;
				break;
			case CHAR_KIND_Orange_DOZEN:
				textmp = texOrangeSprite;
				break;
			case CHAR_KIND_Purple_TANK:
				textmp = texPurpleSprite;
				break;
			default:
				break;
			}
			g_Renderer->DrawTexturedRectSeq(ob->getposX(), ob->getposY(), ob->getposZ(),	ob->getSize(), ob->getR(), ob->getG(), ob->getB(), 
				1.f, textmp,	currImg, ob->getCharDir(), 3, 4, getObject(i)->getLevel());
		}
	}
	g_Renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, texParticle, ETimer, 0.01f);

	//불렛 그리기
	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
	{
		if (m_bullets[i] != NULL)
		{
			auto ob = getBullet(i);

			g_Renderer->DrawTexturedRectSeq(ob->getposX(), ob->getposY(), ob->getposZ(), 50, ob->getR(), ob->getG(), ob->getB(),
				1.f, texBullet, widthImg, heightImg, 5, 5, BULLET_LEVEL);
		}
	}

	//애로우 그리기
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{
		if (m_arrows[i] != NULL)
		{
			auto ob = getArrow(i);

			g_Renderer->DrawParticle(ob->getposX(), ob->getposY(), ob->getposZ(), ob->getSize(), ob->getR(), ob->getG(), ob->getB(), ob->getAlpha(),
				0, ob->getDir(), texParticle, ob->getcumulatedTime(), ob->getLevel());
		}
	}

	//눈 그리기
	if(fever==1)
		g_Renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, texParticle, ETimer, 0.01f);

}

void SceneMgr::Update(float elapsedTimeInSecond)
{
	CollisionTest();	
	ETimer += elapsedTimeInSecond;

	// 빌딩 업데이트
	for (int i = 0; i < MAX_BUILDING_COUNT; ++i)
	{
		if (m_buildings[i] != NULL)
		{
			if (m_buildings[i]->getLife() <= 0)   //life가 다 닳면 소멸
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
				m_objects[i]->Update(elapsedTimeInSecond, m_objects[i]->getType());
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
				m_bullets[i]->Update(elapsedTimeInSecond, OBJECT_BULLET);
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
				m_arrows[i]->Update(elapsedTimeInSecond, OBJECT_ARROW);
		}
	}

	// 캐릭터 생성
	if (timeGetTime() - g_Timer_Unit > 3000.f)
	{
		g_Timer_Unit = timeGetTime();
		POS pos = { rand() % 450 - WINDOW_WIDTH / 2, max(rand() % 350,0) ,0 };
		CreateGameObject(pos.x, pos.y, TEAM_ENEMY, rand()%4);
	}

	//애로우 생성
	if (timeGetTime() - g_Timer_Arrow > 3000.f)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			g_Timer_Arrow = timeGetTime();
			if (m_objects[i] != NULL)
				CreateArrow(*m_objects[i]);
		}
	}

	// 불렛 생성
	if (timeGetTime() - g_Timer_Unit > 3000.f)
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
				if ((m_buildings[k] != NULL) && (m_buildings[k]->getTeam() != m_objects[i]->getTeam())) //빈공간이 아니면서 팀이 다를 때
				{
					if (CollisionBox(Xi, m_buildings[k]->getposX(), Yi, m_buildings[k]->getposY(), sizei, m_buildings[k]->getSize()))
					{   //빌딩과 캐릭터 충돌체크
						m_Coll->PlaySoundW(soundCollision, false, 0.3f);
						if (k == 1)
							ALLYbuildingActive = KING_ACT;
						else if (k == 4)
							ENEMYbuildingActive = KING_ACT;

						m_buildings[k]->minusLife(m_objects[i]->getLife());
						m_objects[i]->setLife(0);
						/*g_Renderer->SetSceneTransform(5, 2, 1.f, 1.f);
						g_Renderer->SetSceneTransform(-5, 2, 1.f, 1.f);*/

					}
				}
			}

			for (int j = 0; j < MAX_BULLETS_COUNT; ++j)
			{   //캐릭터와 불렛 충돌체크
				if (m_bullets[j] != NULL && m_bullets[j]->getTeam() != m_objects[i]->getTeam())
				{
					if (CollisionBox(Xi, m_bullets[j]->getposX(), Yi, m_bullets[j]->getposY(), sizei, m_bullets[j]->getSize()))
					{
						m_Coll->PlaySoundW(soundCollision, false, 0.3f);

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
						if (k == 1)
							ALLYbuildingActive = KING_ACT;
						else if (k == 4)
							ENEMYbuildingActive = KING_ACT;

						m_buildings[k]->minusLife(m_arrows[i]->getLife());
						m_arrows[i]->setLife(0);
					}
				}
			}

			
			for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
			{   //빌딩과 불렛 충돌체크
				if ((m_bullets[i] != NULL) && (m_bullets[i]->getTeam() != m_buildings[k]->getTeam())) //빈공간이 아니면서 팀이 다를 때
				{
					if (CollisionBox(Xi, m_bullets[i]->getposX(), Yi, m_bullets[i]->getposY(), sizei, m_bullets[i]->getSize()))
					{
						if (k == 1)
							ALLYbuildingActive = KING_ACT;
						else if (k == 4)
							ENEMYbuildingActive = KING_ACT;

						m_buildings[k]->minusLife(m_bullets[i]->getLife());
						m_bullets[i]->setLife(0);
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