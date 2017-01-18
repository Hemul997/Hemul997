#include "stdafx.h"
#include "labirint.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count:\n"
			<< "Usage: invert.exe <input file> <output file>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream output(argv[2]);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	Point startPoint;
	Point endPoint;
	Map map;

	ReadMap(input, map);

	if (!FindStartAndEndPoint(map, startPoint, endPoint))
	{
		cout << "Find start or end point error\n";
		return 1;
	}

	DisseminateWave(map, startPoint, endPoint);
	RecoveryPath(map, startPoint, endPoint);
	PrintMap(output, map);

	return 0;
}