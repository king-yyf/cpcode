#include <iostream>
using namespace std;

int main() {
  int t; cin >> t;
  while (t--) {
    string x; cin >> x;
    int i = 0;
    while (x[i] < '5' && i < x.length()) {
      i++;
    }
    if (i == x.length()) {
      cout << x << endl;
    }
    else {
      for (int j = i + 1; j < x.length(); j++) {
        x[j] = '0';
      }
      for (int j = i; j > 0; j--) {
        if (x[j] >= '5') {
          x[j - 1] += 1;
          x[j] = '0';
        }
      }
      if (x[0] >= '5') {
        cout << 10;
      }
      else cout << x[0];
      for (int i = 1; i < x.length(); i++) cout << x[i];
      cout << endl;
    }
  }
  return 0;
}