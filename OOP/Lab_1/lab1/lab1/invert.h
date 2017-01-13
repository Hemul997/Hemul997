#pragma once
#include "stdafx.h"

#define MATRIX_ROW_NUM 3
#define MATRIX_COL_NUM 3

typedef double Matrix[MATRIX_ROW_NUM][MATRIX_COL_NUM];

void ReadMatrixFromFile(std::ifstream &input, Matrix &mainMatrix);
double FindDeterminantOfMatrix(Matrix  const&matrix);// метод треугольника
double FindDetermOfMinor(double a11, double a12, double a21, double a22); // перемножение диагоналей
void PrintInvMatrix(Matrix const &matrix, std::ofstream &output);
double FindMinor(Matrix &matrix, const int &i, const int &j);
void InverseOfMatrix(Matrix &matrix, Matrix &invMatrix, const double determ);