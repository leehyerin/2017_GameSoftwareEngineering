#pragma once

enum OBJECT_TYPE {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
};

enum OBJECT_TEAM {
	TEAM_ALLY,
	TEAM_ENEMY,
};

class GameObject
{
private:
	float posX;
	float posY;
	float posZ;
	float Size;
	float R, G, B;
	float Alpha;
	float vX;
	float vY;
	float Speed;
	int dir;
	int charDIR;
	int MaxLife;
	int Life;
	int LifeTime;
	int Type;
	int Team;
	float Level;
	float Timer=0;  //이걸로 수정하쟈
	float cumulativeTime=0;
	int currImg = 0;

public:
	float getposX() { return posX; }
	float getposY() { return posY; }
	float getposZ() { return posZ; }
	float getSize() { return Size; }
	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float getAlpha() { return Alpha; }
	void minusLife(int minusValue) { Life -= minusValue;  }
	void setLife(int value) { Life = value; }
	int getDitY() { return vY; }
	int getCharDir() { return charDIR; }
	int getType() { return Type; }
	int getTeam() { return Team; }
	int getMaxLife() { return MaxLife; }
	int getLife() { return Life; }
	int getLifeTIme() { return LifeTime; }
	int getLevel() { return Level; }
	int getTimer() { return Timer; };
	void setTimer() { Timer = 0.f; }
	int getCurrImg() { return currImg; }
	
public:
	GameObject(POS pos, int type, int team);
	void Update(float elapsedTIme, int type);

};
