
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int a[maxn],f[maxn];
int getf(int x)
{
	return f[x] = f[x] == x ? x:getf(f[x]); 
}
int main()
{
	for(int i=1;i<=maxn-1;i++)
		f[i] = i;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		int nf = getf(a[i]);
		a[i] = nf;
		f[a[i]] = getf(nf+1);
	}
	for(int i=1;i<=n;i++) {
		cout << a[i];
		if(i != n)
			cout << " ";
	}
	return 0;
}
