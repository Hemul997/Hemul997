#include "stdafx.h"
#include "invert.h"

using namespace std;

int main(int argc, char * argv[])
{

	if (argc != 3)
	{
		{
			cout << "Invalid arguments count\n"
				<< "Usage: copyfile.exe <input file> <output file>\n";
			return 1;
		}
	}

	ifstream fileOfInput;
	fileOfInput.open(argv[1]);
	if (!fileOfInput.is_open())
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

	Matrix matrix;
	ReadMatrixFromFile(fileOfInput, matrix);
	double determ = FindDeterminantOfMatrix(matrix);
	if (determ == 0)
	{
		output << "Invert matrix doesn't exist, because determinant = 0\n";
		return 1;
	}
	Matrix inverseMatrix;
	InverseOfMatrix(matrix, inverseMatrix, determ);
	PrintInvMatrix(inverseMatrix, output);
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0;
}