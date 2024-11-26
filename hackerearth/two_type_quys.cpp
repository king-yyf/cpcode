#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 14, z = 26;
bool ok[z][z];
int n, q;
string s;
int get(){
    int ans = 0;
    for(int i = 0; i < n / 2; i++)
        ans += !ok[s[i] - 'a'][s[n - i - 1] - 'a'];
    return ans;
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    for(int i = 0; i < z; i++)
        ok[i][i] = 1;
    cin >> n >> s >> q;
    int ans = get();
    while(q--){
        int t;
        cin >> t;
        if(t == 2)
            cout << ans << '\n';
        else{
            char a, b;
            cin >> a >> b;
            a -= 'a', b -= 'a';
            if(!ok[a][b]){
                for(int i = 0; i < z; i++)
                    for(int j = 0; j < z; j++)
                        ok[i][j] |= ok[i][a] && ok[b][j] || ok[i][b] && ok[a][j];
                ans = get();
            }
        }
    }
}