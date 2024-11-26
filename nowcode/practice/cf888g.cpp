#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N = 200100, M = N * 31;
int tr[M][2], idx = 1, mx[M], a[N], n;
ll gans=0;

void add(int x, int c) {
	int  p = 0;
	for (int i = 29; i >= 0; --i) {
		mx[p] = max(mx[p], c);
		int g = (x >> i) & 1;
		if (tr[p][g])
			p = tr[p][g];
		else
			p = tr[p][g] = idx++;
	}
	mx[p] = max(mx[p], c);
}

int query(int x, int b) {
	int p = 0, ans = 0;
	for (int i = 29; ~i; --i) {
		int u = (x >>i) & 1;
		if (tr[p][u] && mx[tr[p][u]] >= b) 
			p = tr[p][u];
		else p = tr[p][!u], ans += (1 << i);
	}
	return ans;
}

void run(int l, int r, int k) {
	if (l + 1 >= r || k < 0)
		return;
	int mid = l;
	while (mid < r && !((a[mid] >> k) & 1))
		++mid;
	run(l, mid, k - 1);
	run(mid, r, k - 1);
	if (mid == l || mid == r)
		return;
	int ans = (1 << 30) + 100;
	for (int i = l; i < mid; ++i)
		ans = min(ans, query(a[i], mid));
	gans += ans;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for (int i = 0; i < n; ++i)
		add(a[i], i);
	run(0, n, 29);
	cout << gans << "\n";
	return 0;
}