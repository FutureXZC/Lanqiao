#include<iostream>
using namespace std;

int main() {
	int count = 1;
	for (int i = 0; i < 40; i++) {
		bool flag = false;
		for (int j = 0, tmp = i; j <= i; j++, tmp--) {
			if (j == 19 && tmp == 19) {
				cout << count << endl; // 761
				flag = true;
				break;	
			}
			count++;
		}
		if (flag) {
			break;
		}
	}
	return 0;
}
