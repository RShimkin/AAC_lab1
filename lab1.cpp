// Шимкин Р.Р. 62 группа ПММ, 1 лабораторная работа (№19)
#include <iostream>
#include <math.h>

const int N = 3; // ранг матрицы

using namespace std;

// простая фукнция для проверки
float func1(float* v) {
	return 2 * (*v);
}

// простейшая функция для проверки
float func3(float* v) {
	return 1.0;
}

// функция из задания
auto func(float* v) -> float{
	const float A[][N] = {
		{1, 2, 3},
		{2, 4, 2},
		{3, 2, 1}
	};
	float V[] = { v[0], v[1] + 1, v[2] - 2 };                         // вектор v = { x, y+1, z-2 }
	float T[N];                                                       // промежуточный вектор
	for (int i = 0; i < N; i++)                                       // первое умножение
		T[i] = V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0];
	float res = T[0] * V[0] + T[1] * V[1] + T[2] * V[2];              // второе умножение
	return res;
}

template <typename D> void placement(int r, D &d) {        // функция принимает структуру с информацией и текущий шаг
	static float* x = new float[d.k];                      // статический массив размещения 
	// если массив собран полностью, считаем и добавляем результат к общей сумме
	if (r > d.k) d.res += exp(d.function(x) / -4);
	else {
		// иначе добавляем в массив значение r-ой переменной
		for (float i(1); i <= d.n[r - 1]; i++) {
			x[r - 1] = d.a[r - 1] + d.h * (i - 0.5);
			placement(r + 1, d);  // и рекурсивно считаем с новым состоянием массива
		}
	}
}

auto integral(int k, float h, float (*f)(float*)) {
	struct Data{
		int k;                             // кратность
		float h;                           // разбиение
		float (*function)(float*);         // указатель на функцию
		float* v;                          // 
		float* a;                          // массив нижних пределов
		float* b;                          // массив верхних индексов
		int* n;                            // массив индексов разбиение по каждой переменной
		float res = 0;                     // переменная результата
	} d;
	d.k = k;
	d.h = h;
	d.v = new float[k];
	d.a = new float[k];
	d.b = new float[k];
	int i(0);
	float s(1);                             // переменная для хранения результата умножения дифференциалов переменных
	for (; i < k; i++) {                    // цикл ввода пределов и вычисления s
		cout << "Enter limits for #" << i + 1 << " variable: ";
		cin >> d.a[i] >> d.b[i];
		s *= h;
	}
	d.n = new int[k];
	for (i = 0; i < k; i++)                  // цикл вычисления индексов разбиения
		d.n[i] = (d.b[i] - d.a[i]) / h;
	d.function = f;
	placement(1, d);
	d.res *= s;                              // домножаем результат на произведение дифференциалов переменных
	return d.res;
}

auto main() -> int
{
	int k;                                       // кратность интегрирования
	float h;                                     // разбиение
	cout << "Enter k and h: ";
	cin >> k >> h;
	cout << integral(k, h, func);
}
