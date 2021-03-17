#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

bool judge(long long d) {
	long long step = d / 2;
	for (long long i = 2; i <= step; i++) {
		if (d % i == 0) {
			cout << "false" << endl;
			return false;
		}
	}
	cout << "true" << endl;
	return true;
}

int main() {
	long long c = 20190324, d = 212353, n = 1001733993063167141;
	long long p = 0, q = 0, e = 0, res = 0;
	long long step = n / 2;
	bool flag = false;
	for (long long i = 2; i <= step && !flag; i++) {
		// cout << i << endl;
		if (n % i == 0) {
			p = i;
			q = n / i;
			long long pq = (p - 1) * (q - 1);
			cout << p << " " << q << endl;
			// 891234941 1123984201
			if (judge(p) && judge(q) && d % pq && pq % d) {
				cout << "true" << endl;
				for (long long j = pq / d; ; j++) {
					if (d * j % pq == 1) {
						e = j;
						flag = true;
						cout << "e: " << e << endl;
						break;
					}
				}
			}
			if (flag) {
				res = (long long)pow(d, e) % n;
				cout << res << endl;
				break;
			}
		}
	}
	return 0;
} 
