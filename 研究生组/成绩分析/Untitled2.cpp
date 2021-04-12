#include<iostream>
#include<stdio.h>
using namespace std;

int sum = 0;
int minScore = 100;
int maxScore = -1;

int main() {
	int n = 0, s = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s;
		if (s > maxScore) {
			maxScore = s;
		}
		if (s < minScore) {
			minScore = s;
		}
		sum += s;
	}
	printf("%d\n%d\n%.2f", minScore, maxScore, float(sum) / float(n));
	return 0;
}
