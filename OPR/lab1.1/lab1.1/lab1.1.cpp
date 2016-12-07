// HeightOfJump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

float CalculateTimeOfMaxHeight(const float &G, int heightOfJump);
void PrintJumpTimePoints(const float &G, const float &MULTIPLIER, float timeOfMaxHeight);
void CalculateHeight(const float &G, const float &MULTIPLIER, float &v0, float time);
void CalcutateLanding(const float &G, const float &MULTIPLIER, float &v0, float &timeOfMaxHeight);


int main(int, char *[])
{
	const float G = 9.8f;
	const float MULTIPLIER = 0.5;
	//float timeOfMaxHeight;
	
	int heightOfJump = 0;

	printf("Height of max jump: ");
	if (0 == scanf("%d", &heightOfJump))
	{
		printf("\n" "expected floating-point number" "\n");
		exit(1);
	}
	if (heightOfJump < 0)
	{
		printf("\n" "expected invalid number" "\n");
		exit(1);
	}
	
	PrintJumpTimePoints(G, MULTIPLIER, CalculateTimeOfMaxHeight(G, heightOfJump));
	
	return 0;
}
float CalculateTimeOfMaxHeight(const float &G, int heightOfJump)
{
	float timeOfMaxHeight;
	timeOfMaxHeight = sqrt(heightOfJump * 2 / G);
	printf("Time of max height=%f\n", timeOfMaxHeight);
	return timeOfMaxHeight;
}
void PrintJumpTimePoints(const float &G, const float &MULTIPLIER, float timeOfMaxHeight)
{
	float v0 = G * timeOfMaxHeight;
	bool foundMaxHeight = false;

	for (float currentTime = 0; currentTime < timeOfMaxHeight * 2; currentTime += 0.1f)
	{
		if (currentTime > timeOfMaxHeight && !foundMaxHeight)
		{
			foundMaxHeight = true;
			CalculateHeight(G, MULTIPLIER, v0, timeOfMaxHeight);
		}
		CalculateHeight(G, MULTIPLIER, v0, currentTime);
	}
	CalcutateLanding(G, MULTIPLIER, v0, timeOfMaxHeight);
}
void CalculateHeight(const float &G, const float &MULTIPLIER, float &v0, float time)
{
	float currentHeight = v0 * time - MULTIPLIER * G * time * time;
	printf("Time = %f, height = %f\n", time, currentHeight);
}
void CalcutateLanding(const float &G, const float &MULTIPLIER, float &v0, float &timeOfMaxHeight)
{
	float currentHeight = v0 * (timeOfMaxHeight * 2) - MULTIPLIER * G * (timeOfMaxHeight * 2) * (timeOfMaxHeight * 2);
	printf("Time = %f, height = %f\n", timeOfMaxHeight * 2, currentHeight);
}