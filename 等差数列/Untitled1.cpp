#include<iostream>
#include<algorithm>
using namespace std;

int num[100005];
int n = 0;

int gcd(int a, int b) {
	if (a < b) {
		swap(a, b);
	}
	if (!b) {
		return a;	
	}
	int c = a % b;
	if (c) {
		return gcd(b, c);
	}
	return b;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	sort(num, num + n);
	int d = num[1] - num[0];
	if (d == 0) {
		cout << n;
	} else {
		for (int i = 2; i < n; i++) {
			d = gcd(num[i] - num[i-1], d);
		}	
		cout << (num[n-1] - num[0]) / d + 1;
	}
	return 0;
}

