#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "queue.hpp"
using namespace std;

int main(int argc, char* argv[]) {
		int a, b;

		cout << "Ввод имени файла, в котором первые два числа соответсвуют a и b: " << endl;
		cout << argv[1] << endl;
		ifstream fin(argv[1]);
		if (!fin) {
			cout << "File not open for reading!\n";
			return 0;
		 }

		fin >> a;
		fin >> b;

		int begin_size = 5;
		Queue<int> less(begin_size);
		Queue<int> between(begin_size);
		Queue<int> bigger(begin_size);

		int value;
		while (fin >> value) {
			if (value < a) {
				less.push(value);
			}

			if (value >= a && value <= b) {
				between.push(value);
			}

			if (value > b) {
				bigger.push(value);
			}
		}

		fin.close();

		cout << "a = " << a << "  b = " << b << endl;

		cout << "-------- Numbers --------" << endl;

		while (!less.isEmpty()) {
			cout << less.pop() << " ";
		}

		while (!between.isEmpty()) {
			cout << between.pop() << " ";
		}

		while (!bigger.isEmpty()) {
			cout << bigger.pop() << " ";
		}

		cout << endl;
		cout << "-------------------------" << endl;
}
