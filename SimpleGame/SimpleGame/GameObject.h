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
	int dir = 1;
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

public:
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a) 
		: posX(x), posY(y), posZ(z), size(size), R(r), G(g), B(b), Alpha(a) 
	{
		speedX = (float)(rand() %10);
		speedY = (float)(rand() %10);
	}
	void Update(float elapsedTime);
	~GameObject();


};

