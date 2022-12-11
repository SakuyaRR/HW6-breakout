#include "Score.h"

Score::Score(){}

Score::Score(float& s, int& l, int sw, int sh) 
{
	score = &s;
	prev_score = s;
	score_font.loadFromFile("Asset/Fonts/arial.ttf");
	score_obj.setFont(score_font);
	score_obj.setPosition(0, sh *.8);
	score_obj.setCharacterSize(24);

	life = &l;

	life_font.loadFromFile("Asset/Fonts/arial.ttf");
	life_obj.setFont(score_font);
	life_obj.setPosition(0, sh * .75);
	life_obj.setCharacterSize(24);
}

Score::~Score(){}

void Score::update(float dt)
{
	if (prev_score < *score) 
	{
		prev_score += 1;
	}
	else 
	{
		prev_score = *score;
	}
	ostringstream temp_s;
	temp_s << "Score: " << prev_score;
	score_obj.setString(temp_s.str());

	if (prev_life > *life) 
	{
		prev_life -= 1;
	}
	else 
	{
		prev_life = *life;
	}
	ostringstream temp_l;
	temp_l << "HP: " << prev_life;
	life_obj.setString(temp_l.str());
}

void Score::render(RenderWindow& w)
{
	w.draw(score_obj);
	w.draw(life_obj);
}

void Score::increase_score()
{
	*score = *score + 100;
}