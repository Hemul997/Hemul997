// UchebnyiPlan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include <Windows.h>

using namespace std;
        //���� ����� �����
struct mylist {
	string field;    // ���� ������
	struct mylist *ptr; // ��������� �� ��������� �������
};
mylist *init(string a) {     // �- �������� ������� ����
	mylist *lst;
	// ��������� ������ ��� ������ ������
	lst = (struct mylist*)malloc(sizeof(struct mylist));
	lst->field = a;
	lst->ptr = NULL;  // ��� ��������� ���� ������
	return(lst);
}
void init(string const & a, mylist *lst) 
{     // �- �������� ������� ����
	lst = new mylist(); // ��������� ������ ��� ������ ������
	lst->field = a;
	lst->ptr = NULL;  // ��� ��������� ���� ������
}
mylist *addelem(mylist *lst, string number) {
	mylist *temp, *p;
	temp = new mylist();
	p = lst->ptr;  // ���������� ��������� �� ��������� ����
	lst->ptr = temp;  // ���������� ���� ��������� �� �����������
	temp->field = number;  // ���������� ���� ������ ������������ ����
	temp->ptr = p;    // ��������� ���� ��������� �� ��������� �������
	return temp;
}
void deletelem(mylist *lst, mylist *root) {
	struct mylist *temp;
	temp = root;
	while (temp->ptr != lst)  // ������������� ������ ������� � �����
	{    // ���� �� ������ ����, �������������� lst
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr; // ������������ ���������
	free(lst);  // ����������� ������ ���������� ����
}
void deletehead(mylist *root) {
	struct mylist *temp;
	temp = root->ptr;
	free(root);   // ������������ ������ �������� ����� 
}
void listprint(mylist *lst) {
	struct mylist *p;
	p = lst;
	do {
		cout << p->field; // ����� �������� �������� p
		p = p->ptr; // ������� � ���������� ����
	} while (p != NULL);
}
int main()
{
	mylist *disciplines;
	/*setlocale(LC_CTYPE, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	string disp;
	getline(cin, disp);
	disciplines = init(disp);
	//init(disp, disciplines);
	listprint(disciplines);
	/*getline(cin, disp);
	disciplines = addelem(disciplines, disp);*/
	return 0;
}