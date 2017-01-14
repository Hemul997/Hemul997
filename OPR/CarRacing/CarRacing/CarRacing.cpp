//// CarRacing.cpp : Defines the entry point for the console application.
////
#define _CRT_SECURE_NO_WARNINGS
//
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace sf;

const int NUM_OF_CHECKPOINTS = 8;
const int MAX_FPS = 60;
const int NUM_OF_CARS = 6;
const int COUNT_OF_COORDINATES = 2;
const float MAX_SPEED = 12.0;
const float TURN_SPEED = 0.08;
const float ACC = 0.2;
const float DEC = 0.3;
const float RADIUS_OF_CAR = 22;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int points[NUM_OF_CHECKPOINTS][COUNT_OF_COORDINATES] =
					 {300, 610,
                      1270, 430,
                      1380, 2380,
                      1900, 2460,
                      1970, 1700,
                      2550, 1680,
                      2560, 3150,
                      500, 3300};

struct Car
{
	float x, y, speed, angle; 
	int checkpointNum;
	Car() 
	{
		speed=2; 
		angle=0;
		checkpointNum=0;
	}
	void move()
	{
		x += sin(angle) * speed;
		y -= cos(angle) * speed;
	}
	void findTarget()
	{
		float tx=points[checkpointNum][0];
		float ty=points[checkpointNum][1];
		float beta = angle-atan2(tx-x,-ty+y);
		if (sin(beta) < 0)
		{
			angle += 0.005*speed;
		}
		else
		{
			angle -= 0.005*speed;
		}
		if ((x - tx)*(x - tx) + (y - ty)*(y - ty) < 25 * 25)
		{
			checkpointNum = (checkpointNum + 1) % NUM_OF_CHECKPOINTS;
		}
	}
	
};
struct GameMap
{
	Event event;
	Texture tBackground, tCar;
	Sprite sBackground, sCar;
};

void HandleEvents(RenderWindow & app, GameMap & game);
void CreateTextures(GameMap &game);
void SetParamsForCars(Car *car);
void DrawCar(RenderWindow &app, GameMap &game, Car *car);
void Collision(Car *car);
bool LoadTextures(GameMap &game);
void AddSpeed(float &speed);
void ReduceSpeed(float &speed);
void Retarder(float &speed);
void Movement(Car *car);
void HandleKeyboardPress(float &speed, float &angle);

int main()
{
	RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Car Racing Game!");
	app.setFramerateLimit(MAX_FPS);
	GameMap game;
	Car car[NUM_OF_CARS];
	float speed = 0, angle = 0;
	if (LoadTextures(game))
	{
		CreateTextures(game);
		SetParamsForCars(car);
	}
	else
	{
		return EXIT_FAILURE;
	}
	while (app.isOpen())
	{
		HandleEvents(app, game);
		HandleKeyboardPress(speed, angle);
		car[0].speed = speed;
		car[0].angle = angle;
		Movement(car);
		Collision(car);
		app.clear(Color::White);
		DrawCar(app, game, car);
		app.display();
	}
	return EXIT_SUCCESS;
}

void HandleEvents(RenderWindow & app, GameMap & game)
{
	while (app.pollEvent(game.event))
	{
		if (game.event.type == Event::Closed)
		{
			app.close();
		}
	}
}
void SetParamsForCars(Car *car)
{
	for (int i = 0; i<NUM_OF_CARS; i++)
	{
		car[i].x = 300 + i * 50;
		car[i].y = 1700 + i * 80;
		car[i].speed = 7 + i;
	}
}
bool LoadTextures(GameMap &game)
{
	return game.tBackground.loadFromFile("images/background.png") && game.tCar.loadFromFile("images/car.png");
}
void CreateTextures(GameMap &game)
{
	game.tBackground.setSmooth(true);
	game.tCar.setSmooth(true);
	game.sBackground.setTexture(game.tBackground);
	game.sCar.setTexture(game.tCar);
	game.sBackground.scale(2, 2);
	game.sCar.setOrigin(RADIUS_OF_CAR, RADIUS_OF_CAR);
}
void DrawCar(RenderWindow &app, GameMap &game, Car *car)
{
	int offsetX = 0, offsetY = 0;
	if (car[0].x > 320)
	{
		offsetX = car[0].x - 320;
	}
	if (car[0].y > 240)
	{
		offsetY = car[0].y - 240;
	}

	game.sBackground.setPosition(-offsetX, -offsetY);
	app.draw(game.sBackground);

	Color colors[10] = { Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White, Color::Yellow };

	for (int i = 0; i<NUM_OF_CARS; i++)
	{
		game.sCar.setPosition(car[i].x - offsetX, car[i].y - offsetY);
		game.sCar.setRotation(car[i].angle * 180 / 3.141593);
		game.sCar.setColor(colors[i]);
		app.draw(game.sCar);
	}
}
void Collision(Car *car)
{
	for (int i = 0; i<NUM_OF_CARS; ++i)
	{
		for (int j = 0; j < NUM_OF_CARS; ++j)
		{
			int dx = 0, dy = 0;
			while (dx*dx + dy*dy < 4 * pow(RADIUS_OF_CAR, 2))
			{
				car[i].x += dx / 10.0;
				car[i].x += dy / 10.0;
				car[j].x -= dx / 10.0;
				car[j].y -= dy / 10.0;
				dx = car[i].x - car[j].x;
				dy = car[i].y - car[j].y;
				if (!dx && !dy) break;
			}
		}
	}
}
void AddSpeed(float &speed)
{
	if (speed < 0)
	{
		speed += DEC;
	}
	else
	{
		speed += ACC;
	}
}
void ReduceSpeed(float &speed)
{
	if (speed > 0)
	{
		speed -= DEC;
	}
	else
	{
		speed -= ACC;
	}
}
void Retarder(float &speed)
{
	if (speed - DEC > 0)
	{
		speed -= DEC;
	}
	else
	{
		if (speed + DEC < 0)
		{
			speed += DEC;
		}
		else
		{
			speed = 0;
		}
	}
}
void Movement(Car *car)
{
	for (int i = 0; i < NUM_OF_CARS; ++i) car[i].move();
	for (int i = 1; i < NUM_OF_CARS; ++i) car[i].findTarget();
}
void HandleKeyboardPress(float &speed, float &angle)
{
	bool Up = 0, Right = 0, Down = 0, Left = 0;
	if (Keyboard::isKeyPressed(Keyboard::Up)) Up = 1;
	if (Keyboard::isKeyPressed(Keyboard::Right)) Right = 1;
	if (Keyboard::isKeyPressed(Keyboard::Down)) Down = 1;
	if (Keyboard::isKeyPressed(Keyboard::Left)) Left = 1;

	//car movement
	if (Up && speed < MAX_SPEED)
	{
		AddSpeed(speed);
	}
	if (Down && speed > -MAX_SPEED)
	{
		ReduceSpeed(speed);
	}
	if (!Up && !Down)
	{
		Retarder(speed);
	}
	if (speed != 0)
	{
		if (Right)
		{
			angle += TURN_SPEED * speed / MAX_SPEED;
		}
		if (Left)
		{
			angle -= TURN_SPEED * speed / MAX_SPEED;
		}
	}
}