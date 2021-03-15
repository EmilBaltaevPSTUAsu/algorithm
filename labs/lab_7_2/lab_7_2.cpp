
#include <iostream>
using namespace std;

int min(int k, ...) {
	int* p = &k;	// встаем на начало
	p++;			// встаем на первый элемент списка
	int min = 99999;
	for (; k > 0; k--) {	// идем до конца
		if(min > *p)		// если меньше текущего
			min = *p;
		p++;				// двигаемся на следующий
	}
	return min;
}

void show(int val) {
	if (val == 99999)
		cout << "Нет элементов\n";
	else
		cout << val << endl;
}

int main()
{
	system("chcp 1251");
	cout << "Список из 5 - 8 4 2 36 9: ";
	int val = min(5, 8, 4, 2, 36, 9);
	show(val);
	cout << "Список из 10 - 10 21 17 33 3 34 22 40 3 36: ";
	val = min(10, 10, 21, 17, 33, 3, 34, 22, 40, 3, 36);
	show(val);
	cout << "Список из 12 - 19 34 42 38 7 29 28 17 49 25 0 18: ";
	val = min(12, 19, 34, 42, 38, 7, 29, 28, 17, 49, 25, 0, 18);
	show(val);
}
