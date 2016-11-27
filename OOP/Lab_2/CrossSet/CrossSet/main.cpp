#include "CrossSet.h"
using namespace std;
int main()
{
	set<int> firstSet, secondSet, resultSet;
	int num;
	cout << "Enter the number\n";
	if (!(cin >> num))
	{
		cout << "incorrect input";
		return 1;
	}
	InsertToSets(firstSet, secondSet, num);
	resultSet = CrossSet(firstSet, secondSet);
	PrintSet(firstSet);
	PrintSet(secondSet);
	PrintSet(resultSet);
	return 0;
}