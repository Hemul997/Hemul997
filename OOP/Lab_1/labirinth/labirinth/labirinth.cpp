// labirinth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "labirint.h"

using namespace std;

void DrawEmptyMap(Map map)
{
	for (int y = 0; y < MAP_SIZE; ++y)
	{
		for (int x = 0; x < MAP_SIZE; ++x)
		{
			map[y][x] = BLANK;
		}
	}
}

void ReadMap(ifstream & inputFile, Map map)
{
	DrawEmptyMap(map);

	string buffer;

	for (int y = 0; getline(inputFile, buffer) && y < MAP_SIZE; ++y)
	{
		for (int x = 0; x < static_cast<int>(buffer.length()) && x < MAP_SIZE; ++x)
		{
			switch (buffer[x])
			{
			case '#':
				map[y][x] = WALL;
				break;
			case 'A':
				map[y][x] = START;
				break;
			case 'B':
				map[y][x] = END;
				break;
			}
		}
	}
}

void PrintMap(ofstream & outputFile, Map map)
{
	for (int y = 0; y < MAP_SIZE; ++y)
	{
		for (int x = 0; x < MAP_SIZE; ++x)
		{
			switch (map[y][x])
			{
			case WALL:
				outputFile << '#';
				break;
			case START:
				outputFile << 'A';
				break;
			case END:
				outputFile << 'B';
				break;
			case PATH:
				outputFile << '.';
				break;
			default:
				outputFile << ' ';
				break;
			}
		}

		outputFile << "\n";
	}
}

bool FindStartAndEndPoint(Map map, Point & startPoint, Point & endPoint)
{
	bool foundStart = false, foundEnd = false;

	for (int y = 0; y < MAP_SIZE; ++y)
	{
		for (int x = 0; x < MAP_SIZE; ++x)
		{
			if (map[y][x] == START)
			{
				startPoint.x = x;
				startPoint.y = y;
				foundStart = true;
			}

			if (map[y][x] == END)
			{
				endPoint.x = x;
				endPoint.y = y;
				foundEnd = true;
			}
		}
	}

	if (!foundStart || !foundEnd)
	{
		return false;
	}

	return true;
}

void DisseminateWave(Map map, Point & startPoint, Point & endPoint)
{
	if (map[startPoint.y][startPoint.x] == WALL || map[endPoint.y][endPoint.x] == WALL)
	{
		return;
	}

	int step = 0;
	bool foundWay;
	map[startPoint.y][startPoint.x] = 0;

	do
	{
		foundWay = false;
		for (int y = 0; y < MAP_SIZE; ++y)
		{
			for (int x = 0; x < MAP_SIZE; ++x)
			{
				if (map[y][x] == step)
				{
					for (int k = 0; k < 4; ++k)
					{
						int dy = y + direction[k].y, dx = x + direction[k].x;

						if (dy >= 0 && dy < MAP_SIZE && dx >= 0 &&
							dx < MAP_SIZE && (map[dy][dx] == BLANK || map[dy][dx] == END))
						{
							foundWay = true;
							map[dy][dx] = step + 1;
						}
					}
				}
			}
		}
		step++;
	} while (foundWay && map[endPoint.y][endPoint.x] == END);
}

void RecoveryPath(Map map, Point & startPoint, Point & endPoint)
{
	if (map[endPoint.y][endPoint.x] == BLANK)
	{
		return;
	}

	int lengthPath = map[endPoint.y][endPoint.x];
	int x = endPoint.x;
	int y = endPoint.y;

	while (lengthPath > 0)
	{
		--lengthPath;

		for (int k = 0; k < 4; ++k)
		{
			int dy = y + direction[k].y, dx = x + direction[k].x;

			if (dy >= 0 && dy < MAP_SIZE && dx >= 0 &&
				dx < MAP_SIZE && map[dy][dx] == lengthPath)
			{
				map[y][x] = PATH;
				y = y + direction[k].y;
				x = x + direction[k].x;
				break;
			}
		}
	}

	map[startPoint.y][startPoint.x] = START;
	map[endPoint.y][endPoint.x] = END;
}