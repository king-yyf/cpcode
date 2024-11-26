class Solution {
public:
    map<TreeNode*, vector<int>> dp;
    vector<int> dfs(TreeNode* r){
        if(!r) return {0,0,0,0};

        vector<int> a(4);
        vector<int> u,v;

        if(!r->left) u={0,0,0,0};
        else u= dfs(r->left);

        if(!r->right) v={0,0,0,0};
        else v= dfs(r->right);

       if(r->val==1){
            a[0]=min({1+u[0]+v[0],1+u[1]+v[1],1+u[2]+v[2]});
            a[1]=min({u[1]+v[1],2+u[0]+v[0],2+u[3]+v[3]});
            a[2]=min({u[0]+v[0],2+u[1]+v[1],2+u[2]+v[2]});
            a[3]=min({1+u[1]+v[1],1+u[0]+v[0],1+u[3]+v[3]});
        }else{
            a[0]=min({u[0]+v[0],2+u[1]+v[1],2+u[2]+v[2]});
            a[1]=min({1+u[1]+v[1],1+u[0]+v[0],1+u[3]+v[3]});
            a[2]=min({1+u[0]+v[0],1+u[1]+v[1],1+u[2]+v[2]});
            a[3]=min({u[1]+v[1],2+u[0]+v[0],2+u[3]+v[3]});
        }
        dp[r]=a;
        return a;

    }
    int closeLampInTree(TreeNode* root) {
        if(!root) return 0;
        dp.clear();

        dfs(root);

        return dp[root][0];

    }
};
