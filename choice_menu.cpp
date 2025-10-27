# include <iostream>
# include <vector>
# include <random>
# include "check.h"
# include "files.h"
# include "sort.h"
using namespace std;


void Show_Values(vector<int>& values) {
	for (int number : values) {
		cout << number << " ";
	} cout << endl;
}
int Length_Array() {
	int length = 0;
	cout << "Введите размер массива: ";
	length = Get_Int();
	length = Not_Negative(length);
	return length;
}
// Функция для заполнения данных самостоятельно
void Self_Input(int length, vector<int>& values) {
	values.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка с предыдущего ввода всех дополнительных символов
	for (int i = 0; i < length; i++) {
		int number = 0;
		cout << "Введите число " << i + 1 << ": ";
		number = Get_Int();
		values.push_back(number);
	}
}

// Функция для заполнения данных рандомными числами
void Random_Input(int length, vector<int>& values) {
	srand(time(0));
	for (int i = 0; i < length; i++) {
		values.push_back(rand() * (rand()%2 ? 1: -1));
	}
}

// Функция для заполнения данных рандомными числами в диапазоне
void Random_Range_Input(int length, vector<int>& values) {
	int begin = 0, end = 0;
	bool suitable = false;
	while (true) {
		cout << "Введите начало диапазона: ";
		begin = Get_Int();
		cout << "Введите конец диапазона: ";
		end = Get_Int();
		if (end > begin) {
			suitable = true;
			break;
		} cout << "Ошибка: конец диапазона должен быть больше начала" << endl;
	}
	for (int i = 0; i < length; i++) {
		values.push_back(rand() % (end - begin + 1) + begin);
	}

}

enum Input_Menu { Self = 1, Random = 2, Random_Range = 3, File};

void Implement_Sort() {
	int input_choice = 0;
	int array_length = 0;
	vector<int> original_array;
	vector<int> sorted_array;
	do {
		cout << "Выберите способ заполения массива:" << endl <<
			"Самостоятельно - 1" << endl <<
			"Рандомными числами - 2" << endl <<
			"Рандомными числами в диапазоне - 3" << endl <<
			"Из файла - 4" << endl;
		cout << "Выберите пункт меню: ";
		input_choice = Get_Int();
		switch (input_choice) {
		case Self:
			array_length = Length_Array();
			Self_Input(array_length, original_array);
			Show_Values(original_array);
			Radix_Sort(original_array, sorted_array);
			Show_Values(sorted_array);
			original_array.clear();
			return;
			break;
		case Random:
			array_length = Length_Array();
			Random_Input(array_length, original_array);
			Show_Values(original_array);
			Radix_Sort(original_array, sorted_array);
			Show_Values(sorted_array);
			original_array.clear();
			return;
			break;
		case Random_Range:
			array_length = Length_Array();
			Random_Range_Input(array_length, original_array);
			Show_Values(original_array);
			Radix_Sort(original_array, sorted_array);
			Show_Values(sorted_array);
			original_array.clear();
			return;
			break;
		case File:
			// Пупупу функция вывода данных из файла
			Show_Values(original_array);
			Radix_Sort(original_array, sorted_array);
			Show_Values(sorted_array);
			original_array.clear();
			return;
			break;
		default: // 6(-О-)9
			cout << "Некоректный ввод. Пункт отсутствует в меню." << endl;
			break;
		}
	} while (true);

}
