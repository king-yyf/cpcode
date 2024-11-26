

long long minOperations(vector<int> &a) {
    int n = a.size();
    long long ans = 0;
    priority_queue<int> q;
    for (int i = 0; i < n; ++i) {
        q.push(a[i]);
        if (q.top() > a[i]) {
            ans += q.top() - a[i];
            q.pop();
            q.push(a[i]);
        }
    } 
    return ans;
}

int minimumMovesToSort(int n, vector<int> &a) {
   auto x1=minOperations(a);
   reverse(a.begin(), a.end());
   auto x2=minOperations(a);
   return min(x1,x2);
}

