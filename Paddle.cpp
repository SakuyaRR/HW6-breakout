#include "Paddle.h"

Paddle::Paddle(){}

Paddle::Paddle(int sw, int sh, float speed, int& l, int pad_num) 
{
	screen_width = sw;
	screen_height = sh;
	paddle_width = sw / 6;
	paddle_height = paddle_width / 5;
	paddle.setSize(Vector2f(paddle_width, paddle_height));
	paddle.setPosition(Vector2f(sw / 2 - paddle_width / 2, sh - paddle_height));
	this->speed = speed;
	lives = &l;
	paddle.setTexture(&paddle_texture);
}


Paddle::~Paddle(){}

void Paddle::setTex(int* l) {}

void Paddle::lose_life() 
{
	if (paddle_num != 1)
		*lives = *lives - 1;
	if (*lives > 0) 
	{
		lose_life_sound.play();
	}
	else 
	{
		lose.play();
	}
	setTex(lives);
}

void Paddle::update(float dt) 
{
	Vector2f pos = paddle.getPosition();
	if (Keyboard::isKeyPressed(Keyboard::A) && paddle_num == 0) 
	{
		pos.x -= speed * dt;
		if (pos.x < 0) pos.x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && paddle_num == 0) 
	{
		pos.x += speed * dt;
		if (pos.x > screen_width - paddle_width) 
		{
			pos.x = screen_width - paddle_width;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && paddle_num == 1) 
	{
		pos.x -= speed * dt;
		if (pos.x < 0) pos.x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && paddle_num == 1) 
	{
		pos.x += speed * dt;
		if (pos.x > screen_width - paddle_width) 
		{
			pos.x = screen_width - paddle_width;
		}
	}
	paddle.setPosition(pos);
}