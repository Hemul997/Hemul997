#pragma once
#define MATRIX_ROW_NUM 3
#define MATRIX_COL_NUM 3

typedef double Matrix[MATRIX_ROW_NUM][MATRIX_COL_NUM];

bool IsValidNumArguments(int argc);
bool AreValidInputAndOutputFiles(char * argv[], std::ifstream &inputFile, std::ofstream &outputFile);
void ReadMatrixFromFile(std::ifstream &inputFile, Matrix &mainMatrix);
double FindDeterminantOfMatrix(Matrix  const&matrix);// метод треугольника
double FindDetermOfMinor(double a11, double a12, double a21, double a22); // перемножение диагоналей
void PrintInvMatrix(Matrix const &matrix, std::ofstream &output);
double FindMinor(Matrix &matrix, const int &i, const int &j);
void InverseOfMatrix(Matrix &matrix, Matrix &invMatrix, const double determ);