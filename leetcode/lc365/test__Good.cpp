#include <bits/stdc++.h>
using namespace std;
const int MOD=0;
#define mod MOD
#define mp make_pair
#define pb push_back
#define SZ 543
int a[SZ];typedef long long ll;

ll qz[SZ];
class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        int n=nums.size();
        ll mx=8e18,mi=-8e18;
        ll ans=1e18;
        unordered_map<ll,ll> lv;
        lv[0]=0;
        for(int i=0;i<n*6;++i) {
            a[i]=nums[i%n],qz[i+1]=qz[i]+a[i];
            if(lv.count(qz[i+1]-target)) {
                ans=min(ans,i-lv[qz[i+1]-target]+1);
            }
            lv[qz[i+1]]=i+1;
        }
        ll tot=qz[n];
        int fu=0;
        //<=2tot?
        ll ut=0;
        if(target>=tot*2) {
            ut=target/tot-2;
            target-=ut*tot;
            ut*=n;
            //have to cross boundary!
            lv.clear();
            for(int i=0;i<n*6;++i) {
                lv[qz[i]]=i;
                if(lv.count(qz[i+1]-target)) {
                    ans=min(ans,i-lv[qz[i+1]-target]+ut+1);
                }
            }
        }
        if(ans>1e9) ans=-1;
        return ans;
    }
};



int main() {
    int n,k;
    cin>>n>>k;
    Solution so;
    vector<int> a(n);
    for(int &x:a){
        cin>>x;
    }
    cout<<so.minSizeSubarray(a,k)<<'\n';
    return 0;
}
