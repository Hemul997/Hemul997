#pragma once
#include "stdafx.h"

static const int ARGUMENTS_COUNT = 5;
static const std::string OPERATION_CRYPT = "crypt";
static const std::string OPERATION_DECRYPT = "decrypt";

void Crypt(std::ifstream &, std::ofstream &, int);
void Decrypt(std::ifstream &, std::ofstream &, int);
bool IsValidNumArguments(int);
bool IsValidOperation(const std::string &);
bool IsValidKey(int);
bool AreValidInputAndOutputFiles(char *[], std::ifstream &, std::ofstream &);
char MixBitsForCrypt(const char &);
char MixBitsForDecrypt(const char &);
bool FailedToSaveData(std::ofstream &);