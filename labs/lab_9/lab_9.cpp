#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

FILE *f1, *f2;
const int MAX = 255;
char buf[MAX];

int make_file(const char* path) {
	int n;
	cout << "Количество строк? "; cin >> n;
	if((f1 = fopen(path, "wt")) == 0)	// открываем
		return 1;
	cin.ignore();
	for (int i = 0; i < n; i++) {		
		fgets(buf, MAX, stdin);		// вводим 
		fputs(buf, f1);				// записываем
	}
	fclose(f1);
	return 0;
}

int read_file(const char* path) {
	if ((f1 = fopen(path, "rt")) == 0)
		return 1;
	while (fgets(buf, MAX, f1) != 0)	// пока не конец файла
		cout << buf;		// выводим
	cout << endl;
	fclose(f1);
	return 0;
}

int copy_file(const char* dest, const char* source) {
	if ((f1 = fopen(dest, "rt")) == 0)
		return 1;
	if ((f2 = fopen(source, "wt")) == 0)
		return 1;
	bool ok = false;		// флаг, что нашли строки, начинающиеся с 'A'
	while (fgets(buf, MAX, f1) != 0)	// пока не конец
		if (buf[0] != 'A')		// если не выполняется условие
			fputs(buf, f2);		// копируем
		else
			ok = true;
	fclose(f1);
	fclose(f2);
	if (ok == true)
		return 0;
	else
		return 3;
}

int first_word_length_file(const char* path) {
	if ((f1 = fopen(path, "rt")) == 0)
		return 1;
	if (fgets(buf, MAX, f1) != 0) {	// пока не конец
		int count = 0, i = 0;
		while (i < strlen(buf) && buf[i] == ' ')	// пропускаем начальные пробелы	
			i++;
		if (i == strlen(buf)) {		// если конец строки
			cout << "Нет слов в строке" << endl;
		}
		else {
			while (i < strlen(buf) && buf[i] != ' ') {	// считаем до конца слова
				count++;
				i++;
			}
			cout << "Размер первого слова: " << count << endl;
		}
	}
	fclose(f1);
	return 0;
}



int main()
{
	system("chcp 1251");
	int x, res;
	string menu = "\n";
	menu += "1. Создать файл F1\n";
	menu += "2. Прочитать F1\n";
	menu += "3. Прочитать F2\n";
	menu += "4. Скопировать строки, которые не начинаются на 'A'\n";
	menu += "5. Подсчитать количество символов в первом слове F2\n";
	menu += "9. Показать меню\n";
	menu += "0. Выход\n";
	cout << menu;
	do {
		cout << "\n#>";
		cin >> x;
		switch (x) {
		case 1: res = make_file("F1.txt"); break;
		case 2: res = read_file("F1.txt"); break;
		case 3: res = read_file("F2.txt"); break;
		case 4: res = copy_file("F1.txt", "F2.txt"); break;
		case 5: res = first_word_length_file("F2.txt"); break;
		case 9: cout << menu; break;
		case 0: return 0;
		}
		switch (res) {
		case 0: cout << "Операция успешна" << endl; break;
		case 1: cout << "Ошибка открытия" << endl; break;
		case 2: cout << "Ошибка записи/чтения" << endl; break;
		case 3: cout << "Операция без изменений" << endl; break;
		}
	} while (true);
}
