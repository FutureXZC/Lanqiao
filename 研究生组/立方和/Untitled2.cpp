#include<iostream>
using namespace std;

int main() {
	long long sum = 0;
	int a = 0, b = 0, c = 0, d = 0;
	int arr[4] = {2, 0, 1, 9};
	for (int i = 1; i <= 2019; i++) {
		if (i >= 1000) {
			a = i / 1000;
			b = i / 100 % 10;
			c = i / 10 % 10;
			d = i % 10;
			for (int j = 0; j < 4; j++) {
				if (a == arr[j] || b == arr[j] || c == arr[j] || d == arr[j]) {
					sum += i * i * i;
					cout << i << endl;
					break;
				}
			}
		} else if (i >= 100) {
			a = i / 100;
			b = i / 10 % 10;
			c = i % 10;
			for (int j = 0; j < 4; j++) {
				if (a == arr[j] || b == arr[j] || c == arr[j]) {
					sum += i * i * i;
					cout << i << endl;
					break;
				}
			}
		} else if (i >= 10) {
			a = i / 10;
			b = i % 10;
			for (int j = 0; j < 4; j++) {
				if (a == arr[j] || b == arr[j]) {
					sum += i * i * i;
					cout << i << endl;
					break;
				}
			}
		} else {
			for (int j = 0; j < 4; j++) {
				if (i == arr[j]) {
					sum += i * i * i;
					cout << i << endl;
					break;
				}
			}
		}
	}
	// 283551455541
	cout << sum << endl;
	return 0;
}
