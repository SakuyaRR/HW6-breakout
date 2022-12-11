#pragma once
#include "GameObject.h"
class Score :
	public GameObject
{
public:
	Score();
	Score(float& s, int& l, int sw, int sh);
	~Score();
	void update(float dt);
	void render(RenderWindow& w);
	void increase_score();
	void reset_score() 
	{
		prev_score = 0;
		score = 0;
	}
private:
	Text score_obj;
	Text life_obj;
	float* score;
	float prev_score;
	Font score_font;
	int* life;
	int prev_life;
	Font life_font;

};