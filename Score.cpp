#include "Score.h"

Score::Score(){}

Score::Score(float& s, int& l, int sw, int sh) 
{
	score = &s;
	prevscore = s;
	scorefont.loadFromFile("Asset/Fonts/arial.ttf");
	scoreobj.setFont(scorefont);
	scoreobj.setPosition(0, sh *.8);
	scoreobj.setCharacterSize(24);

	life = &l;

	lifefont.loadFromFile("Asset/Fonts/arial.ttf");
	lifeobj.setFont(scorefont);
	lifeobj.setPosition(0, sh * .75);
	lifeobj.setCharacterSize(24);
}

Score::~Score(){}

void Score::update(float dt)
{
	if (prevscore < *score) 
	{
		prevscore += 1;
	}
	else 
	{
		prevscore = *score;
	}
	ostringstream temps;
	temps << "Score: " << prevscore;
	scoreobj.setString(temps.str());

	if (prevlife > *life) 
	{
		prevlife -= 1;
	}
	else 
	{
		prevlife = *life;
	}
	ostringstream templ;
	templ << "HP: " << prevlife;
	lifeobj.setString(templ.str());
}

void Score::render(RenderWindow& w)
{
	w.draw(scoreobj);
	w.draw(lifeobj);
}

void Score::increasescore()
{
	*score = *score + 100;
}