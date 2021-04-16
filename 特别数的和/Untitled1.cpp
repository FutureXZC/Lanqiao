#include<iostream>
using namespace std;

bool judge(int k) {
	int tmp = 0;
	while (k) {
		tmp = k % 10;
		if (tmp == 2 || tmp == 0 || tmp == 1 || tmp == 9) {
			return true;
		}
		k /= 10;
	}
	return false;
}

int main() {
	int n = 0, sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		if (judge(i)) {
			sum += i;
		}
	}
	cout << sum;
	return 0;
}
