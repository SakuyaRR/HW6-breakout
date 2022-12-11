#include "Brick.h"


Brick::Brick(){}


Brick::Brick(bool ohb, bool invis, float x, float y, int sw, int sh, int l, Ball* b, Score* s)
{

	ball = b;
	score = s;
	onehitbrick = ohb;
	invisible = invis;
	if (!invis) 
	{
		brick.setOutlineColor(Color::Black);
		brick.setOutlineThickness(2);
	}
	if (ohb)
	{
		lives = 1;
	}
	else 
	{
		lives = l;
	}
	brickwidth = sw / 10;
	brickheight = brickwidth / 2;
	brick.setPosition(Vector2f(x, y));
	brick.setSize(Vector2f(brickwidth, brickheight));
}

Brick::~Brick(){}

void Brick::update(float dt)
{
	Vector2f pos = brick.getPosition();
	Vector2f ballPos = ball->getPosition();
	int radius = ball->getRadius();
	if (ballPos.x + radius >= pos.x &&ballPos.x - radius <= pos.x &&ballPos.y >= pos.y &&ballPos.y <= pos.y + brickheight) 
	{
		ball->setPosition(pos.x - radius, ballPos.y);
		lives--;
		if (invisible) 
		{
			brick.setTexture(NULL);
			onehitbrick = true;
			invisible = false;
		}
		ball->reverseX();
		score->increasescore();
	}
	if (ballPos.x - radius <= pos.x + brickwidth &&ballPos.x + radius >= pos.x + brickwidth &&ballPos.y >= pos.y &&ballPos.y <= pos.y + brickheight)
	{
		ball->setPosition(pos.x + brickwidth + radius, ballPos.y);
		lives--;
		if (invisible) 
		{
			brick.setTexture(NULL);
			onehitbrick = true;
			invisible = false;
		}
		ball->reverseX();
		score->increasescore();
	}
	if (ballPos.y - radius <= pos.y + brickheight &&ballPos.y + radius >= pos.y + brickheight &&ballPos.x - radius >= pos.x &&ballPos.x + radius <= pos.x + brickwidth) 
	{
		ball->setPosition(ballPos.x, pos.y + brickheight + radius);
		ball->reverseY();
		lives--;
		if (invisible) 
		{
			brick.setTexture(NULL);
			onehitbrick = true;
			invisible = false;
		}
		score->increasescore();
	}
	if (ballPos.y + radius >= pos.y &&ballPos.y - radius <= pos.y &&ballPos.x - radius >= pos.x &&ballPos.x + radius <= pos.x + brickwidth) 
	{
        ball->setPosition(ballPos.x, pos.y - radius);
		ball->reverseY();
		lives--;
		if (invisible) 
		{
			brick.setTexture(NULL);
			onehitbrick = true;
			invisible = false;
		}
		score->increasescore();
    }
}
