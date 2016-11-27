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

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PI = 3.1415927;
const int CLOCK_CIRCLE_SIZE = 250;
const int CLOCK_CIRCLE_THICKNESS = 2;
int x, y;
const int NUMBER_POINTS = 60;

const int HOUR_HAND_WIDTH = 5;
const int HOUR_HAND_HEIGHT = 180;

const int MINUTE_HAND_WIDTH = 3;
const int MINUTE_HAND_HEIGHT = 240;

const int SECOND_HAND_WIDTH = 2;
const int SECOND_HAND_HEIGHT = 250;

struct Clocks
{
	Vector2f windowCenter;
	CircleShape dot[NUMBER_POINTS];
	ContextSettings settings;
	RenderWindow window;
	CircleShape clockCircle;
	CircleShape centerCircle;
	RectangleShape hourHand;
	RectangleShape minuteHand;
	RectangleShape secondsHand;
	Music clockTick;
	Texture clockImage;
	Texture clockBrand;

};
void CreateHands(Clocks & clock);
////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
	// Define some variables and constants
	float angle = 0.0;
	

	// Set multisampling level
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Create the window of the application
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", Style::Close, settings);

	// Define windowCenter which gets the center of the window here, right after creating window
	Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	// Create a list for clock's dots
	CircleShape dot[NUMBER_POINTS];

	// Create dots and place them to very right positions
	for (int i = 0; i < NUMBER_POINTS; i++)
	{
		x = (CLOCK_CIRCLE_SIZE - 10) * cos(angle);
		y = (CLOCK_CIRCLE_SIZE - 10) * sin(angle);

		if (i % 5 == 0)
			dot[i] = CircleShape(3);
		else
			dot[i] = CircleShape(1);
		dot[i].setFillColor(Color::Black);
		dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
		dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		angle = angle + ((2 * PI) / NUMBER_POINTS);
	}

	// Create outline of the clock
	CircleShape clockCircle(CLOCK_CIRCLE_SIZE);

	clockCircle.setPointCount(100);
	clockCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
	clockCircle.setOutlineColor(Color::Black);
	clockCircle.setOrigin(clockCircle.getGlobalBounds().width / 2, clockCircle.getGlobalBounds().height / 2);
	clockCircle.setPosition(window.getSize().x / 2 + CLOCK_CIRCLE_THICKNESS, window.getSize().y / 2 + CLOCK_CIRCLE_THICKNESS);

	// Crate another circle for center
	CircleShape centerCircle(10);

	centerCircle.setPointCount(100);
	centerCircle.setFillColor(Color::Red);
	centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
	centerCircle.setPosition(windowCenter);

	// Create hour, minute, and seconds hands
	RectangleShape hourHand(Vector2f(HOUR_HAND_WIDTH, HOUR_HAND_HEIGHT));
	RectangleShape minuteHand(Vector2f(MINUTE_HAND_WIDTH, MINUTE_HAND_HEIGHT));
	RectangleShape secondsHand(Vector2f(SECOND_HAND_WIDTH, SECOND_HAND_HEIGHT));

	/*hourHand.setFillColor(Color::Black);
	minuteHand.setFillColor(Color::Black);
	secondsHand.setFillColor(Color::Red);

	hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
	minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
	secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);

	hourHand.setPosition(windowCenter);
	minuteHand.setPosition(windowCenter);
	secondsHand.setPosition(windowCenter);*/
	void CreateHands(Clocks & clock);

	// Create sound effect
	Music clockTick;
	if (!clockTick.openFromFile("resources/clockSound.wav"))
		return EXIT_FAILURE;
	clockTick.setLoop(true);
	clockTick.play();

	// Use a part of SFML logo as clock brand
	Texture clockBrand;
	if (!clockBrand.loadFromFile("resources/clock-brand.png"))
	{
		return EXIT_FAILURE;
	}

	Sprite clockBrandSprite;
	clockBrandSprite.setTexture(clockBrand);
	clockBrandSprite.setOrigin(clockBrandSprite.getTextureRect().left + clockBrandSprite.getTextureRect().width / 2.0f,
		clockBrandSprite.getTextureRect().top + clockBrandSprite.getTextureRect().height / 2.0f);

	clockBrandSprite.setPosition(window.getSize().x / 2, window.getSize().y - 100);


	// Create clock background
	Texture clockImage;
	if (!clockImage.loadFromFile("resources/clock-image.png"))
	{
		return EXIT_FAILURE;
	}
	clockCircle.setTexture(&clockImage);
	clockCircle.setTextureRect(IntRect(40, 0, 500, 500));

	while (window.isOpen())
	{
		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			// Window closed: exit
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		// Get system time
		time_t currentTime = std::time(NULL);

		struct tm * ptm = localtime(&currentTime);

		hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
		minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
		secondsHand.setRotation(ptm->tm_sec * 6);

		// Clear the window
		window.clear(Color::White);

		// Draw all parts of clock
		window.draw(clockCircle);

		for (int i = 0; i<60; i++)
		{
			window.draw(dot[i]);
		}

		window.draw(clockBrandSprite);
		window.draw(hourHand);
		window.draw(minuteHand);
		window.draw(secondsHand);
		window.draw(centerCircle);

		// Display things on screen
		window.display();
	}

	return EXIT_SUCCESS;
}

void CreateHands(Clocks & clock)
{
	clock.hourHand.setSize(Vector2f(HOUR_HAND_WIDTH, HOUR_HAND_HEIGHT));
	clock.minuteHand.setSize(Vector2f(MINUTE_HAND_WIDTH, MINUTE_HAND_HEIGHT));
	clock.secondsHand.setSize(Vector2f(SECOND_HAND_WIDTH, SECOND_HAND_HEIGHT));
	clock.hourHand.setFillColor(Color::Black);
	clock.minuteHand.setFillColor(Color::Black);
	clock.secondsHand.setFillColor(Color::Red);

	clock.hourHand.setOrigin(clock.hourHand.getGlobalBounds().width / 2, clock.hourHand.getGlobalBounds().height - 25);
	clock.minuteHand.setOrigin(clock.minuteHand.getGlobalBounds().width / 2, clock.minuteHand.getGlobalBounds().height - 25);
	clock.secondsHand.setOrigin(clock.secondsHand.getGlobalBounds().width / 2, clock.secondsHand.getGlobalBounds().height - 25);

	clock.hourHand.setPosition(clock.windowCenter);
	clock.minuteHand.setPosition(clock.windowCenter);
	clock.secondsHand.setPosition(clock.windowCenter);
}

void CreateDisplay(Clocks & clock)
{

}
void CreateCircleForCenter(Clocks & clock)
{

}