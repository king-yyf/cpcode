#include<bits/stdc++.h>
using namespace std;

int maxEvenPairs(vector<int> &a) {
	int n = a.size();
	if (n == 1) return 0;

	vector<int> f (n * 2 + 1);
	if ((a[0] + a[1]) % 2 == 0) 
		f[2] = 1;
	for (int i = 3; i <= 2 * n; ++i) {
		
	}
}

int main() {

}