# include <iostream>
# include <string>
# include <vector>
# include <random>
# include "check.h"
# include "files.h"
# include "sort.h"
using namespace std;

void Show_Values(vector<int>& values) {
	for (int number : values) { cout << number << " "; } 
	cout << endl;
}
int Get_Length_Array() { 
	int length = 0;
	cout << "Введите размер массива: ";
	length = Get_Int();
	length = Not_Negative(length);
	return length;
}
// Функция для заполнения данных самостоятельно
void Self_Input(vector<int>& values) {
	values.clear();
	int length = Get_Length_Array();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка с предыдущего ввода всех дополнительных символов
	for (int i = 0; i < length; i++) {
		int number = 0;
		cout << "Введите число " << i + 1 << ": ";
		number = Get_Int();
		values.push_back(number);
	}
}

// Функция для заполнения данных рандомными числами
void Random_Input(vector<int>& values) {
	values.clear();
	int length = Get_Length_Array();
	for (int i = 0; i < length; i++) { values.push_back(rand() * (rand() % 2 ? 1: -1)); }
}

// Функция для заполнения данных рандомными числами в диапазоне 
void Random_Range_Input(vector<int>& values) {
	values.clear();
	int length = Get_Length_Array();
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
	for (int i = 0; i < length; i++) { values.push_back(rand() % (end - begin + 1) + begin); }
}

enum Files_Menu { Save = 1, Not_Save };
void Choice_Save_Into_File(vector<int>& sorted_array) {
	int option = 0;
	bool save_full = false;
	cout << "Вы хотите сохранить данные в файл?" << endl;
	do {
		cout << "Сохранить в файл - 1" << endl
			<< "Не сохранять файл - 2" << endl;
		cout << "Введите число: ";
		option = Get_Int();
		switch (option) {
		case Save:
			save_full = true;
			Transfer_To_File(sorted_array);
			return;
		case Not_Save:
			return;
		default:
			cout << "Некоректный ввод. Пункт отсутствует в меню." << endl;
			return;
		}
	} while (true);
}

void Work_With_Data(vector<int>& original_array, vector<int>& sorted_array){
	Show_Values(original_array);
	Radix_Sort(original_array, sorted_array);
	Show_Values(sorted_array);
	if (!sorted_array.empty()) { Choice_Save_Into_File(sorted_array); }
}

void Primary_Part(void (*Choice_Function)(vector<int>& values), vector<int>& original_array, vector<int>& sorted_array) {
	Choice_Function(original_array);
	Work_With_Data(original_array, sorted_array);
}

enum Input_Menu { Self = 1, Random, Random_Range, File};
void Implement_Sort() {
	vector<int> original_array;
	vector<int> sorted_array;
	int input_choice = 0;
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
			Primary_Part(Self_Input, original_array, sorted_array);
			return;
		case Random:
			Primary_Part(Random_Input, original_array, sorted_array);
			return;
		case Random_Range:
			Primary_Part(Random_Range_Input, original_array, sorted_array);
			return;
		case File:
			Data_From_File(original_array);
			Work_With_Data(original_array, sorted_array);
			return;
		default: // 6(-О-)9
			cout << "Некоректный ввод. Пункт отсутствует в меню." << endl;
			break;
		}
	} while (true);

}
