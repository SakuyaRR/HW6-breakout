#include "GameObject.h"
#include "Ball.h"
#include "Score.h"

class Brick :public GameObject
{
	private:
		Ball* ball;
		Score* score;
		RectangleShape brick;
		int brickwidth;
		int brickheight;
		int lives;
		bool onehitbrick;
		bool invisible;
		Texture invisibletex;

	public:
		Brick();
		Brick(bool obh, bool invis, float x, float y, int sw, int sh, int l, Ball* b, Score* s);
		~Brick();
		void update(float dt);
		void render(RenderWindow& w) 
		{
			w.draw(brick);
		};
		void lowerlife() 
		{
			lives--;
		};
		int getLives() 
		{
			return lives;
		};
		void setTexture(Texture& t) 
		{
			if (invisible)
				brick.setTexture(&invisibletex);
			else if (onehitbrick)
				brick.setFillColor(Color::White);
			else
				brick.setTexture(&t);
		}
		bool getOHB()
		{
			return onehitbrick;
		};
};

