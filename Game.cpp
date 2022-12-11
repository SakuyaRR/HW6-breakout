#include "GameObject.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"

const int SCREENWIDTH = 600;
const int SCREENHEIGHT = 600;
void updatestate(float dt);
void renderframe();
void loadlevelone();
void loadleveltwo();
void loadlevelthree();
void loadnextlevel();
void emptyscene();
int level;
int livesleft;
int numpaddles = 1;
bool lost = false;
bool backgroundone = true;
float currentscore = 0;
Vector2f speed;
float speedX = 150;
float speedY = 200;
float accumtime = 0;
vector<GameObject*> SceneGraph;
vector<Paddle*> Paddles;
RenderWindow window;
Texture t1, t2, t3, t4, bg1, bg2;
Text replaymessage;
Text livesmessage;
Font font;
RectangleShape background;

vector<Texture> texts;

int main() {
	window.create(VideoMode(SCREENWIDTH, SCREENHEIGHT), "Breakout");
	t1.loadFromFile("Asset/Images/brick.png");
	t2.loadFromFile("Asset/Images/cracked brick.png");
	t3.loadFromFile("Asset/Images/cracked brick1.png");
	background.setPosition(0, 0);
	background.setFillColor(sf::Color(0, 0, 0, 155));
	background.setSize(Vector2f(SCREENWIDTH, SCREENHEIGHT));
	texts.push_back(t4);
	texts.push_back(t3);
	texts.push_back(t2);
	texts.push_back(t1);
	speed.x = speedX;
	speed.y = speedY;
	level = 1;
	livesleft = 3;
	replaymessage.setCharacterSize(24);
	replaymessage.setString("Your score was: ??\nPress Enter to play again");
	replaymessage.setPosition(0, 0);
	font.loadFromFile("Asset/Fonts/arial.ttf");
	replaymessage.setFont(font);
	loadlevelone();
	bool altdown = false;
	Clock clock;

	while (window.isOpen()) 
	{
		Event  event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) 
			{
				if (event.key.code == Keyboard::LAlt && !altdown) 
				{
					altdown = true;
					loadnextlevel();
				}
			}
			if (event.type == Event::KeyReleased) 
			{
				if (event.key.code == Keyboard::LAlt) 
				{
					altdown = false;
				}
			}
		}
		float dt = clock.restart().asSeconds();
		accumtime += dt;
		updatestate(dt);
		renderframe();
		window.display();
	}
	return 0;
}

void updatestate(float dt) 
{
	if (!lost) {
		for (auto i = SceneGraph.begin(); i != SceneGraph.end(); ++i) 
		{
			(*i)->update(dt);
		}
		int numBricks = 0;
		for (auto i = SceneGraph.begin(); i != SceneGraph.end(); ++i) 
		{
			if (auto j = dynamic_cast<Brick*>(*i)) 
			{
				numBricks++;
				if (j->getLives() <= 0) 
				{
					delete j;
					SceneGraph.erase(i);
					break;
				}
				else 
				{
					j->setTexture(texts[j->getLives()]);
				}
			}
		}
		if (numBricks == 0) 
		{
			loadnextlevel();
		}
		if (livesleft == 0) 
		{
			emptyscene();
			lost = true;
		}
	}
	else 
	{
		if (Keyboard::isKeyPressed(Keyboard::Return)) 
		{
			speed.x = speedX;
			speed.y = speedY;
			level = 1;
			livesleft = 3;
			currentscore = 0;
			loadlevelone();
			lost = false;
		}
	}
}

void renderframe() 
{
	window.clear(Color(128));
	window.draw(background);
	if (!lost) 
	{
		for (auto i = SceneGraph.begin(); i != SceneGraph.end(); ++i) 
		{
			(*i)->render(window);
		}
	}
	else 
	{
		ostringstream temps;
		temps << "Your score was: " << currentscore << "\nPress Enter to play again!";
		replaymessage.setString(temps.str());
		window.draw(replaymessage);
	}
}

void emptyscene() 
{
	for (auto i = SceneGraph.begin(); i != SceneGraph.end(); ++i) 
	{
		delete* i;
	}
	SceneGraph.clear();
	Paddles.clear();
}

