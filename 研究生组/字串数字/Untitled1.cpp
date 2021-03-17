#include<iostream>
#include<math.h>
using namespace std;

int main() {
	long long sum = 15 + 1 * 26 + 12 * pow(26, 2) + 17 * pow(26, 3) 
			+ 14 * pow(26, 4) + pow(26, 5) + 12 * pow(26, 6);
	
	// abcdefghijkl mn  o  p q  rstuvwxyz
	// 1     7    12 14 15   17
	char *num = "LANQLAO";
	// 3725575297
	cout << sum << endl;
	return 0;	
}
