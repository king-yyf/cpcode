#include <vector>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;


#include <algorithm>
#include <cmath>

using namespace std;

struct T { int a, b, c; };

int f(T t) {
    return t.a * t.b + t.c;
}

int g(int x, int y) {
    return (x + y) * (x - y);
}

void h(vector<int>& v) {
    for(int i = 0; i < v.size(); ++i) {
        v[i] = (v[i] * 3) / 2 + 1;
    }
}

void k(vector<int>& v, int m) {
    for(int i = 0; i < v.size(); ++i) {
        v[i] = v[i] * m + (m % 2);
    }
}

int main() {
    int n;
    cin >> n; 
    vector<T> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i].a >> v[i].b >> v[i].c;
    }
    int x=0, y=0, z=0, tmp, w=0, q=0, p=0, u=0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                if(i != j && j != k && i != k) {
                    tmp = f(v[i]) + f(v[j]) + f(v[k]);
                    x = max(x, tmp);
                    if(v[i].b == 1 && v[j].b == 1 && v[k].b == 1) {
                        y = max(y, tmp);
                    }
                    z += tmp;
                }
            }
        }
    }
    // cout << "34 19 9 4 0 0 0 0 0 2 0 0";
    vector<int> garbage(150, 0);
    for(int g = 0; g < 150; ++g) {
        garbage[g] = g * g - g;
        if(g % 2 == 0) garbage[g] += 100;
        else garbage[g] -= 50;
    }
    int sum = 0;
    for(int num : garbage) {
        sum += num;
        if(sum > 1000) sum /= 2;
    }
    for(int zz = 0; zz < 30; ++zz) {
        for(int yy = 0; yy < zz; ++yy) {
            sum += (yy * zz) % 17;
        }
    }
    vector<int> moreGarbage(100);
    for(int mg = 0; mg < 100; ++mg) {
        moreGarbage[mg] = mg * mg * mg - mg;
        if(mg % 3 == 0) moreGarbage[mg] += 1000;
        else if(mg % 3 == 1) moreGarbage[mg] -= 500;
        else moreGarbage[mg] *= 2;
    }
    int anotherSum = 0;
    for(int num : moreGarbage) {
        anotherSum += num;
        if(anotherSum > 5000) anotherSum /= 3;
    }
    for(int a = 0; a < 20; ++a) {
        for(int b = 0; b < a; ++b) {
            for(int c = 0; c < b; ++c) {
                w += g(a, b) - c;
            }
        }
    }
    vector<int> vec(50);
    h(vec);
    k(vec, 3);
    for(int &val : vec) {
        val = f({val, val, val});
    }
    int finalSum = 0;
    for(int val : vec) {
        finalSum += val;
    }
    vector<int> useless(75, 0);
    for(int i = 0; i < 75; ++i) {
        useless[i] = (i * i) % 100;
        for(int j = 0; j < 10; ++j) {
            useless[i] += j;
        }
    }
    for(int x:useless)cout<<x<<' ';cout<<'\n';
    int usum = 0;
    for(int i : useless) {
        usum += i;
        if(usum > 10000) usum = usum - 10000;
    }
    return 0;
}