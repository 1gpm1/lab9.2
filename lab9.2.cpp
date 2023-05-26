#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

enum Specialnist { KOMPUTERNI_NAUKY, INFORMATYKA, EKONOMIKA, FIZYKA };

string specialnistStr[] = { "КН", "ІН", "МЕ", "ФІ" };

struct Student
{
	string prizv;
	unsigned kurs;
	Specialnist specialnist;
	unsigned programming;
	unsigned matematika;
	union
	{
		unsigned fizyka;
		unsigned chiselni_metody;
		unsigned pedagogika;
	};
};


void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Specialnist specialnist, const unsigned kurs);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];

	int ispecialnist;
	Specialnist specialnist;
	unsigned kurs;
	string prizv;
	int found;


	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних" << endl;
		cout << " [5] - бінарний пошук студента за прізвищем на вказаному курсі та спеціальності" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "курс: ";
			cin >> kurs;
			cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Економіка, 3 - Фізика): ";
			cin >> ispecialnist;
			specialnist = (Specialnist)ispecialnist;

			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, specialnist, kurs)) != -1)
				cout << "Знайдено студента в позиції: " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(Student* p, const int N)
{
	int specialnist;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;

		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Економіка, 3 - Фізика): ";
		cin >> specialnist;
		p[i].specialnist = (Specialnist)specialnist;
		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			cout << "програмування : "; cin >> p[i].programming;
			cout << "математика : "; cin >> p[i].matematika;
			cout << "фізика : "; cin >> p[i].fizyka;
			break;
		case INFORMATYKA:
			cout << "програмування : "; cin >> p[i].programming;
			cout << "математика : "; cin >> p[i].matematika;
			cout << "педагогіка : "; cin >> p[i].pedagogika;
			break;
		case EKONOMIKA:
		case FIZYKA:
			cout << "програмування : "; cin >> p[i].programming;
			cout << "математика : "; cin >> p[i].matematika;
			cout << "фізика : "; cin >> p[i].fizyka;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "======================================================================================================================"
		<< endl;
	cout << "|  №  |   Прізвище   | Курс |   Спеціальність   | Програмування | Математика | Фізика | Чисельні методи | Педагогіка | "
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(12) << right << p[i].prizv << " "
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(17) << right << specialnistStr[p[i].specialnist];

		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			cout << " |" << setw(14) << right
				<< p[i].programming << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(6) << right
				<< p[i].fizyka << " |" << right << setw(18) << right << "|" << setw(13) << right << "|" << endl;
			break;
		case INFORMATYKA:
			cout << " |" << setw(14) << right
				<< p[i].programming << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(8) << right << "|" << setw(18) << right << "|" << setw(11) << right
				<< p[i].pedagogika << " |" << right << endl;
			break;
		case EKONOMIKA:
		case FIZYKA:
			cout << " |" << setw(14) << right
				<< p[i].programming << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(6) << right
				<< p[i].fizyka << " |" << right << setw(18) << right << "|" << setw(13) << right << "|" << endl;
			break;
		}
	}
	cout << "======================================================================================================================"
		<< endl;
	cout << endl;
}


void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].specialnist > p[i1 + 1].specialnist)
				||
				(p[i1].specialnist == p[i1 + 1].specialnist &&
					p[i1].prizv < p[i1 + 1].prizv)
				||
				(p[i1].specialnist == p[i1 + 1].specialnist &&
					p[i1].prizv == p[i1 + 1].prizv &&
					p[i1].kurs > p[i1 + 1].kurs))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив

	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними

	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].specialnist > p[value].specialnist) ||
				(p[I[j]].specialnist == p[value].specialnist &&
					p[I[j]].prizv > p[value].prizv) ||
				(p[I[j]].specialnist == p[value].specialnist &&
					p[I[j]].prizv == p[value].prizv &&
					p[I[j]].kurs > p[value].kurs));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
  // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "======================================================================================================================"
		<< endl;
	cout << "|  №  |   Прізвище   | Курс |   Спеціальність   | Програмування | Математика | Фізика | Чисельні методи | Педагогіка | "
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(12) << right << p[i].prizv << " "
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(17) << right << specialnistStr[p[i].specialnist];

		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			cout << " |" << setw(14) << right
				<< p[i].programming << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(6) << right
				<< p[i].fizyka << " |" << right << setw(18) << right << "|" << setw(13) << right << "|" << endl;
			break;
		case INFORMATYKA:
			cout << " |" << setw(14) << right
				<< p[i].programming << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(8) << right << "|" << setw(18) << right << "|" << setw(11) << right
				<< p[i].pedagogika << " |" << right << endl;
			break;
		case EKONOMIKA:
		case FIZYKA:
			cout << " |" << setw(14) << right
				<< p[i].programming << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(6) << right
				<< p[i].fizyka << " |" << right << setw(18) << right << "|" << setw(13) << right << "|" << endl;
			break;
		}
	}
	cout << "======================================================================================================================"
		<< endl;
	cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const Specialnist specialnist, const unsigned kurs)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].kurs && p[m].specialnist == specialnist)
			return m;
		if ((p[m].specialnist < specialnist)
			||
			(p[m].specialnist == specialnist &&
				p[m].prizv < prizv &&
				p[m].kurs < kurs))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
