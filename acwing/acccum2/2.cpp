/**
 *    author:  sigma-yyf
 *    created: 02.04.2023 19:00:45       
**/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fst first
#define snd second
#define mp make_pair 
#define sz(C) ((int) (C).size())
#define forn(i, n) for (int i = 0; i < (int) n; ++i)
#define ford(i, n) for (int i = ((int) n) - 1; i >= 0; --i)
#define y1 gftxdtrtfhyjfctrxujkvbhyjice
#define y0 ehfoiuvhefroerferjhfjkehfjke
#define left sdhfsjkshdjkfsdfgkqqweqweh
#define right yytrwtretywretwreytwreytwr
#define next jskdfksdhfjkdsjksdjkgf
#define prev koeuigrihjdkjdfj
#define hash kjfdkljkdhgjdkfhgurehg
#define all(C) begin(C), end(C)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;
typedef vector <ll> vll;
typedef vector <int> vi;
typedef vector <vector <int> > vvi;
typedef vector <pii> vii;
typedef long double ld;
typedef complex<double> cd;
typedef vector<cd> vcd;

#define FILE_NAME ""

const ld EPS = 1e-9;

int w;

bool solve(int m) {
  if  (m == 0) {
    return true;
  }

  int rem = m % w;

  if  (rem == 0) {
    return solve(m / w);
  }

  if  (rem == 1) {
    return solve((m - 1) / w);
  }

  if  (rem == w - 1) {
    return solve((m + w - 1) / w);
  }

  return false;
}

int main() {

  int m;
  cin >> w >> m;
  cout << (solve(m) ? "YES" : "NO") << endl;
  return 0;
}
