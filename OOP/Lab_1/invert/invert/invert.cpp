// lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "invert.h"

using namespace std;

bool IsValidNumArguments(int argc)
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: invert.exe <input file> <output file>\n";
		return false;
	}
	return true;
}

void ReadMatrixFromFile(ifstream &inputFile, Matrix &mainMatrix)
{
	for (int i = 0; i < MATRIX_ROW_NUM; ++i)
	{
		for (int j = 0; j < MATRIX_COL_NUM; ++j)
		{
			inputFile >> mainMatrix[i][j];
		}
	}
};

double FindDeterminantOfMatrix(Matrix const &matrix)// ����� ������������
{
	return  (matrix[0][0] * matrix[1][1] * matrix[2][2]
				+ matrix[0][1] * matrix[1][2] * matrix[2][0]
				+ matrix[0][2] * matrix[1][0] * matrix[2][1]
				- matrix[0][0] * matrix[1][2] * matrix[2][1]
				- matrix[0][1] * matrix[1][0] * matrix[2][2]
				- matrix[0][2] * matrix[1][1] * matrix[2][0]);
};

double FindDeterminantOfMinor(double a11, double a12, double a21, double a22) // ������������ ����������
{
	return (a11*a22) - (a12*a21);
};

void PrintInvertMatrix(Matrix const &matrix, ofstream &outputFile)
{
	for (int i = 0; i < MATRIX_ROW_NUM; ++i)
	{
		for (int j = 0; j < MATRIX_COL_NUM; ++j)
		{
			outputFile << fixed << setprecision(3) << matrix[i][j] << ' ';
		}
		outputFile << endl;
	}
};

double FindMinor(Matrix &matrix, int i, int j)
{
	double valueOfMinor[4];
	int index = 0;
	for (int row = 0; row < MATRIX_ROW_NUM; ++row)
	{
		if (row != i) // ����� �� ������
		{
			for (int column = 0; column < MATRIX_COL_NUM; ++column)
			{
				if (column != j) // ����� �� �������
				{
					valueOfMinor[index] = matrix[row][column];
					++index;
				}
			}
		}
	}
	return FindDeterminantOfMinor(valueOfMinor[0], valueOfMinor[1], valueOfMinor[2], valueOfMinor[3]);
};

bool IsNeedInverseSign(int columnNumber,int rowNumber)
{
	int sumOfNumbers = columnNumber + rowNumber;
	return ((sumOfNumbers % 2 != 0) && (sumOfNumbers != 0));
}

void InverseOfMatrix(Matrix &matrix, Matrix &invMatrix, const double determ)
{
	for (int i = 0; i < MATRIX_ROW_NUM; ++i)
	{
		for (int j = 0; j < MATRIX_COL_NUM; ++j)
		{
			invMatrix[j][i] = (1 / determ) * FindMinor(matrix, i, j);
			if (IsNeedInverseSign(j, i))
			{
				invMatrix[j][i] = invMatrix[j][i] * (-1);
			}
		}
	}
}