#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1e2 + 7, INF = 0x3f3f3f3f;
// 状态转移矩阵 
int f[1 << 20];
// 存放每包糖果的状态 
int s[N];

int main() {
	int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;
    // 所有糖果口味可能出现的情况，共2^m方种 
    int all = (1 << m) - 1;
    for (int i = 0; i <= all; i++) {
    	f[i] = INF;	
    }
    for (int i = 0; i < n; i++) {
    	//存储这袋糖果出现的种类
        int state = 0;
        for (int j = 0; j < k; j++) {
            int candy = 0;
            cin >> candy;
            //这个种类糖果出现过标记
            state |= (1 << (candy - 1));
        }
        s[i] = state;
        //买这些糖果至少需要买一袋
        f[state] = 1;
    }
    //枚举每一袋
    for (int i = 0; i < n; i++) {
    	//枚举所有可能状态
        for (int j = 0; j <= all; j++) {
        	//如果这个状态的糖果曾经没有买到过就跳过
            if (f[j] == INF) {
            	continue;	
            }
            //否则可以转移
            f[j | s[i]] = min(f[j | s[i]], f[j] + 1);
        }
    }
    if (f[all] == INF) {
    	cout<<-1<<endl;	
    } else {
    	cout<<f[all]<<endl;	
    }
    return 0;
}
