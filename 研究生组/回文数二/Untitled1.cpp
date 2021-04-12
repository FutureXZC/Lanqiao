#include<iostream>
using namespace std;

int a[1000] = {0}, b[1000] = {0};
int main() {
	int n = 0, len = -1, step = 0;
	long long m = 0;
	cin >> n >> m;
	while (m) {
		len++;
		a[len] = m % 10;
		m /= 10;
	}
	while (1) {
		for (int i = 0; i <= len; i++) {
			b[i] = a[i] + a[len - i];
		}
		for (int i = 0; i <= len; i++) {
			if (b[i] >= n) {
				b[i] -= n;
				b[i + 1]++;
				if (i == len) {
					len++; 
				}
			}
			a[i] = b[i]; 
		}
		step++;
		bool flag = true;
		for (int i = 0; i < len / 2; i++) {
			if (a[i] != a[len - i]) {
				flag = false;
				break;
			}
		}
		if (step > 30) {
			cout << "Impossible!" << endl;
			break;
		}else if (flag) {
			cout << "STEP=" << step << endl;
			break;
		}
	}
	return 0;
}
