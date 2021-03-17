#include<iostream>
#include<vector>
using namespace std;

int main() {
	int N;
	cin >> N;
	if(N <= 1) 
		return 0;
	vector<bool> visit(N + 1, false);
	for (int i = 2; i <= N; i++) {
		if (!visit[i]) {
			cout << i << endl;
			int k = i;
			while (k <= N) {
				visit[k] = true;
				k += i;
			} 
		}
	} 
	return 0;
}
