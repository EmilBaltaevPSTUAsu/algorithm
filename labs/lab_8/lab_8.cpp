#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

// fread - не поддерживает string
struct student {
	char fName[50];
	char sName[50];
	char tName[50];
	char adress[255];
	char group[50];
	double rating;
};

student makeStudent() {
	student st;
	cout << "Введите фамилия? "; cin >> st.fName;
	cout << "Введите имя? "; cin >> st.sName;
	cout << "Введите отчество? "; cin >> st.tName;
	cout << "Введите адрес? "; cin >> st.adress;
	cout << "Введите группа? "; cin >> st.group;
	cout << "Введите рейтинг? "; cin >> st.rating;
	cout << endl;
	return st;
}

void showStudent(student& st) {
	cout << "ФИО: " <<  st.fName << " " << st.sName << " " << st.tName << endl;
	cout << "Адрес проживания: " << st.adress << endl;
	cout << "Группа: " << st.group << " с рейтингом: " << st.rating << endl;
	cout << endl;
}

char path[] = "file.dat";
FILE *fp, *fpTemp;

int make_file() {
	int n;
	cout << "Количество записей? "; cin >> n;
	fp = fopen(path, "wb");
	if (fp == 0)
		return 1;
	for (int i = 0; i < n; i++) {
		student st = makeStudent();		// создаем
		fwrite(&st, sizeof(student), 1, fp); // записываем
	}
	fclose(fp);
	return 0;
}

int read_file() {
	fp = fopen(path, "rb");
	if (fp == 0)
		return 1;
	student st;
	do {
		fread(&st, sizeof(student), 1, fp);	// читаем
		if (feof(fp))
			break;
		showStudent(st);	// выводим
	} while (true);
	fclose(fp);
	return 0;
}

int insert_into_file() {
	fp = fopen(path, "ab");		// режим: добавление
	if (fp == 0)
		return 1;
	student st = makeStudent();
	fwrite(&st, sizeof(student), 1, fp); // записываем
	fclose(fp);
	return 0;
}

int delete_from_file() {
	double val;
	cout << "Заданный рейтинг? "; cin >> val;
	fp = fopen(path, "rb");
	if (fp == 0)
		return 1;
	fpTemp = fopen("temp.dat", "wb");	// доп. файл
	if (fpTemp == 0)
		return 1;
	student st;
	bool ok = false;	// флаг, удалили ли что-нибудь
	do {
		fread(&st, sizeof(student), 1, fp);
		if (feof(fp))
			break;
		if(st.rating >= val)	// если не менее заданного, переписываем
			fwrite(&st, sizeof(student), 1, fpTemp);
		else
			ok = true;
	} while (true);
	fclose(fp);
	fclose(fpTemp);
	remove(path);				// удаляем старый
	rename("temp.dat", path);	// переименовываем новый
	if (ok == true)
		return 0;
	else
		return 3;
}

int main()
{
	system("chcp 1251");
	int x, res;
	string menu = "\n";
	menu += "1. Создать файл с записями\n";
	menu += "2. Прочитать файл\n";
	menu += "3. Добавить запись в конец\n";
	menu += "4. Удаление записей с меньшим рейтингом\n";
	menu += "9. Показать меню\n";
	menu += "0. Выход\n";
	cout << menu;
	do {
		cout << "\n#>";
		cin >> x;
		switch (x) {
		case 1: res = make_file(); break;
		case 2: res = read_file(); break;
		case 3: res = insert_into_file(); break;
		case 4: res = delete_from_file(); break;
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
