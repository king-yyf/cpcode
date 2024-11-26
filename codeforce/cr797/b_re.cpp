#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <math.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        int l, b;
        cin >> l;
        cin >> b;
        bool arr[l];
        int count = 0;
        for(int j = 0; j < l; j++){
            char c;
            cin >> c;
            arr[j] = (c == 'B');
            if(j < b) count += int(arr[j]);
        }
        int m = b - count;
        for(int j = 1; j <= l - b; j++){
            count -= int(arr[j-1]);
            count += int(arr[j+b-1]);
            m = min(m, b - count);
        }
        cout << m << endl;
    }

    return 0;
}