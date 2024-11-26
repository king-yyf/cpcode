#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*



https://www.interviewbit.com/problems/palindromic-binary-representation/
给定整数n，找到第n个二进制表示是回文串的数

n <= 2e4
*/

int Solution::solve(int a) {
	long long p = 1, ans = 0;
	int l = 0, sum = 1;
	while(1) {
	    l++;
	    if(sum + p > a) break;
	    sum += p;
	    l++;
	    if(sum + p > a) break;
	    sum += p;
	    p <<= 1;
	}
	int bits[l]{};
	bits[0] = bits[l - 1] = 1;

	int mid = l >> 1, diff = a - sum; 
	for(int i = 0; diff && i < mid; i++) {
	    bits[mid - i - !(l & 1)] = bits[mid + i] = diff & 1;
	    diff >>= 1;
	}
	p = 1;
	for(int i = 0; i < l; i++) {
	    ans += bits[i] * p;
	    p <<= 1;
	}
	return ans;
}



int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
