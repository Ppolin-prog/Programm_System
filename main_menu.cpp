# include <iostream>
# include "check.h"
# include "choice_menu.h"
using namespace std;

enum Menu { Start = 1, End};

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Поразрядная сортировка, версия MSJ" << endl;
	int choice = 0;
	do {
		cout << "Пункты меню: " << endl << "Начать работу - 1" << endl << "Выйти - 2" << endl;
		cout << "Выберите пункт меню: ";
		choice = Get_Int();
		switch (choice) {
		case Start: 
			cout << "Начало работы программы" << endl;
			Implement_Sort();
			break;
		case End: 
			cout << "Окончание работы программы" << endl;
			break;
		default: // 6(-О-)9
			cout << "Некоректный ввод. Пункт отсутствует в меню." << endl;
			break;
		}
	} while (choice != End);
	return 0;
}