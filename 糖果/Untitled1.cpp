#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1e2 + 7, INF = 0x3f3f3f3f;
// ״̬ת�ƾ��� 
int f[1 << 20];
// ���ÿ���ǹ���״̬ 
int s[N];

int main() {
	int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;
    // �����ǹ���ζ���ܳ��ֵ��������2^m���� 
    int all = (1 << m) - 1;
    for (int i = 0; i <= all; i++) {
    	f[i] = INF;	
    }
    for (int i = 0; i < n; i++) {
    	//�洢����ǹ����ֵ�����
        int state = 0;
        for (int j = 0; j < k; j++) {
            int candy = 0;
            cin >> candy;
            //��������ǹ����ֹ����
            state |= (1 << (candy - 1));
        }
        s[i] = state;
        //����Щ�ǹ�������Ҫ��һ��
        f[state] = 1;
    }
    //ö��ÿһ��
    for (int i = 0; i < n; i++) {
    	//ö�����п���״̬
        for (int j = 0; j <= all; j++) {
        	//������״̬���ǹ�����û���򵽹�������
            if (f[j] == INF) {
            	continue;	
            }
            //�������ת��
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
