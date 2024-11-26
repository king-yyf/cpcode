class Solution {
public:
    long long minOperations(vector<int>& c, vector<int>& b, int k) {
        int n=c.size();
        long long s=0;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            a[i]=c[i]-0ll-b[i];    
            s+=a[i];
        }
        if(s!=0) return -1;
        if(k==0) {
            if(c==b) return 0;
            return -1;
        }
        bool o=1;
        sort(a.begin(), a.end());
        long long d=0;
        for (int i = 0; i < n; ++i) {
            if(a[i]%k!=0) {
                o=0;
                break;
            } else{
                d+=abs(a[i]) /k;
            }
        }
        if(!o) return -1;
        return d/2;
    }
};