void loadlevelone() 
{
	for (int i = 0; i < numpaddles; ++i) 
	{
		Paddle* paddle = new Paddle(SCREENWIDTH, SCREENHEIGHT, speed.x * 1.8, livesleft, i);
		Paddles.push_back(paddle);
		SceneGraph.push_back(paddle);
	}
	Ball* ball = new Ball(SCREENWIDTH, SCREENHEIGHT, 10, Paddles, speed);
	Score* score = new Score(currentscore, livesleft, SCREENWIDTH, SCREENHEIGHT);
	for (float i = SCREENHEIGHT * .1, k = 2; i < SCREENHEIGHT * .4; i += SCREENHEIGHT * .1, k--) 
	{
		for (float j = SCREENWIDTH * .1; j < SCREENWIDTH * .9; j += SCREENWIDTH * .1) 
		{
			Brick* b = new Brick(true, false, j, i, SCREENWIDTH, SCREENHEIGHT, k, ball, score);
			SceneGraph.push_back(b);
		}
	}
	SceneGraph.push_back(ball);
	SceneGraph.push_back(score);
}
void loadleveltwo() 
{
	for (int i = 0; i < numpaddles; ++i) 
	{
		Paddle* paddle = new Paddle(SCREENWIDTH, SCREENHEIGHT, speed.x * 1.8, livesleft, i);
		Paddles.push_back(paddle);
		SceneGraph.push_back(paddle);
	}
	Ball* ball = new Ball(SCREENWIDTH, SCREENHEIGHT, 10, Paddles, speed);
	Score* score = new Score(currentscore, livesleft, SCREENWIDTH, SCREENHEIGHT);
	for (float i = SCREENHEIGHT * .1, k = 2; i < SCREENHEIGHT * .5; i += SCREENHEIGHT * .2, k--) 
	{
		for (float j = SCREENWIDTH * .1; j < SCREENWIDTH; j += SCREENWIDTH * .2) 
		{
			Brick* b = new Brick(false, false, j, i, SCREENWIDTH, SCREENHEIGHT, 3, ball, score);
			SceneGraph.push_back(b);
		}
	}
	for (float i = SCREENHEIGHT * .2, k = 2; i <= SCREENHEIGHT * .4; i += SCREENHEIGHT * .2, k--) 
	{
		for (float j = 0; j < SCREENWIDTH; j += SCREENWIDTH * .2) 
		{
			Brick* b = new Brick(true, false, j, i, SCREENWIDTH, SCREENHEIGHT, 2, ball, score);
			SceneGraph.push_back(b);
		}
	}
	SceneGraph.push_back(ball);
	SceneGraph.push_back(score);
}

void loadlevelthree() 
{
	for (int i = 0; i < numpaddles; ++i) 
	{
		Paddle* paddle = new Paddle(SCREENWIDTH, SCREENHEIGHT, speed.x * 1.8, livesleft, i);
		Paddles.push_back(paddle);
		SceneGraph.push_back(paddle);
	}
	Ball* ball = new Ball(SCREENWIDTH, SCREENHEIGHT, 10, Paddles, speed);
	SceneGraph.push_back(ball);
	Brick* b;
	Score* score = new Score(currentscore, livesleft, SCREENWIDTH, SCREENHEIGHT);

	for (float i = 0, j = 0, k = 1; j < SCREENWIDTH; i += SCREENHEIGHT * .05, j += SCREENWIDTH * .1, k += 1) 
	{
		if ((int)k % 2)
			b = new Brick(true, false, j, i, SCREENWIDTH, SCREENHEIGHT, 3, ball, score);
		else
			b = new Brick(false, false, j, i, SCREENWIDTH, SCREENHEIGHT, 3, ball, score);
		SceneGraph.push_back(b);
	}
	for (float i = 0, j = SCREENWIDTH * .9, k = 1; j >= 0; i += SCREENHEIGHT * .05, j -= SCREENWIDTH * .1, k += 1) 
	{
		if ((int)k % 2)
			b = new Brick(true, false, j, i, SCREENWIDTH, SCREENHEIGHT, 3, ball, score);
		else
			b = new Brick(false, false, j, i, SCREENWIDTH, SCREENHEIGHT, 3, ball, score);
		SceneGraph.push_back(b);
	}
	SceneGraph.push_back(score);
}
void loadnextlevel() 
{
	emptyscene();
	level++;
	speed.x += 25;
	speed.y += 25;
	if (level == 2) 
	{
		loadleveltwo();
	}
	else if (level == 3) 
	{
		loadlevelthree();
	}
	else if (level == 4) 
	{
		loadlevelone();
		level = 1;
	}
}

