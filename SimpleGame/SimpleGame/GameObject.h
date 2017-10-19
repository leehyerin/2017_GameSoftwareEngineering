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
public:
	float getposX() { return posX; }
	float getposY() { return posY; }
	float getposZ() { return posZ; }
	void setposX(float x) { posX = x; }
	void setposY(float y) { posY = y; }
	void setposZ(float z) { posZ = z; }
	float getsize() { return size; }
	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float getAlpha() { return Alpha; }

public:
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a) 
		: posX(x), posY(y), posZ(z), size(size), R(r), G(g), B(b), Alpha(a) 
	{
		speedX = (float)(rand() % 50 - 25);
		speedY = (float)(rand() % 50 - 25);
	}
	void Update();
	~GameObject();


};

