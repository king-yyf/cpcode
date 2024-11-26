#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
int n, m;
cin >> n >> m;

if (n-m==0)
{
cout << “YES\n”;
return;
}
if (n % 3 || m > n)
{
cout << “NO\n”;
return;
}

set<int> st;
st.insert(n);
while (st.size())
{
int x = *(st.begin());
st.erase(st.begin());
if (x == m)
{
cout << “YES” << endl;
return;
}

if (x % 3==0)
{
x /= 3;
if (x == m || 2 * x == m)
{
cout << “YES” << endl;
return;
}
if (x % 3==0)
{
st.insert(x);
st.insert(2 * x);
}
}
}
cout << “NO\n”;
}

int32_t main()
{
int t;
cin >> t;
while (t–)
solve();
}