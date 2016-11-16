#include "CrossSet.h"
using namespace std;
int main()
{
	set<int> firstSet, secondSet, resultSet;
	int num;
	cout << "Enter the number\n";
	cin >> num;
	/*firstSet = InsertToFirstSet(num);
	secondSet = InsertToSecondSet(num);*/
	InsertToSets(firstSet, secondSet, num);
	resultSet = CrossSet(firstSet, secondSet);
	PrintSet(firstSet);
	PrintSet(secondSet);
	PrintSet(resultSet);
	return 0;
}