#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
    for(int x : a) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<int> f = {2,34,5,6,7};
    wt(f);
    vector<int>  g = {4,3,56,2,1};
    cout<<"before:\n";
    wt(f);
    wt(g);
    g.swap(f);
    cout<<"after:\n";
    wt(f);
    wt(g);
    return 0;
}