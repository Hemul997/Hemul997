#pragma once
#define MATRIX_ROW_NUM 3
#define MATRIX_COL_NUM 3

typedef double Matrix[MATRIX_ROW_NUM][MATRIX_COL_NUM];

bool IsValidNumArguments(int argc);
void ReadMatrixFromFile(std::ifstream &inputFile, Matrix &mainMatrix);
double FindDeterminantOfMatrix(Matrix const&matrix);// метод треугольника
void InverseOfMatrix(Matrix &matrix, Matrix &invMatrix, const double determ);
void PrintInvertMatrix(Matrix const &matrix, std::ofstream &output);