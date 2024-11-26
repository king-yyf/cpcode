#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long int li;

int main() {
 int t;
 cin>>t;
 
 while(t--){
     
     int n, k;
     cin>>n>>k;
     
      vector<li> l(n), r(n);
      
      for(int i = 0; i < n; i++)cin>>l[i];
      for(int i = 0; i < n; i++)cin>>r[i];
      
      vector<pair<li, li> > old_seg(n);
      
      for(int i = 0; i < n; i++){
          old_seg[i] = {l[i], r[i]};
      }
      
    //  sort(old_seg.begin(), old_seg.end());
      
      li prev_l = old_seg[0].first, prev_r = old_seg[0].second;
      
      vector<pair<li, li> > seg;
      bool added = false;
      
    
    li ans = 0, count_for_one = 0, ans_for_one = 0, ans_without_one = 0, count_without_one = 0;
    
    li curr_pos = 0;
    for(auto p : old_seg){
        
        
        if(p.second - p.first == 0){
            ans_for_one += 3;
            count_for_one++;
            curr_pos = p.second;
            ans_without_one += 1;
            continue;
        }
        
        ans_for_one += p.first - 1 - curr_pos;
        ans_without_one += p.first - 1 - curr_pos;
        curr_pos = p.first;
        
        count_for_one += max(min(k - count_for_one, p.second - p.first + 1), min(k - count_without_one, p.second - p.first + 1));
        count_without_one += max(min(k - count_without_one, p.second - p.first + 1), min(k - count_for_one, p.second - p.first + 1));
        ans_for_one += max(min(k - count_for_one, p.second - p.first + 1), min(k - count_without_one, p.second - p.first + 1));
        ans_without_one +=  max(min(k - count_without_one, p.second - p.first + 1), min(k - count_for_one, p.second - p.first + 1));
        ans_for_one += 2;
        ans_without_one += 2;
        curr_pos = p.second;
        
        if(count_for_one >= k || count_without_one >= k) break;
    }
    
    
    // cout<<<<" "<<count_without_one<<" ";
    if(count_for_one < k && count_without_one < k) {
        cout<<-1<<"\n";
        continue;
    }
    
    cout<<count_for_one+count_without_one<<"\n";
 }
 return 0;
}