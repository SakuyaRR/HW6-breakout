#include "Paddle.h"

Paddle::Paddle(){}

Paddle::Paddle(int sw, int sh, float speed, int& l, int padnum) 
{
	screenwidth = sw;
	screenheight = sh;
	paddlewidth = sw / 6;
	paddleheight = paddlewidth / 5;
	paddle.setSize(Vector2f(paddlewidth, paddleheight));
	paddle.setPosition(Vector2f(sw / 2 - paddlewidth / 2, sh - paddleheight));
	this->speed = speed;
	lives = &l;
}


Paddle::~Paddle(){}

void Paddle::setTex(int* l) {}

void Paddle::loselife() 
{
	if (paddlenum != 1)
		*lives = *lives - 1;
	setTex(lives);
}

void Paddle::update(float dt) 
{
	Vector2f pos = paddle.getPosition();
	if (Keyboard::isKeyPressed(Keyboard::A) && paddlenum == 0) 
	{
		pos.x -= speed * dt;
		if (pos.x < 0) pos.x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && paddlenum == 0) 
	{
		pos.x += speed * dt;
		if (pos.x > screenwidth - paddlewidth) 
		{
			pos.x = screenwidth - paddlewidth;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && paddlenum == 1) 
	{
		pos.x -= speed * dt;
		if (pos.x < 0) pos.x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && paddlenum == 1) 
	{
		pos.x += speed * dt;
		if (pos.x > screenwidth - paddlewidth) 
		{
			pos.x = screenwidth - paddlewidth;
		}
	}
	paddle.setPosition(pos);
}