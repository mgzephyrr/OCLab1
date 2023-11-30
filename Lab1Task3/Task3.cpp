#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <windows.h> 
#include <excpt.h>

using namespace std;

double input_double(double lowest = -DBL_MAX, double highest = DBL_MAX) {
	string input;
	bool ok = true; // переменная, отвечающая за "правильность" введенного значения
	double number;

	do {
		cin >> input;
		cout << endl;
		try {
			if (input.find_first_not_of("0123456789") != input.find_last_not_of("0123456789") ||
				(input.find(",") == string::npos && input.find_first_not_of("0123456789") != string::npos))
				throw invalid_argument("");

			number = stod(input);

			if (number < lowest or number > highest)
				throw out_of_range("");

			ok = true;
		}
		catch (invalid_argument) {
			cout << "Вы ввели не число. Повторите, пожалуйста, ввод.\n";
			ok = false;
		}
		catch (out_of_range) {
			cout << "Вы ввели число, выходящее за указанные границы. Повторите, пожалуйста, ввод.\n";
			ok = false;
		}

	} while (!ok);

	return number;
}

int input_int(int lowest = INT_MIN, int highest = INT_MAX) {
	string input;
	bool check = true;
	int number;

	do {
		cin >> input;
		cout << endl;

		if (input.find_first_not_of("0123456789") != string::npos) {
			cout << "Вы ввели не число, отрицательное или дробное число, повторите, пожалуйста, ввод.\n";
			check = false;
		}
		else {
			try {
				number = stoi(input);
				if (number < lowest or number > highest)
					throw out_of_range("");

				else 
					check = true;
			}
			catch (out_of_range) {
				cout << "Вы ввели число, выходящее за указанные границы. Повторите, пожалуйста, ввод.\n";
				check = false;
			}
		}

	} while (!check);

	return number;
}

