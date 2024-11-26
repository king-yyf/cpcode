#include<bits/stdc++.h>
using namespace std;

bool canMove(vector<int> &a, vector<int> &p, int b, int e) {
    int n = a.size();
    vector<array<int, 2>> ranges(n), tmp;
    for (int i = 0; i < n; ++i) {
        ranges[i] = {p[i] - a[i], p[i] + a[i]};
    }
    sort(ranges.begin(), ranges.end(), [&](auto &x, auto &y){
        if (x[0] != y[0]) return x[0] < y[0];
        return x[1] < y[1];
    });
    tmp.push_back(ranges[0]);
    for (int i = 1; i < n; ++i) {
        if (ranges[i][0] <= tmp.back()[1]) 
            tmp.back()[1] = max(tmp.back()[1], ranges[i][1]);
        else
            tmp.push_back(ranges[i]);
    }

    auto get = [&](int x) {
        int l = 0, r = tmp.size() - 1, c = -1;
        if (x < tmp[0][0] || x > tmp[r][1]) return -1;
        while (l <= r) {
            int md = (l + r) / 2;
            if (x >= tmp[md][0] && x <= tmp[md][1]) {
                c = md;
                break;
            } else if (x < tmp[md][0]) r = md - 1;
            else l = md + 1;
        }
        return c;
    };

    int x = get(b), y = get(e);

    return (x != -1 && y != -1 && x == y);
}


int main() {
	vector<int> a{1,4,2},p{10,4,7};
	int b=11,e=1;
	cout<<canMove(a,p,b,e)<<"\n";
}