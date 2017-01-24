// crypt.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "crypt.h"

using namespace std;

bool FailedToSaveData(ofstream &output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return true;
	}
	return false;
}

bool IsValidNumArguments(int argc)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: crypt.exe (crypt/decrypt) <input file> <output file> <key> \n";
		return false;
	}
	return true;
}

bool IsValidOperation(const string &operation)
{
	if ((operation != OPERATION_CRYPT) && (operation != OPERATION_DECRYPT))
	{
		cout << "Invalid operation\n";
		return false;
	}
	return true;
}

bool IsValidKey(int key)
{
	const int MAX_KEY = 255;
	const int MIN_KEY = 0;
	if ((key < MIN_KEY) || (key > MAX_KEY))
	{
		cout << "Failed key: " << key << endl;
		return false;
	}
	return true;
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
bool IsNumber(char *symbol)
{
	return (symbol[0] >= '0' && symbol[0] <= '9') ? (true) : (false);
}