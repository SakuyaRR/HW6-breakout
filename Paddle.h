#pragma once
#include "GameObject.h"
class Paddle :public GameObject
{
private:
	int paddlewidth;
	int paddleheight;
	int screenwidth;
	int screenheight;
	int paddlenum;
	RectangleShape paddle;
	float speed = 150;
	int* lives;

public:
	Paddle();
	Paddle(int sw, int sh, float speed, int& l, int padnum);
	~Paddle();
	void update(float dt);
	void render(RenderWindow& w) 
	{
		w.draw(paddle);
	}
	Vector2f getMidpoint() 
	{
		return Vector2f(paddle.getPosition().x + paddlewidth / 2, paddle.getPosition().y);
	}
	const Vector2f getPosition() 
	{
		return paddle.getPosition();
	}
	int getWidth() 
	{
		return paddlewidth;
	}
	void loselife();
	void setTex(int* l);
};