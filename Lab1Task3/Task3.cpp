#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	unsigned int n;
	double x, e;

	cout << "������� x: ";
	cin >> x;
	cout << "\n������� n: ";
	cin >> n;
	cout << "\n������� epsilon: ";
	cin >> e;
	cout << endl;

	double funcAns = atan(x);

	printf("��������, ����������� � ������� ������� atan: %.64f\n\n", funcAns); // ��������, � ������� ����� ���������� ���������� ����������

	float floatNumerator = x, floatNAns = 0, floatEpsAns = 0, floatMaxAns = 0; // ���������� ��������� � ���� ���� ���� float
	double doubleNumerator = x, doubleNAns = 0, doubleEpsAns = 0, doubleMaxAns = 0; // ���������� ��������� � ���� ���� ���� double
	unsigned long long denominator = 1; // ����������� (����� ��� ����� ����)

	for (int i = 0; i < n; i++) {
		floatNAns += floatNumerator / denominator; // ����������� float �����
		doubleNAns += doubleNumerator / denominator; // ����������� double �����
		floatNumerator *= -x * x; doubleNumerator *= -x * x; // ������������ ��������� ��������� ���������
		denominator += 2; // ������������ �����������
	}

	printf("��������, ����������� � ������� %d ������ ��������� ���� (float): %.64f\n",n , floatNAns);
	printf("��������, ����������� � ������� %d ������ ��������� ���� (double): %.64f\n\n", n, doubleNAns);

	floatNumerator = x; doubleNumerator = x; // ��������� �������� �� ���������
	denominator = 1; // ��������� �������� �� ���������
	unsigned long long floatIterations = 0, doubleIterations = 0; // ���������� ��� �������� ���-�� ��������

	while (abs(floatNumerator / denominator) > e) {
		floatEpsAns += floatNumerator / denominator; // ����������� float �����
		floatNumerator *= -x * x; // ������������ ��������� ����. ��������
		denominator += 2; floatIterations++; // ������������ ����������� ����. �������� � ����������� ���-�� ��������
	}

	denominator = 1; // ��������� �������� �� ���������

	while (abs(doubleNumerator / denominator) > e) {
		doubleEpsAns += doubleNumerator / denominator; // ����������� double �����
		doubleNumerator *= -x * x; // ������������ ��������� ����.��������
		denominator += 2; doubleIterations++; // ������������ ����������� ����. �������� � ����������� ���-�� ��������
	}

	printf("��������, ����������� �� �������� epsilon = %f (���-�� �������� = %lld) (float): %.64f\n", e, floatIterations, floatEpsAns);
	printf("��������, ����������� �� �������� epsilon = %f (���-�� �������� = %lld) (double): %.64f\n\n", e, doubleIterations, doubleEpsAns);

	floatNumerator = x; doubleNumerator = x; // ���������� ��������
	denominator = 1; // ���������� ��������
	floatIterations = 0, doubleIterations = 0; // ���������� ��������

	while (abs(floatNumerator / denominator) > 0) {
		floatMaxAns += floatNumerator / denominator; // ����������� float �����
		floatNumerator *= -x * x; // ������������ ��������� ����. ��������
		denominator += 2; floatIterations++; // ������������ ����������� ����. �������� � ����������� ���-�� ��������
	}

	denominator = 1; // ��������� �������� �� ���������

	while (abs(doubleNumerator / denominator) > 0) {
		doubleMaxAns += doubleNumerator / denominator; // ����������� double �����
		doubleNumerator *= -x * x; // ������������ ��������� ����.��������
		denominator += 2; doubleIterations++; // ������������ ����������� ����.�������� � ����������� ��� - �� ��������
	}

	printf("��������, ����������� �� ������������ �������� (���-�� �������� = %lld) (float): %.64f\n", floatIterations, floatMaxAns);
	printf("��������, ����������� �� ������������ �������� (���-�� �������� = %lld) (double): %.64f\n\n", doubleIterations, doubleMaxAns);
}