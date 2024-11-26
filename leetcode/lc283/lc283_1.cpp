#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k,x,ans=0;
    scanf("%d%d",&n,&k);
    map<string,int> mp;
    for(int i=0;i<n;++i){
        vector<int> v;
        for(int j=0;j<k;++j){
            scanf("%d",&x);
            v.push_back(x);
        }
        string s;
        for(int j=1;j<v.size();++j){
            s+=to_string(v[j]-v[j-1])+'#';
        }
        ans+=mp[s];
        mp[s]++;
    }
    printf("%d\n",ans);
}