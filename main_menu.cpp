# include <iostream>
# include "check.h"
# include "choice_menu.h"
using namespace std;

enum Menu { Start = 1, End = 2 };

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "����������� ����������, ������ MSJ" << endl;
	int choice = 0;
	do {
		cout << "������ ����: " << endl << "������ ������ - 1" << endl << "����� - 2" << endl;
		cout << "�������� ����� ����: ";
		choice = Get_Int();
		switch (choice) {
		case Start: 
			cout << "������ ������ ���������" << endl;
			Implement_Sort();
			break;
		choice = 2;
		case End: 
			cout << "��������� ������ ���������" << endl;
			break;
		default: // 6(-�-)9
			cout << "����������� ����. ����� ����������� � ����." << endl;
			break;
		}
	} while (choice != End);
	return 0;
}