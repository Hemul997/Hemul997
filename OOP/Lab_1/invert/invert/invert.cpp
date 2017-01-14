// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "invert.h"

using namespace std;

void ReadMatrixFromFile(ifstream &input, Matrix &mainMatrix)
{
	for (int i = 0; i < MATRIX_ROW_NUM; ++i)
	{
		for (int j = 0; j < MATRIX_COL_NUM; ++j)
		{
			input >> mainMatrix[i][j];
		}
	}
};

double FindDeterminantOfMatrix(Matrix  const&matrix)// ����� ������������
{
	return  (matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[0][0] * matrix[1][2] * matrix[2][1]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]);
};

double FindDetermOfMinor(double a11, double a12, double a21, double a22) // ������������ ����������
{
	double determ = 0;
	determ = (a11*a22) - (a12*a21);
	return determ;
};

void PrintInvMatrix(Matrix const &matrix, ofstream &output)
{
	for (int i = 0; i < MATRIX_ROW_NUM; ++i)
	{
		for (int j = 0; j < MATRIX_COL_NUM; ++j)
		{
			output << fixed << setprecision(3) << matrix[i][j] << ' ';
		}
		output << endl;
	}
};

double FindMinor(Matrix &matrix, const int &i, const int &j)
{
	double minor;
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
	minor = FindDetermOfMinor(valueOfMinor[0], valueOfMinor[1], valueOfMinor[2], valueOfMinor[3]);
	return minor;
};

bool IsNeedInverseSign(const int& columnNumber, const int & rowNumber)
{
	int Summ = columnNumber + rowNumber;
	return ((Summ % 2 != 0) && (Summ != 0));
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