int main() {
	setlocale(LC_ALL, "Russian");
	_control87(_EM_INVALID, _EM_DENORMAL); // демаскирует исключения, связанные с операциями с плавающей запятой (денормализация и неверная операция)

	int n;
	double x, e;

	cout << "Введите x (дробное или целое число в пределах [0; 1]): ";
	x = input_double(0, 1);

	cout << "Введите n (целое число, в пределах от [1; 1 000 000]): ";
	n = input_int(1, 1000000);

	cout << "Введите epsilon (дробное или целое число в пределах (0; 1]): ";
	e = input_double(DBL_MIN, 1);

	cout << endl;

	double funcAns = atan(x);

	printf("Значение, посчитанное с помощью функции atan: %.64f\n\n", funcAns); // значение, с которым будем сравнивать получаемые результаты

	float floatNumerator = x, floatNAns = 0, floatEpsAns = 0, floatMaxAns = 0; // переменные числителя и трех сумм типа float
	double doubleNumerator = x, doubleNAns = 0, doubleEpsAns = 0, doubleMaxAns = 0; // переменные числителя и трех сумм типа double
	unsigned long long denominator = 1; // знаменатель (общий для обеих сумм)
	__try {
		for (int i = 0; i < n; i++) {
			floatNAns += floatNumerator / denominator; // увеличиваем float сумму
			doubleNAns += doubleNumerator / denominator; // увеличиваем double сумму
			floatNumerator *= -x * x; doubleNumerator *= -x * x; // рассчитываем числители следующих элементов
			denominator += 2; // рассчитываем знаменатель
		}
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		// EXCEPTION_EXECUTE_HANDLER — указывает на возможность данного обработчика обработать исключение.
		// При получении такого значения операционная система прекращает поиск релевантных обработчиков исключения и,
		// выполнив раскрутку стека, передаёт управление первому, вернувшему значение EXCEPTION_EXECUTE_HANDLER.		
		printf("Получилось денормализованное число!\n");
	}

	printf("Значение, посчитанное с помощью %d первых элементов ряда (float): %.64f\n",n , floatNAns);
	printf("Значение, посчитанное с помощью %d первых элементов ряда (double): %.64f\n\n", n, doubleNAns);

	floatNumerator = x; doubleNumerator = x; // возвращаю значения на начальные
	denominator = 1; // возвращаю значения на начальные
	unsigned long long floatIterations = 0, doubleIterations = 0; // переменные для подсчета кол-ва итераций

	__try {
		while (abs(floatNumerator / denominator) > e) {
			floatEpsAns += floatNumerator / denominator; // увеличиваем float сумму
			floatNumerator *= -x * x; // рассчитываем числитель след. элемента
			denominator += 2; floatIterations++; // рассчитываем знаменатель след. элемента и увеличиваем кол-во итераций
		}
	} // цикл приводит к денормализации очередного элемента ряда, что вызывает invalid_operation исключение
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		// EXCEPTION_EXECUTE_HANDLER — указывает на возможность данного обработчика обработать исключение.
		// При получении такого значения операционная система прекращает поиск релевантных обработчиков исключения и,
		// выполнив раскрутку стека, передаёт управление первому, вернувшему значение EXCEPTION_EXECUTE_HANDLER.		
		printf("Получилось денормализованное число во float!\n");
	}

	denominator = 1; // возвращаю значение на стартовое

	__try {
		while (abs(doubleNumerator / denominator) > e) {
			doubleEpsAns += doubleNumerator / denominator; // увеличиваем double сумму
			doubleNumerator *= -x * x; // рассчитываем числитель след.элемента
			denominator += 2; doubleIterations++; // рассчитываем знаменатель след.элемента и увеличиваем кол - во итераций
		}
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		printf("Получилось денормализованное число в double!\n");
	}

	printf("Значение, посчитанное до точности epsilon = %f (кол-во итераций = %lld) (float): %.64f\n", e, floatIterations, floatEpsAns);
	printf("Значение, посчитанное до точности epsilon = %f (кол-во итераций = %lld) (double): %.64f\n\n", e, doubleIterations, doubleEpsAns);

	floatNumerator = x; doubleNumerator = x; // возвращаем значения
	denominator = 1; // возвращаем значения
	floatIterations = 0, doubleIterations = 0; // возвращаем значения

	__try {
		while (abs(floatNumerator / denominator) > 0) {
			floatMaxAns += floatNumerator / denominator; // увеличиваем float сумму
			floatNumerator *= -x * x; // рассчитываем числитель след. элемента
			denominator += 2; floatIterations++; // рассчитываем знаменатель след. элемента и увеличиваем кол-во итераций
		}
	} // цикл приводит к денормализации очередного элемента ряда, что вызывает invalid_operation исключение
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) { 
		// EXCEPTION_EXECUTE_HANDLER — указывает на возможность данного обработчика обработать исключение.
		// При получении такого значения операционная система прекращает поиск релевантных обработчиков исключения и,
		// выполнив раскрутку стека, передаёт управление первому, вернувшему значение EXCEPTION_EXECUTE_HANDLER.		
		printf("Получилось денормализованное число во float!\n");
	}

	denominator = 1; // возвращаю значение на стартовое

	__try {
		while (abs(doubleNumerator / denominator) > 0) {
			doubleMaxAns += doubleNumerator / denominator; // увеличиваем double сумму
			doubleNumerator *= -x * x; // рассчитываем числитель след.элемента
			denominator += 2; doubleIterations++; // рассчитываем знаменатель след.элемента и увеличиваем кол - во итераций
		}
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		printf("Получилось денормализованное число в double!\n");
	}
	

	printf("Значение, посчитанное до максимальной точности (кол-во итераций = %lld) (float): %.64f\n", floatIterations, floatMaxAns);
	printf("Значение, посчитанное до максимальной точности (кол-во итераций = %lld) (double): %.64f\n\n", doubleIterations, doubleMaxAns);
}