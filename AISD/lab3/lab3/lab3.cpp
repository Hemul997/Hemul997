//�� 22 ������ ������
//18. �   ���������   ���������   ����������   ��   ���������
//�����������  ������ ����� ���������.� ������ �� ��� ��������
//�������� ������� ������������� ����������, ���������� �  ����
//�������  �������  ��  �������, �������  �����  �����  � �����
//������� �����������.���������� ����� ���� ����������� � �����
//�������������   �������, ��   ��������, �  ������������  �
//����������������  �����������  ��������.��   ������   ������
//�������� ����� ������������� ������� �������, ������� ��������
//������  ���������, �  ���  ������  ���������  ������   ������
//�����������  �  ���  �����������.���������  ���������  �����
//������������  ����������  �����������.������  ������   �����
//���������(12).

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
#include <regex>
#include <locale>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <algorithm>
#include <list>

const int DL = 256;
const int MAX_NUMBER_COMPUTER = 10;

using namespace std;

struct Tree
{
	string name;
	int urov;
	Tree *fath;         // ���� � �������� ������
	Tree *left;
	Tree *right;
	bool Tlist;
};
struct Computers
{
	int Number;
	string audiotory;
};
Tree *root1; Tree *root2;

ostream & operator<<(ostream &out, const list<string> & obj)
{
	for (auto it = obj.begin(); it != obj.end(); ++it)
	{
		out << *it << ' ';
	}
	return out;
}

void read_from_file(FILE *F, Tree **r);  // ������ �� �����, ������������ ������
void back_from_bin(Tree *p);            // ������ �������� ������ �� ���������
long int Count(Tree *q); // ������� ����� � ������
void GetComputersFromAuditories(Tree *t, ofstream &outFile);
void GetComputersFromFaculties(Tree *t, ofstream &outFile);
vector<Computers> ReadToVector(ifstream &inputFile);
void outVector(vector<Computers> &computers);
bool findInVector(int number, vector<Computers> &computers1);
bool findAuditories(vector<Computers> &computers1, vector<Computers> &computers2, list<string> &auditories);
bool findInVectorAud(int findNumber, string &findAud, vector<Computers> &computers1, vector<Computers> &computers2);
int main(int argc, char* argv[])
{
	vector<Computers> computers1;
	vector<Computers> computers2;
	list<string> outList;
	root1 = 0;
	root2 = 0;
	FILE *Fin1, *Fin2;
	setlocale(LC_ALL, "rus");
	Fin1 = fopen("tree1.txt", "r");
	Fin2 = fopen("tree2.txt", "r");
	ofstream outFile("out.txt");
	ofstream outFile2("out2.txt");
	if ((Fin1 == NULL) || (Fin2 == NULL))
	{
		cout << "\nCan not open file";
		cin.get();
		return -1;
	}

	read_from_file(Fin1, &root1);
	read_from_file(Fin2, &root2);
	back_from_bin(root1);
	back_from_bin(root2);
	fclose(Fin1);
	fclose(Fin2);
	cin.get();
	cout << "���-�� �������:" << Count(root1) << endl;
	cout << "���-�� �������:"<< Count(root2) << endl;
	cin.get();
	GetComputersFromFaculties(root1, outFile);
	GetComputersFromAuditories(root2, outFile2);
	outFile.close();
	outFile2.close();
	ifstream inpFile("out.txt");
	ifstream inpFile2("out2.txt");
	cin.get();
	computers1 = ReadToVector(inpFile);
	computers2 = ReadToVector(inpFile2);
	outVector(computers1);
	outVector(computers2);
	if (!findAuditories(computers1, computers2, outList))
	{
		cout << "Auditories has not been found";
		return EXIT_FAILURE;
	}
	cout << "Next auditories belong to several faculties:\n"<< outList << endl;
	return EXIT_SUCCESS;
}

void read_from_file(FILE *F, Tree **r)
{
	char buf[DL];
	int i, k, m;
	size_t len;
	Tree *p, *q, *t;       // *root = 0 
	m = 0;                 // ������� �������
	t = 0;
	while (!feof(F))
	{
		k = fscanf(F, "%s", buf);
		len = strlen(buf);
		if (len == 0) break;            // ���� ����� ����� � ��������� ������
		k = 0;
		while (buf[k] == '.')
		{
			++k;     // k-������� �������
		}
		p = new Tree;
		for (size_t i = 0; i < len; ++i)
		{
			if (buf[i] != '.')
			{
				p->name += buf[i];
			}
		}
		p->name += '\0';                  // ���� ����� ����� � ��������� ������
		p->urov = k;
		p->left = 0;
		p->right = 0;
		if (k == 0)                    // ������
		{
			*r = p;
			t = *r;
			continue;
		}
		if (k > m)                  // ������� �� ��������� �������
		{
			t->left = p;
			p->fath = t;
		}
		else
			if (k == m)            // ��� �� �������
			{
				t->right = p;
				p->fath = t->fath;  // ���� ��� ��
			}
			else        // ������ �� ������ �� m-k �������
			{
				q = t;
				for (i = 0; i < m - k; i++) q = q->fath;
				// q - ���������� ������� ���� �� ������
				p->fath = q->fath;   // ���� ��� ��, ��� � �����
				q->right = p;
			}
		m = k;      // ������� �������
		t = p;      // ������� �������
	}
}

