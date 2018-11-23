#include <iostream>
#include <cstdlib>
#include "list.hpp"
using namespace std;

using namespace h_list;
lisp concat(const lisp y, const lisp z);
lisp l_list(const lisp s);

int main() {
	lisp s1, s2;
	cout << "Enter the list:" << endl;
	read_lisp(s1);
	cout << "Input list: " << endl;
	write_seq(s1);
	cout << endl;

	cout << "Linear list = " << endl;
	s2 = l_list(s1);
	write_lisp(s2);
	cout << endl;
	cout << "Freeing memory: " << endl;
	destroy(s1);
	destroy(s2);
	cout << "End!" << endl;
	return 0;
}


lisp concat(const lisp y, const lisp z) {
	if (isNull(y)) return copy_lisp(z);
	else return cons(copy_lisp(head(y)), concat(tail(y), z));
}

lisp l_list(const lisp s) {
	if (isNull(s)) return NULL;
	else if (isAtom(s)) {

		cout << s->node.atom << endl;
		return cons(make_atom(getAtom(s)), NULL);
	}
	else //s - not empty list
		if (isAtom(head(s))) {
			cout << "(";
			write_seq(s);
			cout << ")" << endl;
			cout << endl;
			return cons(make_atom(getAtom(head(s))), l_list(tail(s)));
		}
		else {
			cout << "(";
			write_seq(s);
			cout << ")" << endl;
			cout << endl;
			return concat(l_list(head(s)), l_list(tail(s)));
		}
}

namespace h_list {
	lisp head(const lisp s) {
		if (s != NULL)
			if (!isAtom(s))	return s->node.pair.head;
					else
					{
					cout << "Atom\n";
					exit(1);
					}
		else
		{
			cout << "The list is empty\n";
			exit(1);
		}
	}
	bool isAtom(const lisp s) {						//функция проверяет атомарен ли список
		if (s == NULL) return false;
		else return (s->test);
	}
	bool isNull(const lisp s) {					//функция проверяет список на пустоту
		return s == NULL;
	}

	lisp tail(const lisp s) {
		if (s != NULL)
			if (!isAtom(s))
				return s->node.pair.tail;
			else
			{
				cout << "The list is empty\n";
				exit(1);
			}
	}

	lisp cons(const lisp h, const lisp t) {
		lisp p;
		if (isAtom(t))
		{
			cout << "Atom\n";
			exit(1);
		}
		else {
			p = new s_expr;
			if (p == NULL) {
				cerr << "Not enough memory\n";
				exit(1);
			}
			else {
				p->test = false;
				p->node.pair.head = h;
				p->node.pair.tail = t;
				return p;
			}
		}
	}
	lisp make_atom(const char x) {
		lisp s;
		s = new s_expr;
		s->test = true;
		s->node.atom = x;
		return s;
	}

	void destroy(lisp s) {					//функция освобождения памяти
		if (s != NULL) {
			if (!isAtom(s)) {
				destroy(head(s));
				destroy(tail(s));
			}
			delete s;
		};
	}

	char getAtom(const lisp s) {					//функция дает возможность получить значение атомарного выражения
		if (!isAtom(s))
		{
			cout << " Error - it's not an atom \n";
			exit(1);
		}
		else return (s->node.atom);
	}

	void read_lisp(lisp& y) {					//функция считывания списка
		char x;
		do
			cin >> x;
		while (x == ' ');
		read_s_expr(x, y);
	}

	void read_s_expr(char prev, lisp& y) {						//вспомогательная процедура для read_lisp
		if (prev == ')')
		{
			cout << " Incorrect using a closing bracket\n" << endl;
			exit(1);
		}
		else if (prev != '(') y = make_atom(prev);
		else read_seq(y);
	}

	void read_seq(lisp& y) {					//вспомогательная процедура для read_lisp
		char x;
		lisp p1, p2;
		if (!(cin >> x))
		{
			cout << "Error\n" << endl;
			exit(1);
		}
		else {
			while (x == ' ')
				cin >> x;
			if (x == ')')
				y = NULL;
			else {
				read_s_expr(x, p1);
				read_seq(p2);
				y = cons(p1, p2);
			}
		}
	}

	void write_lisp(const lisp x) {					//функция вывода списка с внешними скобками
		if (isNull(x)) cout << "()";
		else if (isAtom(x)) cout << ' ' << x->node.atom;
		else {
			cout << "(";
			write_seq(x);
			cout << ")";
		}
	}

	void write_seq(const lisp x) {					//функция вывода последовательности элементов списка без скобок
		if (!isNull(x)) {
			write_lisp(head(x));
			write_seq(tail(x));
		}
	}

	lisp copy_lisp(const lisp x) {
		if (isNull(x)) return NULL;
		else if (isAtom(x)) return make_atom(x->node.atom);
		else return cons(copy_lisp(head(x)), copy_lisp(tail(x)));
	}
}
