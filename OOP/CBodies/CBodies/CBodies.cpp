#include "stdafx.h"
#include "Controller.h"

using namespace std;

int main()
{
	vector<shared_ptr<CBody>> bodies;
	CBodyController controller(bodies, cin, cout);
	controller.Help();
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		controller.HandleCommand();
	}

	controller.PrintBodies(bodies);
	controller.FindBodyWithMaxMass(bodies);
	controller.FindBodyWithMinWeightInWater(bodies);

	return 0;
}