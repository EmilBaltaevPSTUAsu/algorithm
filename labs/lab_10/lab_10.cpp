
#include <iostream>
using namespace std;

int** form_mas(int& rows, int& cols) {
	cout << "Строк? "; cin >> rows;
	cout << "Столбцов? "; cin >> cols;
	int** mas = new int* [rows];			// память под строки
	for (int i = 0; i < rows; i++) {
		mas[i] = new int[cols];				// память под столбцы
		for (int j = 0; j < cols; j++)
			mas[i][j] = rand() % 100 - 50;	// случайное присвоение
	}
	return mas;
}

void print_mas(int** mas, int rows, int cols, string text = "Массив: ") {
	cout << text << endl;
	for (int i = 0; i < rows; i++) {	// по строкам
		for (int j = 0; j < cols; j++)	// по столбцам
			cout << mas[i][j] << "  ";
		cout << endl;
	}
}

int** delete_mas(int** mas, int rows) {
	for (int i = 0; i < rows; i++)	// очищаем строки
		delete[] mas[i];
	delete[] mas;		// очищаем весь массив
	return 0;
}

int** delete_col_by_num(int** mas, int rows, int& cols) {
	int K;
	cout << "Номер столбца для удаления? "; cin >> K;
	if (K < 1 || K > cols) {
		cout << "Неверный номер" << endl;	// вводим и проверяем
		return mas;
	}
	int** temp = new int* [rows];		// строк аналогично
	for (int i = 0; i < rows; i++) {
		temp[i] = new int[cols - 1];	// столбцов меньше на 1
		for(int j=0, k=0; j<cols; j++)
			if (j != (K - 1)) {			// если не введенный номер
				temp[i][k] = mas[i][j];	// копируем
				k++;
			}
	}
	mas = delete_mas(mas, rows);
	cols--;
	return temp;
}

int main()
{
	system("chcp 1251");
	srand((unsigned)time(0));
	int rows, cols;
	int** mas = form_mas(rows, cols);
	print_mas(mas, rows, cols);
	mas = delete_col_by_num(mas, rows, cols);
	print_mas(mas, rows, cols, "После удаления столбца");
	mas = delete_mas(mas, rows);
}
