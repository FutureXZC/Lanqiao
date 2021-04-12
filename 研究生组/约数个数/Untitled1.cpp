#include <bits/stdc++.h>
using namespace std;

int main() {
	int count = 0, a = 78120;
	
	for (int i = 1; i <= a; i++) {
		if (a % i == 0)
			count++;
	} 
	cout << count << endl; // 96
	return 0;
}
