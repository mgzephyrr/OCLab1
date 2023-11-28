#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	unsigned int n;
	double x, e;

	cout << "Введите x: ";
	cin >> x;
	cout << "\nВведите n: ";
	cin >> n;
	cout << "\nВведите epsilon: ";
	cin >> e;
	cout << endl;

	double funcAns = atan(x);

	printf("Значение, посчитанное с помощью функции atan: %.64f\n\n", funcAns); // значение, с которым будем сравнивать получаемые результаты

	float floatNumerator = x, floatNAns = 0, floatEpsAns = 0, floatMaxAns = 0; // переменные числителя и трех сумм типа float
	double doubleNumerator = x, doubleNAns = 0, doubleEpsAns = 0, doubleMaxAns = 0; // переменные числителя и трех сумм типа double
	unsigned long long denominator = 1; // знаменатель (общий для обеих сумм)

	for (int i = 0; i < n; i++) {
		floatNAns += floatNumerator / denominator; // увеличиваем float сумму
		doubleNAns += doubleNumerator / denominator; // увеличиваем double сумму
		floatNumerator *= -x * x; doubleNumerator *= -x * x; // рассчитываем числители следующих элементов
		denominator += 2; // рассчитываем знаменатель
	}

	printf("Значение, посчитанное с помощью %d первых элементов ряда (float): %.64f\n",n , floatNAns);
	printf("Значение, посчитанное с помощью %d первых элементов ряда (double): %.64f\n\n", n, doubleNAns);

	floatNumerator = x; doubleNumerator = x; // возвращаю значения на начальные
	denominator = 1; // возвращаю значения на начальные
	unsigned long long floatIterations = 0, doubleIterations = 0; // переменные для подсчета кол-ва итераций

	while (abs(floatNumerator / denominator) > e) {
		floatEpsAns += floatNumerator / denominator; // увеличиваем float сумму
		floatNumerator *= -x * x; // рассчитываем числитель след. элемента
		denominator += 2; floatIterations++; // рассчитываем знаменатель след. элемента и увеличиваем кол-во итераций
	}

	denominator = 1; // возвращаю значение на стартовое

	while (abs(doubleNumerator / denominator) > e) {
		doubleEpsAns += doubleNumerator / denominator; // увеличиваем double сумму
		doubleNumerator *= -x * x; // рассчитываем числитель след.элемента
		denominator += 2; doubleIterations++; // рассчитываем знаменатель след. элемента и увеличиваем кол-во итераций
	}

	printf("Значение, посчитанное до точности epsilon = %f (кол-во итераций = %lld) (float): %.64f\n", e, floatIterations, floatEpsAns);
	printf("Значение, посчитанное до точности epsilon = %f (кол-во итераций = %lld) (double): %.64f\n\n", e, doubleIterations, doubleEpsAns);

	floatNumerator = x; doubleNumerator = x; // возвращаем значения
	denominator = 1; // возвращаем значения
	floatIterations = 0, doubleIterations = 0; // возвращаем значения

	while (abs(floatNumerator / denominator) > 0) {
		floatMaxAns += floatNumerator / denominator; // увеличиваем float сумму
		floatNumerator *= -x * x; // рассчитываем числитель след. элемента
		denominator += 2; floatIterations++; // рассчитываем знаменатель след. элемента и увеличиваем кол-во итераций
	}

	denominator = 1; // возвращаю значение на стартовое

	while (abs(doubleNumerator / denominator) > 0) {
		doubleMaxAns += doubleNumerator / denominator; // увеличиваем double сумму
		doubleNumerator *= -x * x; // рассчитываем числитель след.элемента
		denominator += 2; doubleIterations++; // рассчитываем знаменатель след.элемента и увеличиваем кол - во итераций
	}

	printf("Значение, посчитанное до максимальной точности (кол-во итераций = %lld) (float): %.64f\n", floatIterations, floatMaxAns);
	printf("Значение, посчитанное до максимальной точности (кол-во итераций = %lld) (double): %.64f\n\n", doubleIterations, doubleMaxAns);
}