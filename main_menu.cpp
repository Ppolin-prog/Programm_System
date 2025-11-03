# include <iostream>
# include "check.h"
# include "choice_menu.h"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
using namespace std;

enum Menu { Start = 1, End};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Поразрядная сортировка, версия MSD" << endl;
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
			return 0;
		default: // 6(-О-)9
			cout << "Некоректный ввод. Пункт отсутствует в меню." << endl;
			break;
		}
	} while (true);
	return 0;
}