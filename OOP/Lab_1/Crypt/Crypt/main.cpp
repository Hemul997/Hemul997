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

	ifstream inputFile(argv[2], ios::binary | ios::in);
	ofstream outputFile(argv[3], ios::binary | ios::out);

	if (!AreValidInputAndOutputFiles(argv, inputFile, outputFile))
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

	(operation == OPERATION_CRYPT) ? Crypt(inputFile, outputFile, key) : Decrypt(inputFile, outputFile, key);

	if (FailedToSaveData(outputFile))
	{
		return 1;
	}

	inputFile.close();
	outputFile.close();

	return 0;
}