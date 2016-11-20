// HeightOfJump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// This program takes max jump height from input and prints
// jump height for every time point with step 0.1 seconds.
// Program should print all time points when height is min and max.
//
// TODO: Fix all warnings on high warning level (/W4, -Wall -Wextra).
// TODO: Rename variables and split to several functions,
// see also https://ps-group.github.io/sfml/coding_conventions.html
// TODO: fix negative height values, fix heigh values higher than max height.
int main(int, char *[])
{
	const float g = 9.8f;
	const float MULTIPLIER = 0.5;
	float timeOfMaxHeight;
	int heightOfMaxJump;

	printf("Height of max jump: ");
	if (0 == scanf("%d", &heightOfMaxJump))
	{
		printf("\n" "expected floating-point number" "\n");
		exit(1);
	}
	// T - time point when height is at maximum.
	// t - current time point
	// v(t) == v0 - g * t
	// v0 = g * T
	// s(t) == v0 * t - 0.5 * g * t * t
	timeOfMaxHeight = sqrt(heightOfMaxJump * 2 / g);
	printf("Time of max height=%f\n", timeOfMaxHeight);
	bool flag = false;
	for (float currentTime = 0; currentTime < timeOfMaxHeight * 2; currentTime += 0.1f)
	{
		if (currentTime > timeOfMaxHeight && !flag)
		{
			flag = true;
			float V0 = g * timeOfMaxHeight;
			float currentHeight = V0 * timeOfMaxHeight - MULTIPLIER * g * timeOfMaxHeight * timeOfMaxHeight;
			printf("Time of max height=%f, current height=%f\n", timeOfMaxHeight, currentHeight);
		}
		float V0 = g * timeOfMaxHeight;
		float currentHeight = V0 * currentTime - MULTIPLIER * g * currentTime * currentTime;
		printf("Current time=%f, Current height=%f\n", currentTime, currentHeight);
	}

	float V0 = g * timeOfMaxHeight;
	float currentHeight = V0 * (timeOfMaxHeight * 2) - MULTIPLIER * g * (timeOfMaxHeight * 2) * (timeOfMaxHeight * 2);
	printf("Current time=%f, Current height=%f\n", timeOfMaxHeight * 2, currentHeight);


	return 0;
}

