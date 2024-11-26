#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string str;
    cin >> str;

    int n = str.length();

    int mx = INT_MAX;
    for (int i = 0; i < 26; i++)
    {
        int x = 0, tmp = 0;
        while (x < n)
        {
            while (x < n && str[x] == i + 'a')
                x++;
            int y = x;
            while (y < n && str[y] != i + 'a')
                y++;
            tmp = max(tmp, y - x);
            x = y;
        }
        mx = min(mx, tmp);
    }
    if (mx == 0)
    {
        cout << mx << endl;
        return;
    }
    int ans = ceil(log2(mx));
    if (!(mx & (mx - 1)))
        ans++;
    cout << ans << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
        solve();
}
