#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t,n;
    cin>>t;
    string s;
    while(t--){
        cin>>n;
        cin>>s;
        int c=0;
        int i=0,j=n-1;
        while(i<j){
            c+=s[i++]!=s[j--];
        }
        cout<<c<<"\n";
    }
    return 0;
}
