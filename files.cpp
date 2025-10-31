# include <iostream>
# include <fstream>
# include <string>
# include <cctype>
# include <vector>
# include <filesystem>
# include <algorithm>
# include "check.h"
using namespace std;

// Функции для заполнения данных из вектора в файл
void Save_In_File(vector<int>& array, string& path) {
	ofstream file;
	file.open(path);
	for (int i = 0; i < array.size(); i++) {
		file << array[i];
		file << " ";
	}
	file.close();
}

// Функции для заполнения данных из файла в вектор
void Data_From_File(vector<int>& receive_array) {
	receive_array.clear();
	string path = "";
	cout << "Введите путь копирования данных из файла: ";
	getline(cin, path);
	ifstream file(path);
	int number = 0;
	if (!file.is_open()) {
		cerr << "Ошибка при открытии файла";
		return;
	}
	while (file >> number) { receive_array.push_back(number); }
	if (receive_array.empty()) {
		cerr << "Файл пустой";
		file.close();
		return;
	}
	if (file.bad()) { cerr << "Ошибка: данные не числового типа" << endl; }

	file.close();
}

enum Menu_Save { Remove = 1, Leave};
void Transfer_To_File(vector<int>& sorted_array) {
	ofstream file;
	file.exceptions(ios::failbit);
	int option = 0;
	string way = "";
	bool file_modified = false;
	while (!file_modified) {
		cout << "Введите путь для сохранения файла: ";
		getline(cin, way);

		if (Error_Name(way)) {
			file_modified = false;
			cout << "Ошибка. Введенное имя файла запрещено" << endl;
			continue; 
		}
		if (File_Exist(way)) {
			cout << "Файл с таким именем уже существует. Хотите удалить информацию из файла?" << endl
				<< "Удалить информацию - 1" << endl
				<< "Оставить информацию - 2" << endl;
			cout << "Введите число: ";
			option = Get_Int();
			switch (option) {
			case Remove:
				try {
					file_modified = true;
					file.open(way, ofstream::trunc);
					cout << "Предыдущие данные удалены из файла" << endl;
					Save_In_File(sorted_array, way);
					cout << "Данные сохранены в файл" << endl;
					file.close();
				}
				catch (const std::exception&) {
					file_modified = false;
					cout << "Ошибка. Файл открыт только для чтения" << endl;
				}
				break;
			case Leave:
				break;
			default:
				cout << "Некоректный ввод. Пункт отсутствует в меню." << endl;
				break;
			}
		}
		else {
			try {
				ofstream first_file(way, ios::out);
				Save_In_File(sorted_array, way);
				cout << "Данные сохранены в файл" << endl;
				file_modified = true;
				first_file.close();
			}
			catch (const std::exception&) {
				file_modified = false;
				cout << "Ошибка. Неправильный путь к файлу" << endl;
			}
		}
	}
}