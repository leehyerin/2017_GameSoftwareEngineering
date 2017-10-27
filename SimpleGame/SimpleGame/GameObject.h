#pragma once
class GameObject
{
private:
	float posX;
	float posY;
	float posZ;
	float size;
	float R, G, B;
	float Alpha;
	float speedX;
	float speedY;
	int dir;
	int life;
	int lifeTime;
public:
	float getposX() { return posX; }
	float getposY() { return posY; }
	float getposZ() { return posZ; }
	void setposX(float x) { posX = x; }
	void setposY(float y) { posY = y; }
	void setposZ(float z) { posZ = z; }
	void setR(float r) { R = r; };
	void setG(float g) { G = g; };
	void setB(float b) { B = b; };
	float getSize() { return size; }
	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float getAlpha() { return Alpha; }
	void minusLife() { --life; }
	int getLife() { return life; }
	int getLifeTIme() { return lifeTime; }

public:
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a) 
		: posX(x), posY(y), posZ(z), size(size), R(r), G(g), B(b), Alpha(a) 
	{
		speedX =(float)(rand() % 500)-100;
		speedY =(float)(rand() % 500)-100;
		dir = 1;
		life = 1;
		lifeTime = 100000.f;
	}
	void Update(float elapsedTIme);
	~GameObject();


};