long int Count(Tree *q)
{
	return q == NULL ? 0 : 1 + Count(q->left) + Count(q->right);
}

void back_from_bin(Tree *p)
{
	int i;
	string str, countUrov = "";
	if (p)
	{
		for (i = 0; i < p->urov; ++i) countUrov += '.';
		str = p->name;
		str += '\0';
		cout << countUrov << str << endl;
		back_from_bin(p->left);
		back_from_bin(p->right);
	}
}

void GetComputersFromAuditories(Tree *t , ofstream &outFile)
{
	int comp;
	char num;
	if (t)
	{
		GetComputersFromAuditories(t->left, outFile);
		GetComputersFromAuditories(t->right, outFile);
		if (!t->right || !t->left)
		{
			num = t->name[0];
			if (isdigit(num) && t->urov > 2)
			{
				comp = stoi(t->name);
				outFile << comp << ' ' << t->fath->name << endl;
			}
		}
	}
}
void GetComputersFromFaculties(Tree *t, ofstream &outFile)
{
	int comp;
	char num;
	if (t)
	{
		GetComputersFromFaculties(t->left, outFile);
		GetComputersFromFaculties(t->right, outFile);
		if (!t->right || !t->left)
		{
			num = t->name[0];
			if (isdigit(num) && t->urov > 2)
			{
				comp = stoi(t->name);
				if (t->urov == 4)
				{
					outFile << comp << ' ' << t->fath->fath->name << endl;
				}
				if (t->urov == 5)
				{
					outFile << comp << ' ' << t->fath->fath->fath->name << endl;
				}
				if (t->urov == 3)
				{
					outFile << comp << ' ' << t->fath->name << endl;
				}
			}
		}
	}
}
vector<Computers> ReadToVector(ifstream &inputFile)
{
	vector<Computers> vector;
	Computers computers;
	while (!inputFile.eof())
	{
		inputFile >> computers.Number >> computers.audiotory;
		if (!inputFile.eof())
		{
			vector.push_back(computers);
		}
	}
	return vector;
}
void outVector(vector<Computers> &computers)
{
	for (auto it = computers.begin(); it != computers.end(); ++it)
	{
		cout << it->Number << ' ' << it->audiotory << endl;
	}
}
bool findAuditories(vector<Computers> &computers1, vector<Computers> &computers2, list<string> &auditories)
{
	for (auto it = computers2.begin(); it != computers2.end(); ++it)
	{
		if (findInVector(it->Number, computers1) )
		{
			auditories.push_back(it->audiotory);
		}
		else
		{
			if (findInVectorAud(it->Number, it->audiotory, computers1, computers2))
			{
				auditories.push_back(it->audiotory);
			}
		}
		
	}
	if (!auditories.empty())
	{
		auditories.sort();
		auditories.unique();
		return true;
	}
	return false;
	
}
bool findInVector(int number , vector<Computers> &computers1)
{
	auto it = std::find_if(computers1.begin(), computers1.end(), [&](const Computers & s)->bool { return s.Number == number; });
	auto rev_it = std::find_if(computers1.rbegin(), computers1.rend(), [&](const Computers & s)->bool { return s.Number == number; });
	if (it != --rev_it.base())
	{
		return true;
	}
	
	return false;
}
bool findInVectorAud(int findNumber, string &findAud, vector<Computers> &computers1, vector<Computers> &computers2)
{
	int nextComp;
	string nextAud = "";
	auto it = computers2.begin();
	while (it != computers2.end())
	{
		if (it->Number == findNumber && it != computers2.end())
		{
			++it;
			if (it != computers2.end())
			{
				nextComp = it->Number;
				nextAud = it->audiotory;
				break;
			}
			else
			{
				return false;
			}
		}
		++it;
	}
	if (nextAud == findAud)
	{
		auto it = std::find_if(computers1.begin(), computers1.end(), [&](const Computers & s)->bool { return s.Number == findNumber; });
		auto it2 = std::find_if(computers1.begin(), computers1.end(), [&](const Computers & s)->bool { return s.Number == nextComp; });
		if (it->audiotory != it2->audiotory)
		{
			return true;
		}
	}
	return false;
}