////////////////////////////////////////////////////////////
// Headers:
// ctime for getting system time and
// cmath for sin and cos functions
////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>

using namespace sf;
using namespace std;

// Define some variables and constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int ANTIALIASING_LEVEL = 8;
const int NUMBERS_FONT_SIZE = 25;
const int COUNTS_OF_DOTS = 60;
const int COUNT_OF_NUMBERS = 12;
const int CIRCLE_POINT_COUNTS = 100;
const float PI = 3.1415927;

const float CLOCK_CIRCLE_RADIUS = 250;
const float CLOCK_CIRCLE_THICKNESS = 2;
const float CENTER_CIRCLE_RADIUS = 10;
const float HOUR_HAND_WIDTH = 5;
const float HOUR_HAND_HEIGHT = 180;
const float MINUTE_HAND_WIDTH = 3;
const float MINUTE_HAND_HEIGHT = 240;
const float SECOND_HAND_WIDTH = 2;
const float SECOND_HAND_HEIGHT = 250;
const float OFFSET_NUMBERS = 30;
const float OFFSET_DOTS = 10;

struct Clocks
{
	CircleShape dot[COUNTS_OF_DOTS];
	ContextSettings settings;
	CircleShape clockOutline;
	CircleShape centerCircle;
	RectangleShape hourHand;
	RectangleShape minuteHand;
	RectangleShape secondsHand;
	Music clockTick;
	Texture clockImage;
	Texture clockBrand;
	Sprite clockBrandSprite;
	Event event;
	Text numbers[COUNT_OF_NUMBERS];
	Font font;
};
void CreateOutline(RenderWindow & window, Clocks & clock);
void CreateCenterCircle(Vector2f &windowCenter, Clocks & clock);
void CreateTextures(RenderWindow & window, Clocks & clock);
void CreateDots(RenderWindow & window, Clocks & clock);
void CreateNumbers(RenderWindow &window, Clocks & clock);
void CreateMusic(Clocks &clock);
void CreateDisplay(RenderWindow & window, Clocks & clock);
void GetSystemTime(Clocks & clock);
void CreateHands(Vector2f & windowCenter, Clocks & clock);
void HandleEvents(RenderWindow & window, Clocks & clock);

Vector2f GetRectCenter(IntRect & brandTextureRect);

bool LoadClockImage(Clocks &clock);
bool LoadBrandImage(Clocks &clock);
bool LoadFont(Clocks & clock);
bool LoadMusic(Clocks &clock);

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
	Clocks clock;

	// Set multisampling level
	ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;

	// Create the window of the application
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", Style::Close, settings);

	// Define windowCenter which gets the center of the window here, right after creating window
	Vector2f windowCenter(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	if (LoadClockImage(clock) && LoadBrandImage(clock) && LoadMusic(clock) && LoadFont(clock))
	{
		CreateOutline(window, clock);
		CreateCenterCircle(windowCenter, clock);
		CreateHands(windowCenter, clock);
		CreateDots(window, clock);
		CreateNumbers(window, clock);
		CreateTextures(window, clock);
		CreateMusic(clock);
	}
	else
	{
		return EXIT_FAILURE;
	}
	
	while (window.isOpen())
	{
		HandleEvents(window, clock);
		GetSystemTime(clock);
		CreateDisplay(window, clock);
	}

	return EXIT_SUCCESS;
}
void GetSystemTime(Clocks & clock)
{
	time_t currentTime = time(NULL);
	struct tm * ptm = localtime(&currentTime);
	clock.hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
	clock.minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
	clock.secondsHand.setRotation(ptm->tm_sec * 6);
}
void CreateHands(Vector2f & windowCenter, Clocks & clock)
{
	Vector2f hourHandSize = Vector2f(HOUR_HAND_WIDTH, HOUR_HAND_HEIGHT);
	Vector2f minuteHandSize = Vector2f(MINUTE_HAND_WIDTH, MINUTE_HAND_HEIGHT);
	Vector2f secondsHandSize = Vector2f(SECOND_HAND_WIDTH, SECOND_HAND_HEIGHT);

	clock.hourHand.setSize(hourHandSize);
	clock.minuteHand.setSize(minuteHandSize);
	clock.secondsHand.setSize(secondsHandSize);

	clock.hourHand.setFillColor(Color::Black);
	clock.minuteHand.setFillColor(Color::Black);
	clock.secondsHand.setFillColor(Color::Red);

	clock.hourHand.setOrigin(clock.hourHand.getGlobalBounds().width / 2, clock.hourHand.getGlobalBounds().height - 25);
	clock.minuteHand.setOrigin(clock.minuteHand.getGlobalBounds().width / 2, clock.minuteHand.getGlobalBounds().height - 25);
	clock.secondsHand.setOrigin(clock.secondsHand.getGlobalBounds().width / 2, clock.secondsHand.getGlobalBounds().height - 25);

	clock.hourHand.setPosition(windowCenter);
	clock.minuteHand.setPosition(windowCenter);
	clock.secondsHand.setPosition(windowCenter);
}

