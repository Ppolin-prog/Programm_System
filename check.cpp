# include <iostream>
# include <vector>
# include <algorithm>
# include <fstream>
# include <locale>
# include <string>

using namespace std;

int Get_Int() {
	int number = 0;
	while (!(cin >> number)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // игнорирует максимальное количество символов при вводе
		cerr << "Ошибка ввода. Введите целое число: "; // 6(-О-)9
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return number;
}

int Not_Negative(int number) {
	while (number < 0) {
		cerr << "Введенное значение меньше нуля. Введите новое число: "; // 6(-О-)9
		cin >> number;
	}
	return number;
}

bool File_Exist(string path) {
	ifstream file(path);
	return file.good();
}

// Проверка на запрещенные имена файла
bool Error_Name(string path) {
	const string forbidden_path[] = { "CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6",
			 "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };
	string filename = path.substr(path.find_last_of("/\\") + 1);
	size_t dot_pos = filename.find_last_of('.');

	if (dot_pos != string::npos) { filename = filename.substr(0, dot_pos); }
	if (dot_pos != string::npos) { filename = filename.substr(0, dot_pos); }

	locale loc;
	transform(filename.begin(), filename.end(), filename.begin(),
		[&loc](unsigned char c) { return static_cast<unsigned char>(toupper(c, loc)); });

	for (const auto& forbidden : forbidden_path) {
		if (filename == forbidden) { return true; }
	}
	return false;
}


// 6(-О-)9