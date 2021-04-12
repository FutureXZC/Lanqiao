#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int reverseNum(int m) {
	int a[100];
	int i = 0, tmp = m, res = 0;
	while (tmp) {
		a[i] = tmp % 10;
		tmp /= 10;
		i++;
	}
	for (int j = 0; j < i; j++) {
		res = res * 10 + a[j];
	}
	return res;
}

int count(int m, int step) {
	if (++step >= 8) {
		return 0;
	}
	int tmp = m + reverseNum(m);
	stringstream ss;
	ss << tmp;
	string s = ss.str();
	bool flag = true;
	for (int i = 0, j = s.length() - 1; i < j ;i++, j--) {
		if (s[i] != s[j]) {
			flag = false;
			break;
		}
	}
	if (!flag) {	
		return count(tmp, step);
	}
	return step;
}

int main() {
	int n = 0;
	cin >> n;
	while (n--) {
		int m = 0;
		cin >> m;
		cout << count(m, 0) << endl;
	}
	return 0;
}
