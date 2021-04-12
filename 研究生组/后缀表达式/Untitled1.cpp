#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a[200005], sum = 0, mi = 1000000009;
int n, m, fu = 0;
bool cmp(int a, int b) { return a > b; }
int main() 
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n + m + 1; i++) 
    {
        scanf("%lld", &a[i]);
        if (a[i] < 0) fu++;
        sum += a[i];
        mi = min(mi, a[i]);
    }
    if (m == 0) printf("%lld\n", sum);
    else
    {
        if(fu == 0) printf("%lld\n", sum - mi - mi);
        else
        {
            if (fu == n + m + 1)  //***全是负数
            {
                sum = 0; mi = 1000000009;
                for (int i = 0; i < n + m + 1; ++i)
                {
                    sum += abs(a[i]);
                    mi = min(mi, abs(a[i]));
                }
                printf("%lld\n", sum - mi - mi);
            }
            else
            {
                sum = 0;
                for (int i = 0; i < n + m + 1; ++i) sum += abs(a[i]);
                printf("%lld\n", sum);
            }
        }
    }
    return 0;
}
