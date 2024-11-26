#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351163

/*
给你一棵树，它有n个顶点和n−1条边。(1 ≤ n ≤ 2 * 1e5)

对于整数L，R（1≤L≤R≤n），让我们定义函数 f(L,R)

设S是编号为L到R的顶点的集合。f(L,R)表示仅由顶点集合S和其端点都属于S的边形成的子图中连通分量的数量。

计算所有 f(L,R)的和。 1 <= L <= R <= n

*/

const int mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n;
	cin >> n;

	long long res = n * 1ll * (n + 1) * (n + 2) / 6;

	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		if (u > v) swap(u, v);
		res -= u * 1ll * (n - v + 1);
	}

	cout << res << "\n";

}