class Solution {
public:
    int minimizeArrayValue(vector<int>& a) {
        int n=a.size();
        vector<long long> s(n+1);
        for (int i = 0; i < n; ++i) {
            s[i+1]=s[i]+a[i];
        }
        long long l=0,r=1e9,c=r;
        while(l<=r){
        	long long mid=(l+r)/2;
        	bool flag=1;
        	for(int i=0;i<n;++i){
        		if(s[i+1]>mid*(i+1)){
                    flag=0;
                }
        	}
            if(flag){
                c=mid;
                l=mid+1;
            }else r=mid-1;
        }
        return c;
    }
};