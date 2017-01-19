#include "stdafx.h"
#include "crypt.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (!IsValidNumArguments(argc))
	{
		return 1;
	}

	string operation = argv[1];
	if (!IsValidOperation(operation))
	{
		return 1;
	}

	ifstream input(argv[2], ios::binary | ios::in);
	ofstream output(argv[3], ios::binary | ios::out);

	if (!AreValidInputAndOutputFiles(argv, input, output))
	{
		return 1;
	}
	if (!IsNumber(argv[4]))
	{
		return 1;
	}
	int key = atoi(argv[4]);
	if (!IsValidKey(key))
	{
		return 1;
	}

	(operation == OPERATION_CRYPT) ? Crypt(input, output, key) : Decrypt(input, output, key);

	if (FailedToSaveData(output))
	{
		return 1;
	}

	input.close();
	output.close();

	return 0;
}