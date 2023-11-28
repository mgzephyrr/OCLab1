#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <numeric>
#include <algorithm>
#include <cmath>

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

using namespace std;

#define readvectorint(x, n) vector<int> x(n); for(int i = 0; i < n; i++) scanf_s("%d", &x[i])

int main() {
	static signed __int8 A;
	A = -127;
	int iteration = 1;
	while (A < 0)
	{
		cout << A << endl;
		A = A - 1;
		iteration++;
	}
	cout << A << endl;
	return 0;
}