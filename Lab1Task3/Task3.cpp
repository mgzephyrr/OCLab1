#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <windows.h> 
#include <excpt.h>

using namespace std;

double input_double(double lowest = -DBL_MAX, double highest = DBL_MAX) {
	string input;
	bool ok = true; // ����������, ���������� �� "������������" ���������� ��������
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
			cout << "�� ����� �� �����. ���������, ����������, ����.\n";
			ok = false;
		}
		catch (out_of_range) {
			cout << "�� ����� �����, ��������� �� ��������� �������. ���������, ����������, ����.\n";
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
			cout << "�� ����� �� �����, ������������� ��� ������� �����, ���������, ����������, ����.\n";
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
				cout << "�� ����� �����, ��������� �� ��������� �������. ���������, ����������, ����.\n";
				check = false;
			}
		}

	} while (!check);

	return number;
}

int main() {
	setlocale(LC_ALL, "Russian");
	_control87(_EM_INVALID, _EM_DENORMAL); // ����������� ����������, ��������� � ���������� � ��������� ������� (�������������� � �������� ��������)

	int n;
	double x, e;

	cout << "������� x (������� ��� ����� ����� � �������� [0; 1]): ";
	x = input_double(0, 1);

	cout << "������� n (����� �����, � �������� �� [1; 1 000 000]): ";
	n = input_int(1, 1000000);

	cout << "������� epsilon (������� ��� ����� ����� � �������� (0; 1]): ";
	e = input_double(DBL_MIN, 1);

	cout << endl;

	double funcAns = atan(x);

	printf("��������, ����������� � ������� ������� atan: %.64f\n\n", funcAns); // ��������, � ������� ����� ���������� ���������� ����������

	float floatNumerator = x, floatNAns = 0, floatEpsAns = 0, floatMaxAns = 0; // ���������� ��������� � ���� ���� ���� float
	double doubleNumerator = x, doubleNAns = 0, doubleEpsAns = 0, doubleMaxAns = 0; // ���������� ��������� � ���� ���� ���� double
	unsigned long long denominator = 1; // ����������� (����� ��� ����� ����)
	__try {
		for (int i = 0; i < n; i++) {
			floatNAns += floatNumerator / denominator; // ����������� float �����
			doubleNAns += doubleNumerator / denominator; // ����������� double �����
			floatNumerator *= -x * x; doubleNumerator *= -x * x; // ������������ ��������� ��������� ���������
			denominator += 2; // ������������ �����������
		}
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		// EXCEPTION_EXECUTE_HANDLER � ��������� �� ����������� ������� ����������� ���������� ����������.
		// ��� ��������� ������ �������� ������������ ������� ���������� ����� ����������� ������������ ���������� �,
		// �������� ��������� �����, ������� ���������� �������, ���������� �������� EXCEPTION_EXECUTE_HANDLER.		
		printf("���������� ����������������� �����!\n");
	}

	printf("��������, ����������� � ������� %d ������ ��������� ���� (float): %.64f\n",n , floatNAns);
	printf("��������, ����������� � ������� %d ������ ��������� ���� (double): %.64f\n\n", n, doubleNAns);

	floatNumerator = x; doubleNumerator = x; // ��������� �������� �� ���������
	denominator = 1; // ��������� �������� �� ���������
	unsigned long long floatIterations = 0, doubleIterations = 0; // ���������� ��� �������� ���-�� ��������

	__try {
		while (abs(floatNumerator / denominator) > e) {
			floatEpsAns += floatNumerator / denominator; // ����������� float �����
			floatNumerator *= -x * x; // ������������ ��������� ����. ��������
			denominator += 2; floatIterations++; // ������������ ����������� ����. �������� � ����������� ���-�� ��������
		}
	} // ���� �������� � �������������� ���������� �������� ����, ��� �������� invalid_operation ����������
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		// EXCEPTION_EXECUTE_HANDLER � ��������� �� ����������� ������� ����������� ���������� ����������.
		// ��� ��������� ������ �������� ������������ ������� ���������� ����� ����������� ������������ ���������� �,
		// �������� ��������� �����, ������� ���������� �������, ���������� �������� EXCEPTION_EXECUTE_HANDLER.		
		printf("���������� ����������������� ����� �� float!\n");
	}

	denominator = 1; // ��������� �������� �� ���������

	__try {
		while (abs(doubleNumerator / denominator) > e) {
			doubleEpsAns += doubleNumerator / denominator; // ����������� double �����
			doubleNumerator *= -x * x; // ������������ ��������� ����.��������
			denominator += 2; doubleIterations++; // ������������ ����������� ����.�������� � ����������� ��� - �� ��������
		}
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		printf("���������� ����������������� ����� � double!\n");
	}

	printf("��������, ����������� �� �������� epsilon = %f (���-�� �������� = %lld) (float): %.64f\n", e, floatIterations, floatEpsAns);
	printf("��������, ����������� �� �������� epsilon = %f (���-�� �������� = %lld) (double): %.64f\n\n", e, doubleIterations, doubleEpsAns);

	floatNumerator = x; doubleNumerator = x; // ���������� ��������
	denominator = 1; // ���������� ��������
	floatIterations = 0, doubleIterations = 0; // ���������� ��������

	__try {
		while (abs(floatNumerator / denominator) > 0) {
			floatMaxAns += floatNumerator / denominator; // ����������� float �����
			floatNumerator *= -x * x; // ������������ ��������� ����. ��������
			denominator += 2; floatIterations++; // ������������ ����������� ����. �������� � ����������� ���-�� ��������
		}
	} // ���� �������� � �������������� ���������� �������� ����, ��� �������� invalid_operation ����������
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) { 
		// EXCEPTION_EXECUTE_HANDLER � ��������� �� ����������� ������� ����������� ���������� ����������.
		// ��� ��������� ������ �������� ������������ ������� ���������� ����� ����������� ������������ ���������� �,
		// �������� ��������� �����, ������� ���������� �������, ���������� �������� EXCEPTION_EXECUTE_HANDLER.		
		printf("���������� ����������������� ����� �� float!\n");
	}

	denominator = 1; // ��������� �������� �� ���������

	__try {
		while (abs(doubleNumerator / denominator) > 0) {
			doubleMaxAns += doubleNumerator / denominator; // ����������� double �����
			doubleNumerator *= -x * x; // ������������ ��������� ����.��������
			denominator += 2; doubleIterations++; // ������������ ����������� ����.�������� � ����������� ��� - �� ��������
		}
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		printf("���������� ����������������� ����� � double!\n");
	}
	

	printf("��������, ����������� �� ������������ �������� (���-�� �������� = %lld) (float): %.64f\n", floatIterations, floatMaxAns);
	printf("��������, ����������� �� ������������ �������� (���-�� �������� = %lld) (double): %.64f\n\n", doubleIterations, doubleMaxAns);
}