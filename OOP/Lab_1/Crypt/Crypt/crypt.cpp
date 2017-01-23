// crypt.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "crypt.h"

using namespace std;

bool FailedToSaveData(ofstream &output)
{
	bool error = false;
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		error = true;
	}
	return error;
}

bool IsValidNumArguments(int argc)
{
	bool success = true;
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: crypt.exe (crypt/decrypt) <input file> <output file> <key> \n";
		success = false;
	}
	return success;
}

bool IsValidOperation(const string &operation)
{
	bool success = true;
	if ((operation != OPERATION_CRYPT) && (operation != OPERATION_DECRYPT))
	{
		cout << "Invalid operation\n";
		success = false;
	}
	return success;
}

bool AreValidInputAndOutputFiles(char * argv[], ifstream &inputFile, ofstream &outputFile)
{
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading\n";
		return  false;
	}
	if (inputFile.peek() == ifstream::traits_type::eof())
	{
		cout << "File " << argv[2] << " is empty" << endl;
		return  false;
	}
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[3] << " for writing" << endl;
		return false;
	}
	return true;
}

bool IsValidKey(int key)
{
	const int MAX_KEY = 255;
	const int MIN_KEY = 0;
	bool success = true;
	if ((key < MIN_KEY) || (key > MAX_KEY))
	{
		cout << "Failed key: " << key << endl;
		success = false;
	}
	return success;
}

char MixBitsForCrypt(const char &value)
{
	char newValue = '\0';
	int currentRank = 0x80;

	newValue += ((value & (currentRank)) >> 2);

	newValue += ((value & (currentRank >>= 1)) >> 5);

	newValue += ((value & (currentRank >>= 1)) >> 5);

	newValue += ((value & (currentRank >>= 1)) << 3);

	newValue += ((value & (currentRank >>= 1)) << 3);

	newValue += ((value & (currentRank >>= 1)) << 2);

	newValue += ((value & (currentRank >>= 1)) << 2);

	newValue += ((value & (currentRank >>= 1)) << 2);
	return newValue;
}

void Crypt(ifstream &input, ofstream &output, int key)
{
	char value;
	while (input.read(&value, sizeof value))
	{
		value ^= key;
		value = MixBitsForCrypt(value);
		output << value;
	}
}


char MixBitsForDecrypt(const char &value)
{
	char newValue = '\0';
	int currentRank = 0x01;

	newValue += ((value & (currentRank)) << 5);

	newValue += ((value & (currentRank <<= 1)) << 5);

	newValue += ((value & (currentRank <<= 1)) >> 2);

	newValue += ((value & (currentRank <<= 1)) >> 2);

	newValue += ((value & (currentRank <<= 1)) >> 2);

	newValue += ((value & (currentRank <<= 1)) << 2);

	newValue += ((value & (currentRank <<= 1)) >> 3);

	newValue += ((value & (currentRank <<= 1)) >> 3);
	return newValue;
}

void Decrypt(ifstream &input, ofstream &output, int key)
{
	char value;
	while (input.read(&value, sizeof value))
	{
		value = MixBitsForDecrypt(value);
		value ^= key;
		output << value;
	}
}
bool IsNumber(char *Symbol)
{
	return (Symbol[0] >= '0' && Symbol[0] <= '9') ? (true) : (false);
}