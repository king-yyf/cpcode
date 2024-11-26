#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int n=s.size(),mx=0,cnt=1;
	stack<int> sk;
	for (int i = 0; i < n; ++i) {
	    if (sk.size() && s[i] == ')' && s[sk.top()] == '(') {
	    	sk.pop();
	    } else sk.push(i);
	    int r = sk.size() ? i-sk.top() : i+1;
	    if(r > mx) mx = r, cnt=1;
	    else if(r==mx&&r) cnt++;
	}
	cout<<mx<<" "<<cnt<<"\n";
}
