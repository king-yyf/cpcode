class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        if (k == 1) {
            return 0;
        }
        
        int n = nums.size();
        vector<int> g;
        vector<int> sum = {0};
        int count = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                ++count;
                g.push_back(i - count);
                sum.push_back(sum.back() + g.back());
            }
        }
        
        int m = g.size();
        int ans = INT_MAX;
        for (int i = 0; i + k <= m; ++i) {
            int mid = (i + i + k - 1) / 2;
            int q = g[mid];
            ans = min(ans, (2 * (mid - i) - k + 1) * q + (sum[i + k] - sum[mid + 1]) - (sum[mid] - sum[i]));
        }
        
        return ans;
    }
};

