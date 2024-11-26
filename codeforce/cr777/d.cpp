#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int T,x,d;
bool isprime(int A){
    int flag=1;
    for(int t=2;t*t<=A;t++){
        if(A%t==0){
            flag=0;
            break;
        }
    }
    if(flag)return true;
    return false;
}


int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&x,&d);
        if(isprime(d)){
            int cnt=0;
            while(x%d==0){
                x/=d;
                cnt++;
            }
            if(cnt==1||isprime(x))puts("NO");
            else puts("YES");
        }
        else{
            int cnt=0;
            while(x%d==0){
                x/=d;
                cnt++;
            }
            if(cnt==1)puts("NO");
            else if(cnt==2){
                if(isprime(x))puts("NO");
                else puts("YES");
            }
            else{
                if(!isprime(x))puts("YES");
                else{
                    if(cnt>=4)puts("YES");
                    else{
                        if(1ll*d==1ll*x*x)puts("NO");
                        else puts("YES");
                    }
                }
            }
        }
    }

}
