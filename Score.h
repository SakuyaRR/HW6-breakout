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
	void increasescore();
	void resetscore() 
	{
		prevscore = 0;
		score = 0;
	}
private:
	Text scoreobj;
	Text lifeobj;
	float* score;
	float prevscore;
	Font scorefont;
	int* life;
	int prevlife;
	Font lifefont;
};
