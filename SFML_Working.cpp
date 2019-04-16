// SFML_Test.cpp : snake game

#include "pch.h"
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>

//dimensions for window size and background
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels
int w = size * num_horzBox;  //background number of pixels in width
int h = size * num_vertBox;    //background number of pixels in height
float delay = 0.15f;
int supertimer = 0;

//Actual Snake in game is an array of x,y coordinates of sprite2
struct Block
{
	int x, y;
};
struct Snake
{
	Block b[100];
	int direction;    //direction the snake is moving 
	int snake_length = 4; //initial size is 4, also the score
}s1, s2;

//***NEW*** this is the fruit or food that the snake will eat
struct Fruit
{
	int x, y;    // only need one sprite needed for one food item
}food, superfood;

//move snake head based on user input and body by incrementing 
//forward by iterating through arrays previous position
void move(struct Snake *s) {

	//1st update body so everything updates in proper order
	//move the body only!  s[0] = head will not be changed here
	for (int i = s->snake_length; i > 0; i--)
	{
		s->b[i].x = s->b[i - 1].x;
		s->b[i].y = s->b[i - 1].y;
	}
	//2nd update the head
	//Head of snake, s[0] depends on direction user inputs 
	//if user presses up
	if (s->direction == 0)
		s->b[0].y -= 1;

	//if user presses down
	if (s->direction == 1)
		s->b[0].y += 1;

	//if user presses left
	if (s->direction == 2)
		s->b[0].x -= 1;

	//if user presses right
	if (s->direction == 3)
		s->b[0].x += 1;


	//***NEW*** If Snake eats food it should grow
	//check if snake head = food location
	if (((s->b[0].x) == food.x) && ((s->b[0].y) == food.y))
	{
		//increment snake
		s->snake_length++;

		//increase speed
		if (delay - 0.05 > 0)
			delay -= 0.005f;


		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	//Check if snake ate the superfruit
	if (((s->b[0].x) == superfood.x) && ((s->b[0].y) == superfood.y))
	{
		//increment snake
		s->snake_length+=2;

		//increase speed
		delay += 0.01f;

		//Place superfruit outside bounds
		superfood.x = -10;
		superfood.y = -10;
	}

	//Boundary checking
	if (s->b[0].x > num_horzBox)
		s->b[0].x = 0;
	if (s->b[0].x < 0)
		s->b[0].x = num_horzBox;
	//TOP and BOTTOM
	if (s->b[0].y > num_vertBox-1)
		s->b[0].y = 0;
	if (s->b[0].y < 0)
		s->b[0].y = num_vertBox-1;

	//Check if snake is eating itself
	for (int i = 1; i < s->snake_length; i++)
	{
		if (s->b[0].x == s->b[i].x && s->b[0].y == s->b[i].y)
			s->snake_length = i;
	}
}

int main()
{
	//Setting pseudorandom time, TODO:discuss true random vs pseudorandom 
	srand(time(0));

	//Window that we can play the game in 
	sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");

	//Textures load an image into the GPU Memory
	sf::Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/fruit.png");
	t3.loadFromFile("images/snake1-1.png");
	t4.loadFromFile("images/snake2-1.png");
	t5.loadFromFile("images/superfruit.png");

	//Sprite has physical dimmensions that can be set in 
	//coordinate system, setPosition(x,y), and drawn on screen
	sf::Sprite sprite1(t1);
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);
	sf::Sprite sprite4(t4);
	sf::Sprite sprite5(t5);

	//***NEW*** initially place food somewhere on screen
	food.x = 10;
	food.y = 10;

	superfood.x = -10;
	superfood.y = -10;

	sf::Clock clock;
	float timer = 0.0f;

	while (window.isOpen())
	{
		
		//Error in class I placed this before the while loop
		//Should be placed in while loop as shown here to update
		//timer 
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something
		sf::Event e;

		//Check when the window is closed
		while (window.pollEvent(e))
		{
			//If user presses x in the top right, Windows, top left, Mac,  close the window
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Control for Snake 1 by User
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) s1.direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) s1.direction = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) s1.direction = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) s1.direction = 3;

		//Control for Snake 2 by User
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) s2.direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) s2.direction = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) s2.direction = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) s2.direction = 3;

		if (timer > delay)
		{
			timer = 0; //reset timer
			move(&s1);  //move Snake one
			move(&s2);	//move Snake two
			
			//update snake one's sprite for its length
			if (s1.snake_length > 33)
				t3.loadFromFile("images/snake1-12.png");
			else if(s1.snake_length > 30)
				t3.loadFromFile("images/snake1-11.png");
			else if (s1.snake_length > 27)
				t3.loadFromFile("images/snake1-10.png");
			else if(s1.snake_length > 24)
				t3.loadFromFile("images/snake1-9.png");
			else if (s1.snake_length > 21)
				t3.loadFromFile("images/snake1-8.png");
			else if (s1.snake_length > 18)
				t3.loadFromFile("images/snake1-7.png");
			else if (s1.snake_length > 15)
				t3.loadFromFile("images/snake1-6.png");
			else if (s1.snake_length > 12)
				t3.loadFromFile("images/snake1-5.png");
			else if (s1.snake_length > 9)
				t3.loadFromFile("images/snake1-4.png");
			else if (s1.snake_length > 6)
				t3.loadFromFile("images/snake1-3.png");
			else if (s1.snake_length > 3)
				t3.loadFromFile("images/snake1-2.png");
			else
				t3.loadFromFile("images/snake1-1.png");

			//update snake two's sprite for its length
			if (s2.snake_length > 33)
				t4.loadFromFile("images/snake2-12.png");
			else if (s2.snake_length > 30)
				t4.loadFromFile("images/snake2-11.png");
			else if (s2.snake_length > 27)
				t4.loadFromFile("images/snake2-10.png");
			else if (s2.snake_length > 24)
				t4.loadFromFile("images/snake2-9.png");
			else if (s2.snake_length > 21)
				t4.loadFromFile("images/snake2-8.png");
			else if (s2.snake_length > 18)
				t4.loadFromFile("images/snake2-7.png");
			else if (s2.snake_length > 15)
				t4.loadFromFile("images/snake2-6.png");
			else if (s2.snake_length > 12)
				t4.loadFromFile("images/snake2-5.png");
			else if (s2.snake_length > 9)
				t4.loadFromFile("images/snake2-4.png");
			else if (s2.snake_length > 6)
				t4.loadFromFile("images/snake2-3.png");
			else if (s2.snake_length > 3)
				t4.loadFromFile("images/snake2-2.png");
			else
				t4.loadFromFile("images/snake2-1.png");
			
			//if superfruit is not on the board
			if (superfood.x < 0)
			{
				//1 in 50 spawn the superfruit randomly on the board
				if (rand() % 50 == 0)
				{
					superfood.x = rand() % num_horzBox;
					superfood.y = rand() % num_vertBox;
					supertimer = 0;
				}
			}
			else
			{
				//after 66 loops (around 10 seconds) take superfruit off board
				if (++supertimer > 66)
				{
					superfood.x = -10;
					superfood.y = -10;
				}
			}
		}
		/*****************
		//Draw in window
		*****************/
		window.clear();    //clear the window so new frame can be drawn in

		//NOTE: Order matters as we will draw over items listed first. 
		//Hence the background should be the first thing you will always do
		//1st: Draw Background first
		for (int i = 0; i < num_horzBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				//Set position of sprite1 one at a time
				sprite1.setPosition(i*size, j*size);
				//Draw sprite1 but, do not show it on screen. 
				window.draw(sprite1);
			}
		}

		//2nd: Then Draw snake otherwise background will be drawn over snake if order was reversed with background
		for (int i = 0; i < s1.snake_length; i++)
		{
			//position sprite2 one at a time
			sprite3.setPosition(s1.b[i].x*size, s1.b[i].y*size);
			//Draw sprite2 one at a time by drawing over background
			window.draw(sprite3);
		}

		for (int i = 0; i < s2.snake_length; i++)
		{
			//position sprite2 one at a time
			sprite4.setPosition(s2.b[i].x*size, s2.b[i].y*size);
			//Draw sprite2 one at a time by drawing over background
			window.draw(sprite4);
		}

		//***NEW*** 3rd: Draw Fruit
		sprite2.setPosition(food.x*size, food.y*size);
		window.draw(sprite2);

		//Draw superfruit
		sprite5.setPosition(superfood.x*size, superfood.y*size);
		window.draw(sprite5);
		//Show everything we have drawn on the screen
		window.display();
	}
	return 0;
}