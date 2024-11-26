#include<bits/stdc++.h>
using namespace std;

int minSwaps(vector<int> &a) {
    priority_queue<int, vector<int>, greater<int>> q;
    long long s = 0;
    int ans = 0;
    for (auto & x : a) {
        s += x;
        if (x < 0) q.push(x);
        if (s < 0) {
            s -= q.top();
            q.pop();
            ans ++;
        } 
    }
    return ans;
}

int main() {
	vector<int> a{5,-2,-3,1,-1};
	cout<<minSwaps(a)<<"\n";
}