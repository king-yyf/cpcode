#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 5e5 + 13;
const int A = 1e6 + 13;
 
vector<int> divs[A];
int a[N];
 
int lmx[N], rmx[N];
int lmn[N], rmn[N];
 
vector<int> pos[A];
int ind[A];
 
void solve() {
    int n;
    cin >> n;
 
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
 
    {
        stack<int> st;
        for(int i = 0; i < n; i++) {
            while(!st.empty() && a[st.top()] < a[i])
                st.pop();
 
            lmx[i] = (st.empty() ? -1 : st.top());
            st.push(i);
        }
    }
 
    {
        stack<int> st;
        for(int i = n - 1; i >= 0; i--) {
            while(!st.empty() && a[st.top()] <= a[i])
                st.pop();
 
            rmx[i] = (st.empty() ? n : st.top());
            st.push(i);
        }
    }
 
    {
        stack<int> st;
        for(int i = 0; i < n; i++) {
            while(!st.empty() && a[st.top()] >= a[i])
                st.pop();
 
            lmn[i] = (st.empty() ? -1 : st.top());
            st.push(i);
        }
    }
 
    {
        stack<int> st;
        for(int i = n - 1; i >= 0; i--) {
            while(!st.empty() && a[st.top()] >= a[i])
                st.pop();
 
            rmn[i] = (st.empty() ? n : st.top());
            st.push(i);
        }
    }

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        for(int x : divs[a[i]]) {
            if(ind[x] >= 1) {
                int j = pos[x][ind[x] - 1];
                if(j > lmx[i] && rmn[j] > i) {
                    ans += (j - max(lmx[i], lmn[j])) * 1ll * (min(rmx[i], rmn[j]) - i);
                }
            }
 
            if(ind[x] < pos[x].size()) {
                int j = pos[x][ind[x]];
                if(j < rmx[i] && lmn[j] < i) {
                    ans += (i - max({lmx[i], lmn[j], ind[x] >= 1 ? pos[x][ind[x] - 1] : -1})) * 1ll * (min(rmx[i], rmn[j]) - j);
                }
 
            }
        }
 
        ind[a[i]]++;
    }
 
    cout << ans << endl;
 
    for(int i = 0; i < n; i++) {
        pos[a[i]].erase(pos[a[i]].begin(), pos[a[i]].end());
        lmx[i] = rmx[i] = lmn[i] = rmn[i] = 0;
        ind[a[i]] = 0;
    }
}
 
int main() {
    for(int i = 1; i < A; i++) {
        for(int j = i; j < A; j += i)
            divs[j].push_back(i);
    }
 
    int t;
    cin >> t;
 
    while(t--)
        solve();
}