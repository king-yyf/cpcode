#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int n, m, q;
        cin >> n >> m >> q;
        int a[n];
        vector<int> b;
        for (int i = 0; i < n; i++)
            cin >> a[i];

        for (int i = 0; i < m; i++)
        {
            int x;
            cin >> x;

            if (b.empty() || b.size() > 0 && b.back() != x)
            {
                b.push_back(x);
            }
        }

        m = b.size();

        unordered_set<int> s;
        int ans = 1;

        int idx = 0;

        for (int i = 0; i < m; i++)
        {

            if (b[i] == a[idx])
            {
                s.insert(a[idx]);
                idx++;
            }
            else
            {
                auto it = s.find(b[i]);

                if (it != s.end())
                {
                }
                else
                {
                    ans = 0;
                    break;
                }
            }
        }

        if (ans)
        {
            cout << "YA" << endl;
        }
        else
        {
            cout << "TIDAK" << endl;
        }
    }
}