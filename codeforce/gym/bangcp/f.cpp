#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define pb push_back
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fr(m,n) for(i=m;i<n;i++)
#define frr for(i=n-1;i>=0;i--)
#define frr1 for(i=n;i>=1;i--)
#define ff for(i=0;i<n;i++)
#define ff1 for(i=1;i<=n;i++)
#define frj(m,n) for(j=m;j<n;j++)
#define frl(m,n) for(l=m;l<n;l++)
#define frd(m,n) for(d=m;d<n;d++)
#define wq while(q--)
#define lb lower_bound
#define ub upper_bound
#define yes cout << "YES"
#define no cout << "NO"
#define yesm cout << "Yes"
#define nom cout << "No"
#define inf INT_MAX
#define ext {cout << -1; return;}
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) (a*(b/gcd(a,b)))
#define rall(a) (a).rbegin(),(a).rend()
#define vi vector<int>
#define vb vector<bool>
#define pi pair<int,int>
#define vvi vector<vi>
#define vc vector<char>
#define vs vector<string>
#define vpi vector<pi>
#define mii map<int,int>
#define mbi map<int,bool>
#define mci map<char,int>
#define als(i) cout << i.fi << " " << i.se << endl
#define si set<int>
#define mp make_pair
#define fi first
#define se second
#define sz size()
#define el cout<<endl
bool id = 0, id1 = 0,  id2 = 0;
int x = 0, y = 0, z = 0;
int ans = 0, num = 0, sum = 0, mo = 0, me = 0, cnt = 0, mi = inf, ma = 0, mid;
string s, p, st;
int n = 0, m = 0, k = 0, i = 0, j = 0, l = 0, r = 0, q = 0, a = 0, b = 0, c = 0, d = 0;
const int mod = 1e9 + 7;
// const int mod = 998244353;
const double PI = 3.141592653589793238462643383279502884;
const long long N = 1e5 + 2;
int add(int x, int y) {return ((x + y) % mod + mod) % mod;}
int mul(int x, int y) {return x * y % mod;}
int binpow(int x, int y) {int z = 1; while (y) {if (y % 2 == 1) z = mul(z, x); x = mul(x, x); y /= 2;} return z;}
int inv(int x) {return binpow(x, mod - 2);}
int divide(int x, int y) {return mul(x, inv(y));}
ll factorial(ll n) {ll ans = 1; for (int i = 1; i <= n; ++i) {ans = ans * i;} return ans;}
bool check_prime(ll n) {if (n <= 1)return false; if (n <= 3)return true; if (n % 2 == 0 || n % 3 == 0)return false; for (int i = 5; i * i <= n; i = i + 6)if (n % i == 0 || n % (i + 2) == 0)return false; return true;}
vector<int> A, ST;
void build(int node, int L, int R) {
	if (L == R) {
		ST[node] = A[L];
	}
	else {
		int mid = (L + R) / 2;
		build(2 * node, L, mid);
		build(2 * node + 1, mid + 1, R);
		ST[node] = ST[2 * node] + ST[2 * node + 1];
	}
}
void update(int node, int L, int R, int idx, int val) {
	if (L == R) {
		A[idx] %= val;
		ST[node] %= val;
	}
	else {
		int mid = (L + R) / 2;
		if (L <= idx and idx <= mid)
			update(2 * node, L, mid, idx, val);
		else
			update(2 * node + 1, mid + 1, R, idx, val);
		ST[node] = ST[2 * node] + ST[2 * node + 1];
	}
}
int query(int node, int tl, int tr, int l, int r) {
	if (r < tl or tr < l)
		return 0;
	if (l <= tl and tr <= r)
		return ST[node];
	int tm = (tl + tr) / 2;
	return query(2 * node, tl, tm, l, r) + query(2 * node + 1, tm + 1, tr, l, r);
}
int maxAreaOfIsland(vector<vector<int>>& grid) {
	int ans = 0;
	int r = grid.size(), c = grid[0].size();
	vector<vector<bool>> vis(r, vector<bool>(c, false));
	int dir_x[] = {0, 0, 1, -1};
	int dir_y[] = {1, -1, 0, 0};

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (grid[i][j] == 0 || vis[i][j])continue;
			queue<pair<int, int>> q;
			int island = 0;
			q.push({i, j});
			vis[i][j] = true;
			while (!q.empty()) {
				auto front = q.front();
				q.pop();
				island += grid[front.fi][front.se];
				for (int d = 0; d < 4; d++) {
					int qr = front.first + dir_x[d];
					int qc = front.second + dir_y[d];
					if (qr < 0 || qr >= r || qc < 0 || qc >= c) {
						continue;
					}
					if (grid[qr][qc] == 0) continue;
					if (vis[qr][qc]) continue;
					q.push({qr, qc});
					vis[qr][qc] = true;
				}
			}
			ans = max(ans, island);
		}
	}
	return ans;
}
bool v[101][101] = {0};
int vis[101][101] = {0};
void dfs(int i, int j) {
	vis[i][j] = 1;
	// cout << i << " " << j;
	// el;
	if (i != 0 && !vis[i - 1][j] && v[i - 1][j] != 0) {
		dfs(i - 1, j);
	}
	if (j != 0 && !vis[i][j - 1] && v[i][j - 1] != 0) {
		dfs(i, j - 1);
	}
	if (i != n - 1 && !vis[i + 1][j] && v[i + 1][j] != 0) {
		dfs(i + 1, j);
	}
	if (j != m - 1 && !vis[i][j + 1] && v[i][j + 1] != 0) {
		dfs(i, j + 1);
	}
}
// int nCr(int n, int r) {if (n < r) return 0; if (r == 0) return 1; int mm = (fac[r] * fac[n - r]); mm %= mod; k = divide(fac[n], mm); k %= mod; return k;}
int lcs(vi v, vi w) {
	unordered_map<int, int> mp;
	int m = v.sz;
	fr(0, m)mp[v[i]] = i + 1;
	vi tmp;
	fr(0, m) {
		if (mp.find(w[i]) != mp.end()) {
			tmp.pb(mp[w[i]]);
		}
	}
	vi tail;
	tail.pb(tmp[0]);
	fr(1, tmp.sz) {
		if (tmp[i] > tail.back()) tail.pb(tmp[i]);
		else if (tmp[i] < tail[0]) tail[0] = tmp[i];
		else {
			auto it = lower_bound(all(tail), tmp[i]);
			*it = tmp[i];
		}
	}
	return tail.sz;
}
void solve() {
	id = 0, id1 = 0,  id2 = 0;
	x = 0, y = 0, z = 0, cnt = -1;
	ans = 0, num = 0, sum = 0, mo = 0, me = 0, cnt = 0, mi = inf, ma = 0;
	s = "", p = "", st = "";
	n = 0, m = 0, k = 0, i = 0, j = 0, l = 0, r = 0, q = 0, a = 0, b = 0, c = 0, d = 0;

	// cin >> n; vi v(n), w(n), f(n);
	// ff{
	// 	cin >> v[i] >> w[i] >> f[i];
	// }
	// cin>>k;
	// vi
	// fr(0,k){
	// 	cin>>
	// }
	cin >> n; vi v(n), w(n);
	ff{
		cin >> v[i];
	}
	ff{
		cin >> w[i];
	}
	// vvi dp(n + 1, vi(n + 1, -1));
	cout << 2 * (n - lcs(v, w));
}
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
	int T = 1;
	cin >> T;
	// vector <ll> vec;
	// bool prime[10005];
	// memset(prime, true, sizeof(prime));
	// for (ll i = 2; i <= 10000; i++) {
	// 	if (prime[i]) {
	// 		vec.push_back(i);
	// 		for (ll j = i * i; j <= 10000; j += i) {
	// 			prime[j] = false;
	// 		}
	// 	}
	// }
	// for (int i = 2; i < N; i++)
	// {
	// 	if (pfact[i].size() == 0)
	// 	{
	// 		for (int j = i; j < N; j += i)
	// 			pfact[j].pb(i);
	// 	}
	// }
	while (T--) {
		solve();
		cout << endl;
	} return 0;
}