void CreateDisplay(RenderWindow & window, Clocks & clock)
{
	window.clear(Color::White);
	window.draw(clock.clockOutline);

	for (int i = 0; i<60; i++)
	{
		window.draw(clock.dot[i]);
	}
	for (int i = 0; i < COUNT_OF_NUMBERS; ++i)
	{
		window.draw(clock.numbers[i]);
	}
	window.draw(clock.clockBrandSprite);
	window.draw(clock.hourHand);
	window.draw(clock.minuteHand);
	window.draw(clock.secondsHand);
	window.draw(clock.centerCircle);
	// Display things on screen
	window.display();
}
void HandleEvents(RenderWindow & window, Clocks & clock)
{
	while (window.pollEvent(clock.event))
	{
		if (clock.event.type == Event::Closed)
		{
			window.close();
		}
	}
}
void CreateOutline(RenderWindow & window, Clocks & clock)
{
	clock.clockOutline.setRadius(CLOCK_CIRCLE_RADIUS);
	clock.clockOutline.setPointCount(CIRCLE_POINT_COUNTS);
	clock.clockOutline.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
	clock.clockOutline.setOutlineColor(Color::Black);
	auto circleGlobalBounds = clock.clockOutline.getGlobalBounds();
	clock.clockOutline.setOrigin(circleGlobalBounds.width / 2, circleGlobalBounds.height / 2);
	clock.clockOutline.setPosition(window.getSize().x / 2 + CLOCK_CIRCLE_THICKNESS, window.getSize().y / 2 + CLOCK_CIRCLE_THICKNESS);
}

void CreateCenterCircle(Vector2f & windowCenter, Clocks & clock)
{
	// Crate another circle for center
	clock.centerCircle.setRadius(CENTER_CIRCLE_RADIUS);
	clock.centerCircle.setPointCount(CIRCLE_POINT_COUNTS);
	clock.centerCircle.setFillColor(Color::Red);
	auto circleGlobalBounds = clock.centerCircle.getGlobalBounds();
	clock.centerCircle.setOrigin(circleGlobalBounds.width / 2, circleGlobalBounds.height / 2);
	clock.centerCircle.setPosition(windowCenter);
}
void CreateTextures(RenderWindow & window, Clocks & clock)
{
	clock.clockOutline.setTexture(&clock.clockImage);
	clock.clockOutline.setTextureRect(IntRect(40, 0, 500, 500));

	Sprite &brandSprite = clock.clockBrandSprite;
	IntRect brandTextureRect = brandSprite.getTextureRect();
	brandSprite.setTexture(clock.clockBrand);
	brandSprite.setOrigin(GetRectCenter(brandTextureRect));
	brandSprite.setPosition(window.getSize().x / 2, window.getSize().y - 150);
}
Vector2f GetRectCenter(IntRect & brandTextureRect)
{
	return Vector2f(brandTextureRect.left + brandTextureRect.width / 2.0f,
		brandTextureRect.top + brandTextureRect.height / 2.0f);
}
bool LoadClockImage(Clocks &clock)
{
	return clock.clockImage.loadFromFile("resources/clock-image.png");
}
bool LoadBrandImage(Clocks & clock)
{
	return clock.clockBrand.loadFromFile("resources/clock-brand.png");
}
bool LoadMusic(Clocks & clock)
{
	return clock.clockTick.openFromFile("resources/clockSound.wav");
}
void CreateDots(RenderWindow & window, Clocks & clock)
{
	float x = 0.0;
	float y = 0.0;
	float angle = 0.0;
	for (int i = 0; i < COUNTS_OF_DOTS; i++)
	{
		x = (CLOCK_CIRCLE_RADIUS - OFFSET_DOTS) * cos(angle);
		y = (CLOCK_CIRCLE_RADIUS - OFFSET_DOTS) * sin(angle);

		if (i % 5 == 0)
			clock.dot[i] = CircleShape(3);
		else
			clock.dot[i] = CircleShape(1);
		clock.dot[i].setFillColor(Color::Black);
		clock.dot[i].setOrigin(clock.dot[i].getGlobalBounds().width / 2, clock.dot[i].getGlobalBounds().height / 2);
		clock.dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		angle = angle + ((2 * PI) / COUNTS_OF_DOTS);
	}
}
void CreateNumbers(RenderWindow &window, Clocks & clock)
{
	float x = 0.0, y = 0.0;
	float angle = 0.0;
	for (int i = 0; i < COUNT_OF_NUMBERS; ++i)
	{
		x = (CLOCK_CIRCLE_RADIUS - OFFSET_NUMBERS) * cos(angle - (PI / 3));
		y = (CLOCK_CIRCLE_RADIUS - OFFSET_NUMBERS) * sin(angle - (PI / 3));
		clock.numbers[i].setString(std::to_string(i + 1));
		clock.numbers[i].setFont(clock.font);
		clock.numbers[i].setCharacterSize(NUMBERS_FONT_SIZE);
		clock.numbers[i].setFillColor(Color::Black);
		clock.numbers[i].setStyle(Text::Bold);
		clock.numbers[i].setOrigin(clock.numbers[i].getGlobalBounds().width / 2, clock.numbers[i].getGlobalBounds().height);
		clock.numbers[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);
		angle += ((2 * PI) / COUNT_OF_NUMBERS);
	}
}
void CreateMusic(Clocks & clock)
{
	clock.clockTick.setLoop(true);
	clock.clockTick.play();
}
bool LoadFont(Clocks & clock)
{
	return (clock.font.loadFromFile("resources/arial.ttf"));
}