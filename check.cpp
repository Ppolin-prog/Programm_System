# include <iostream>
# include <vector>
# include <algorithm>
# include <fstream>
using namespace std;

int Get_Int() {
	int number = 0;
	while (!(cin >> number)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������������ ���������� �������� ��� �����
		cerr << "������ �����. ������� ����� �����: "; // 6(-�-)9
	}
	return number;
}

int Not_Negative(int number) {
	while (number < 0) {
		cerr << "��������� �������� ������ ����. ������� ����� �����: "; // 6(-�-)9
		cin >> number;
	}
	return number;
}

bool File_Exist(string path) {
	ifstream file(path);
	return file.good();
}

// �������� �� ����������� ����� �����
bool Error_Name(string path) {
	const string forbidden_path[] = { "CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6",
			 "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };
	string filename = path.substr(path.find_last_of("/\\") + 1);
	size_t dot_pos = filename.find_last_of('.');
	if (dot_pos != string::npos) {
		filename = filename.substr(0, dot_pos);
	}
	transform(filename.begin(), filename.end(), filename.begin(),
		[](unsigned char �) {return static_cast<unsigned char>(toupper(�)); });

	for (const auto forbidden : forbidden_path) {
		if (filename == forbidden) {
			return true;
		}
	}
	return false;
}


// 6(-�-)9