
 #include <bits/stdc++.h>
using namespace std;
using LL = long long;
int mp[505][505], ans[505][505];
bool dp[505][505];
int n, m;
int main() {
    cin >> n >> m;
     for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= m; j++) {
             cin >> mp[i-1][j-1];
         }
    }
    //输入，不多说
    int res = 0;
   /*思路简析：要求按位与的最大值，就需要保证从矩阵的左上角到右下角的过程中，
  存在二进制中相同的一位都是1，如此按位与之后才能保证最大的值*/
    for (int k = 30; k >= 0; k--) {//从(1<<30)开始找这个 1,贪心的思路
        dp[1][0] = 1;//初始化
       res += (1 << k);//答案肯定是001000101100...这种形式，所以假设先有路径，就先加上
        for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= m; j++) {
                 //重要性质：按位与 & 是严格不增的，故可用这个性质判断
             /*if语句的意思: 如果此时的mp[i][j]和当前答案按位与之后，答案不变，并且该位置的左边或者上面有这个1，说明能够转移*/
               if (((mp[i-1][j-1] & res) == res) && (dp[i - 1][j] || dp[i][j - 1]))
                   dp[i][j] = 1;
              else/*否则不能转移*/
                    dp[i][j] = 0;
            }
        }
         if (!dp[n][m]) res -= (1 << k);//如果不存在这样的连通路径就把它减掉

    }

    cout << res << endl;
    return 0;
 }