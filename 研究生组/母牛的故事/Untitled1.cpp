#include<iostream>
using namespace std;
int main()
{
    int n, i;
    int f[55] = { 0,1,2,3 };  //f[0]=0,f[1]=1,f[2]=2,f[3]=3
    for (i = 4; i < 55; i++)
        f[i] = f[i - 1] + f[i - 3];
    while (cin >> n && n != 0)  //输入 n 的值，且 n 不等于0，则进入，否则退出
    {
        cout << f[n] << endl;
    }
    return 0;
}
