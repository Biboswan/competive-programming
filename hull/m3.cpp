#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long
#define mod 1000000007
using namespace std;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	if (f)
		x = -x;
	return x;
}
int a[500005], n;
ll s1[500005];
ll s2[500005];
ll ans = 0;
inline ll calc(int d)
{
	ll maxn = 0;
	for (int i = 1; i + d - 1 <= n; i++)
	{
		ll res = (s1[i + d - 1] - s1[i - 1]) * (s1[i + d - 1] - s1[i - 1]);
		res -= (s2[i + d - 1] - s2[i - 1]);
		if (res > maxn)
			maxn = res;
	}
	return maxn;
}
int main()
{
	int i, j, k;
	n = read();
	for (i = 1; i <= n; i++)
	{
		a[i] = read();
	}
	for (i = 1; i <= n; i++)
	{
		s1[i] = s1[i - 1] + a[i];
		s2[i] = s2[i - 1] + a[i] * a[i];
	}
	srand((unsigned long long)new char);
	while (((double)(clock())) / CLOCKS_PER_SEC < 1.95)
	{
		int l = 1, r = n;
		while (l + 5 <= r)
		{
			int m1 = l + rand() % (r - l + 1);
			int m2 = r - rand() % (r - l + 1);
			if (m1 > m2)
				swap(m1, m2);
			ll t1 = calc(m1), t2 = calc(m2);
			if (t1 > ans)
				ans = t1;
			if (t2 > ans)
				ans = t2;
			if (t1 > t2)
			{
				r = m2;
			}
			else
			{
				l = m1;
			}
		}
		for (int i = max(0, l - 10); i <= min(n, l + 10); i++)
		{
			ans = max(ans, calc(i));
		}
	}
	printf("%lld\n", ans / 2);
	return 0;
}
