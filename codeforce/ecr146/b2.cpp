#include<iostream>
#include<unordered_map>
using namespace std;

int main() {
int k;
cin >> k;
int size;
cin >> size;
int arr[size];
for(int i = 0; i < size; i++) {
cin >> arr[i];
}
int curr = 0, res = 0;
unordered_map<int, int> mp;
for(int i = 0; i < size; i++) {
curr += arr[i];
if(curr == k) {
res += 1;
}
if(mp.find(curr - k) != mp.end()) {
res += mp[curr - k];
}
mp[curr]++;
}
cout << res;
return 0;
}