# include <iostream>
# include <vector>
# include <cmath>
# include <algorithm>
using namespace std;

int Number_Length(int number) {
	int count = 0;
	if (number == 0)
		count = 1;
	number = abs(number);
	while (number > 0) {
		count++;
		number /= 10;
	} return count;
}
int Max_Length(vector<int>& original) {
	int array_length = original.size();
	int maximum_length = Number_Length(original[0]);
	for (size_t i = 1; i < array_length; i++) {
		int current_length = Number_Length(original[i]);
		if (maximum_length < current_length) {
			maximum_length = current_length;
		}
	} 
	return maximum_length;
}
// Функция для сортировки векторов (отрицательного и положительного)
void Sort_Funktion(vector<int>& array, int position = 0, int max_len =-1) {
	if (max_len == -1)
		max_len = Max_Length(array);
	int array_length = array.size();
	if ((array_length <= 1) || (position >= max_len))
		return;

	vector<vector<int>> hundreds(10);
	int power = max_len - 1 - position;
	if (power < 0) return;
	int divisor = (int)pow(10, power);
	for (int number : array) {
		if (divisor == 0) divisor = 1;
		int rang = (number / divisor) % 10;
		hundreds[rang].push_back(number);
	}
	
	int p = 0;
	for (int i = 0; i < 10; i++) {

		if (!hundreds[i].empty()) {
			if (position + 1 < max_len){ Sort_Funktion(hundreds[i], position + 1, max_len); }
			for (int number : hundreds[i]) {
				if (p < array.size())
					array[p++] = number;
				else
					cout << "Ошибка: выход за границы при записи в исходный массив" << endl;
			}
		}
	}
	
}

// Заполнение конечного вектора отсортированными значениями
void Radix_Sort(vector<int>& original, vector<int>& sorted) {
	int array_length = original.size();
	vector<int> negative;
	vector<int> positive;
	if (array_length == 0)
		return;
	for (size_t j = 0; j < array_length; j++) {
		if (original[j] == 0) {
			sorted.push_back(original[j]);
		}
		if (original[j] < 0)
			negative.push_back(abs(original[j]));
		else {
			positive.push_back(original[j]);;
		}
	}
	Sort_Funktion(positive);
	Sort_Funktion(negative);
	for (int begin = negative.size() - 1; begin >= 0; begin--) {
		sorted.push_back(-negative[begin]);
	}
	for (int end = 0; end < positive.size(); end++) {
		sorted.push_back(positive[end]);
	}
	// Проверка на дубликаты
	for (size_t j = 1; j < sorted.size(); ) {
		if (sorted[j - 1] == sorted[j])
			sorted.erase(sorted.begin() + j);
		else
			j++;
	}
}
