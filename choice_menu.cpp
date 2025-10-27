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
	cout << "������� ������ �������: ";
	length = Get_Int();
	length = Not_Negative(length);
	return length;
}
// ������� ��� ���������� ������ ��������������
void Self_Input(int length, vector<int>& values) {
	values.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������� � ����������� ����� ���� �������������� ��������
	for (int i = 0; i < length; i++) {
		int number = 0;
		cout << "������� ����� " << i + 1 << ": ";
		number = Get_Int();
		values.push_back(number);
	}
}

// ������� ��� ���������� ������ ���������� �������
void Random_Input(int length, vector<int>& values) {
	srand(time(0));
	for (int i = 0; i < length; i++) {
		values.push_back(rand() * (rand()%2 ? 1: -1));
	}
}

// ������� ��� ���������� ������ ���������� ������� � ���������
void Random_Range_Input(int length, vector<int>& values) {
	int begin = 0, end = 0;
	bool suitable = false;
	while (true) {
		cout << "������� ������ ���������: ";
		begin = Get_Int();
		cout << "������� ����� ���������: ";
		end = Get_Int();
		if (end > begin) {
			suitable = true;
			break;
		} cout << "������: ����� ��������� ������ ���� ������ ������" << endl;
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
		cout << "�������� ������ ��������� �������:" << endl <<
			"�������������� - 1" << endl <<
			"���������� ������� - 2" << endl <<
			"���������� ������� � ��������� - 3" << endl <<
			"�� ����� - 4" << endl;
		cout << "�������� ����� ����: ";
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
			// ������ ������� ������ ������ �� �����
			Show_Values(original_array);
			Radix_Sort(original_array, sorted_array);
			Show_Values(sorted_array);
			original_array.clear();
			return;
			break;
		default: // 6(-�-)9
			cout << "����������� ����. ����� ����������� � ����." << endl;
			break;
		}
	} while (true);

}
