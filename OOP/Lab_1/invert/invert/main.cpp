#include "stdafx.h"
#include "invert.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (!IsValidNumArguments(argc))
	{
		return 1;
	}

	ifstream inputFile;
	inputFile.open(argv[1]);
	ofstream outputFile(argv[2]);

	if (!AreValidInputAndOutputFiles(argv, inputFile, outputFile))
	{
		return 1;
	}
	Matrix matrix;
	ReadMatrixFromFile(inputFile, matrix);
	double determ = FindDeterminantOfMatrix(matrix);
	if (determ == 0)
	{
		outputFile << "Invert matrix doesn't exist, because determinant = 0\n";
		return 1;
	}
	Matrix inverseMatrix;
	InverseOfMatrix(matrix, inverseMatrix, determ);
	PrintInvMatrix(inverseMatrix, outputFile);
	if (!outputFile.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0;
}