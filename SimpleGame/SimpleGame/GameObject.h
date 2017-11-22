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
	int life;
	int lifeTime;
	int Type;
	int Team;

public:
	float getposX() { return posX; }
	float getposY() { return posY; }
	float getposZ() { return posZ; }
	float getSize() { return Size; }
	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float getAlpha() { return Alpha; }
	void minusLife(int minusValue) { life -= minusValue; }
	void setLife(int value) { life = value; }
	int getType() { return Type; }
	int getTeam() { return Team; }
	int getLife() { return life; }
	int getLifeTIme() { return lifeTime; }
	
public:
	GameObject(POS pos, int type, int team);
	void Update(float elapsedTIme,int type);

};
