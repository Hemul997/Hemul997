#pragma once

static const int ARGUMENTS_COUNT = 5;
static const std::string OPERATION_CRYPT = "crypt";
static const std::string OPERATION_DECRYPT = "decrypt";

void Crypt(std::ifstream &input, std::ofstream &output, int key);
void Decrypt(std::ifstream &input, std::ofstream &output, int key);
bool IsValidNumArguments(int argc);
bool IsValidOperation(const std::string &operation);
bool IsValidKey(int key);
bool FailedToSaveData(std::ofstream &output);
bool IsNumber(char *Symbol);