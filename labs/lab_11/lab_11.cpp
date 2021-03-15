#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct point {
	int data;
	point* next;
	point* prev;
};

point* make_point(int data) {
	point* p = new point;
	p->data = data;
	p->next = p->next = 0;
	return p;
}

point* make_list() {
	int n;
	cout << "Количество? "; cin >> n;
	if (n == 0)
		return 0;
	point* beg = make_point(rand() % 100 - 50);
	point* curr = beg;
	for (int i = 1; i < n; i++) {
		point* p = make_point(rand() % 100 - 50);
		curr->next = p;
		p->prev = curr;
		curr = curr->next;
	}
	return beg;
}

void print_list(point* beg, string text = "Список: ") {
	if (beg == 0)
		cout << "Пустой список";
	else
		cout << text;
	point* curr = beg;
	while (curr != 0) {
		cout << curr->data << "  ";
		curr = curr->next;
	}
	cout << endl;
}

point* insert_back(point* beg) {
	int val;
	cout << "Значение? "; cin >> val;
	point* p = make_point(val);
	if (beg == 0)
		return p;
	point* curr = beg;
	while (curr->next != 0)
		curr = curr->next;
	curr->next = p;
	p->prev = curr;
	return beg;
}

point* delete_first(point* beg) {
	if (beg == 0)
		return 0;
	if (beg->next == 0)
		return 0;
	point* curr = beg;
	beg = beg->next;
	beg->prev = 0;
	delete curr;
	return beg;
}

point* clear_list(point* beg) {
	while (beg != 0) {
		point* curr = beg;
		beg = beg->next;
		delete curr;
	}
	cout << "Успешное очищение списка" << endl;
	return 0;
}

FILE* fp;

int list_to_file(point* beg) {
	if ((fp = fopen("list.dat", "wb")) == 0)
		return 1;
	point* curr = beg;
	while (curr != 0) {
		fwrite(&curr->data, sizeof(int), 1, fp);
		curr = curr->next;
	}
	fclose(fp);
	cout << "Успешная запись в файл" << endl;
	return 0;
}

point* list_from_file() {
	if ((fp = fopen("list.dat", "rb")) == 0)
		return 0;
	int temp;
	point* beg = 0;
	point* curr = 0;
	do {
		fread(&temp, sizeof(int), 1, fp);	// читаем
		if (feof(fp))
			break;
		if (curr == 0) {
			curr = make_point(temp);
			beg = curr;
		}
		else {
			point* p = make_point(temp);
			curr->next = p;
			p->prev = curr;
			curr = curr->next;
		}
	} while (true);
	fclose(fp);
	cout << "Успешное чтение из файла" << endl;
	return beg;
}

int main()
{
	system("chcp 1251");
	srand((unsigned)time(0));
	point* beg = make_list();
	print_list(beg, "Исходный список: ");
	beg = insert_back(beg);
	print_list(beg, "После добавления в конец: ");
	beg = delete_first(beg);
	print_list(beg, "После удаления первого: ");
	int res = list_to_file(beg);
	beg = clear_list(beg);
	print_list(beg, "Запись в файл и уничтожение: ");
	beg = list_from_file();
	print_list(beg, "Восстановление из файла: ");
	beg = clear_list(beg);
	print_list(beg, "Уничтожение списка: ");
}

