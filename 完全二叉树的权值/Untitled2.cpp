#include<iostream>
#define lld long long int
using namespace std;
int tree(int n) {
    int x = 1, y = 0, c;//
    lld max=0;
    while(n>0) {
        lld sum=0;
        //��ȫ���������һ����ܲ��������� i ҪС�� min(n ,x);
        for(int i = 0; i < min(n,x); i++) {
            int t;
            cin >> t;
            //cout << t << " ";//���
            sum+=t;
        }
        //cout << endl;
        y++;
        if(max < sum) {
            max = sum;
            c = y;
        }
        n = n - x;
        x = x * 2;
    }
    return c;
}
int main() {
    int n;
    while(cin >> n) {
        cout << tree(n) << endl;
    }
    return 0;
}
