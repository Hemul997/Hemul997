#pragma once


struct Point
{
	int x;
	int y;
};

const int MAP_SIZE = 100;
typedef int Map[MAP_SIZE][MAP_SIZE];
const int WALL = -1, BLANK = -2, PATH = -3, START = 0, END = -4;
static Point direction[4] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };


void DrawEmptyMap(Map map);
void ReadMap(std::ifstream & inputFile, Map map);
void PrintMap(std::ofstream & outputFile, Map map);
bool FindStartAndEndPoint(Map map, Point & startPoint, Point & endPoint);
void DisseminateWave(Map map, Point & startPoint, Point & endPoint);
void RecoveryPath(Map map, Point & startPoint, Point & endPoint);