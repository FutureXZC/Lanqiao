#include<iostream>
using namespace std;

int mat[105][105];

int main() {
	int n = 0, m = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mat[i][j];
		}
	}
	for (int j = 0; j < m; j++) {
		for (int i = n - 1; i >= 0; i--) {
			cout << mat[i][j];
			if (i != 0) {
				cout << " ";
			}
		}
		cout << endl;
	}
	return 0;
}
