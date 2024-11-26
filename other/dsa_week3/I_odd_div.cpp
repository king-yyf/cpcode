#include <bits/stdc++.h>
using namespace std;

void wt(vector<int> &a){
    for(int x:a)cout<<x<<" ";cout<<"\n";
}

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<int> f(10);
    vector<int> s(11);
    auto get=[&](int x){
        int p=1;
        for(int i=1;i<=x;i+=2)if(x%i==0)p=i;
            return p;
    };
    for(int i=1;i<10;++i)f[i]=get(i);
        for(int i=1;i<=10;++i)s[i]=s[i-1]+f[i];
            wt(f);wt(s);
    return 0;
}
