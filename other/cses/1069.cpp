#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s;
    cin>>s;
    int n=s.size();
    int mx = 0, c=0;
    for (int i = 0; i < n; ++i) {
        if(i==0||s[i]==s[i-1])c++;
        else {
        	mx=max(mx,c);
        	c=1;
        }
    }
    mx=max(mx,c);
    cout<<mx<<"\n";

    return 0;
}
