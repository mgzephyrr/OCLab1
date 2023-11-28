#include <iostream>
#include <string>

using namespace std;

const float DAY_FARE = 5.3;
const float NIGHT_FARE = 3.25;

int input_a_number(string message, int lowest = INT_MIN, int highest = INT_MAX) {
	string input;
	bool check = true;
	int number;

	do {
		cout << message;
		cin >> input;
		cout << endl;

		if (input.find_first_not_of("0123456789") != string::npos){
			cout << "�� ����� �� �����, ������������� ��� ������� �����, ���������, ����������, ����.\n";
			check = false;
		}
		else {
			try {
				number = stoi(input);
				if (number < lowest or number > highest) {
					cout << "�� ����� �����, ��������� �� ��������� �������. ���������, ����������, ����.\n";
					check = false;
				}
				else {
					check = true;
				}
			}
			catch (out_of_range) {
				cout << "�� ����� �����, ��������� �� ��������� �������. ���������, ����������, ����.\n";
				check = false;
			}			
		}
			
	} while (!check);

	return number;
}

int main(){
	setlocale(LC_ALL, "Russian");
	
	int energyConsumedAtDay, energyConsumedAtNight;
	cout << "������������! ��� ��������� ��� ���������� ������ ����������� ��������������.\n\n";

	int previousMonthDaytime = input_a_number("����������, ������� ��������� �������� �� �������� ������ �� ������� ����� (����� ����� � �������� �� 0 �� 999 999): ", 0, 999999);
	int currentMonthDaytime = input_a_number("����������, ������� ��������� �������� �� �������� ������ �� ������� ����� (����� ����� � �������� �� 0 �� 999 999): ", 0, 999999);

	int previousMonthNighttime = input_a_number("����������, ������� ��������� �������� �� ������� ������ �� ������� ����� (����� ����� � �������� �� 0 �� 999 999): ", 0, 999999);
	int currentMonthNighttime = input_a_number("����������, ������� ��������� �������� �� ������� ������ �� ������� ����� (����� ����� � �������� �� 0 �� 999 999): ", 0, 999999);

	if (currentMonthDaytime < previousMonthDaytime) {
		energyConsumedAtDay = 1000000 - previousMonthDaytime + currentMonthDaytime;
	}
	else {
		energyConsumedAtDay = currentMonthDaytime - previousMonthDaytime;
	}

	if (currentMonthNighttime < previousMonthNighttime) {
		energyConsumedAtNight = 1000000 - previousMonthNighttime + currentMonthNighttime;
	}
	else {
		energyConsumedAtNight = currentMonthNighttime - previousMonthNighttime;
	}

	double totalFare = energyConsumedAtDay * DAY_FARE + energyConsumedAtNight * NIGHT_FARE;

	printf("�� ���� ����� �� ������ ��������� %.2f ���. �� �������������� ���� ��������������.\n", totalFare);
}