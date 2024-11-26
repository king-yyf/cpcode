#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,t;
    cin>>n>>t;
    string s1,s2;
    cin>>s1>>s2;
    t=n-t;
    string bs;
    for(char x='a';x<='z';++x)
        bs+=x;
	int c0 = 0, c1 =0;
	for(int i=0;i<n;++i){
		if(s1[i]==s2[i]) c0++;else c1++;
	}
    string res;
	if(c0>=t){
        int cur=0;
        for(int i=0;i<n;++i){
            if(s1[i]==s2[i]&&cur<t){
                res+=s1[i];
                cur++;
            }else{
                for(auto ch:bs){
                    if(ch!=s1[i]&&ch!=s2[i]){
                        res+=ch;break;
                    }
                }
            }
        }
    }else{
        if(c1<2*(t-c0)){
            cout<<"-1\n";
            return 0;
        }
        int cur=0;
        for(int i=0;i<n;++i){
            if(s1[i]==s2[i]){
                res+=s1[i];
            }else{
                if(cur<t-c0){
                    res+=s1[i];
                }else if(cur<2*(t-c0)){
                    res+=s2[i];
                }else{
                    for(auto ch:bs){
                        if(ch!=s1[i]&&ch!=s2[i]){
                            res+=ch;break;
                        }
                    }
                }
                cur++;
            }
        }
    }
    cout<<res<<"\n";
    return 0;
}
