// UchebnyiPlan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include <Windows.h>

using namespace std;
        //макс длина слова
struct mylist {
	string field;    // поле данных
	struct mylist *ptr; // указатель на следующий элемент
};
mylist *init(string a) {     // а- значение первого узла
	mylist *lst;
	// выделение памяти под корень списка
	lst = (struct mylist*)malloc(sizeof(struct mylist));
	lst->field = a;
	lst->ptr = NULL;  // это последний узел списка
	return(lst);
}
void init(string const & a, mylist *lst) 
{     // а- значение первого узла
	lst = new mylist(); // выделение памяти под корень списка
	lst->field = a;
	lst->ptr = NULL;  // это последний узел списка
}
mylist *addelem(mylist *lst, string number) {
	mylist *temp, *p;
	temp = new mylist();
	p = lst->ptr;  // сохранение указателя на следующий узел
	lst->ptr = temp;  // предыдущий узел указывает на создаваемый
	temp->field = number;  // сохранение поля данных добавляемого узла
	temp->ptr = p;    // созданный узел указывает на следующий элемент
	return temp;
}
void deletelem(mylist *lst, mylist *root) {
	struct mylist *temp;
	temp = root;
	while (temp->ptr != lst)  // просматриваем список начиная с корня
	{    // пока не найдем узел, предшествующий lst
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr; // переставляем указатель
	free(lst);  // освобождаем память удаляемого узла
}
void deletehead(mylist *root) {
	struct mylist *temp;
	temp = root->ptr;
	free(root);   // освобождение памяти текущего корня 
}
void listprint(mylist *lst) {
	struct mylist *p;
	p = lst;
	do {
		cout << p->field; // вывод значения элемента p
		p = p->ptr; // переход к следующему узлу
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