#include <cstdlib>
#include "head.h"
#include "head.cpp"
using namespace std;

int main(){
	cout << "If you want to calculate the formula, you'll have to write tht formula without variables.\n";
	char x;

	Formula* head = new Formula;

	read_form(head); // вызов функции считывания формулы с клавиатуры

	cin.get(x);
	if (x != '\n') {
		ErrorMessege(); // если не все данные были считаны, то вывод об ошибке и прерывание программы
		return 0;
	}

	// печать дерева-формулы
	int depth = 0; // переменная для определения текущей глубины формулы
	bool close[50]; 

	for (int k = 1; k <= 49; k++)
		close[k] = 0;

	print(head); // вызов функции печати формулы
	cout << endl;
	build(head, &depth, close); // вызов функции печати дерева-формулы

	 // расчет результата формулы
	int k = 1; // переменная, определяющая наличие терминалов-букв
	int res; // переменная для записи в нее результата

	calculate(head, &res, &k); // вызов функции расчета результата
	print(head); // вызов функции печати формулы
	if (!k){ // печать о невозможности расчета результата из-за наличия в формуле не только цифр
		cout << "\nCalcutation can not be performed.\n";
	}
	else{ // печать результата
		cout << " = " << res << endl;
	}

	// печать дерева-формулы производной
	print(head); // вызов функции печати формулы
	cout << endl;

	cout << "Please, enter the variable: ";
	cin >> x; // запрос на введение переменной, по которой будет считаться производная

	Formula* p;
	p = new Formula; // объявление указателя на голову дерева-производной
	p = proizv(head, x); // вызов функции, создающей список дерев-поризводной
	int depth1 = 0;
	bool close1[50];
	for (int k = 1; k < 50; k++)
		close1[k] = 0;

	build(p, &depth1, close1);

	return 0;
}
