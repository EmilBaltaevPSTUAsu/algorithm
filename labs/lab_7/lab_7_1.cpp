
#include <iostream>
using namespace std;

struct complex {
	double x;
	double y;
};

double Divide(int a, int b) {
	double res = (double)a / (double)b;
	return res;
}

complex Divide(complex a, complex b) {
	complex temp;
	temp.x = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
	temp.y = (b.x * a.y - a.x * b.y) / (b.x * b.x + b.y * b.y);
	return temp;
}

int main()
{
	system("chcp 1251");
	int a, b;
	cout << "Использование целочисленного деления\n";
	cout << "a? "; cin >> a;
	cout << "b? "; cin >> b;
	cout << "Результат: " << Divide(a, b) << endl;
	cout << endl;
	cout << "Использование комплексного деления\n";
	complex c, d;
	cout << "c.x? "; cin >> c.x;
	cout << "c.y? "; cin >> c.y;
	cout << "d.x? "; cin >> d.x;
	cout << "d.y? "; cin >> d.y;
	complex  res = Divide(c, d);
	cout << "Результат: (" << res.x << ", " << res.y << ")\n";
}
