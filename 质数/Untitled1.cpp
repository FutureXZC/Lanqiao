#include<iostream> 
using namespace std;

bool judge(int num) {
	int n = num / 2;
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	int count = 1;
	int i = 1;
	while(count <= 2019) {
		i++;
		if (judge(i)) {
			cout << i << " " << count<< endl;
			count++;
		}
	}
	// 17569
	cout << "result: " << i << endl;
	return 0;
}
