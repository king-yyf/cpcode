#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize(2)

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {

        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x;
}

void write(long long x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

int n,x;
void solve(){
	n=read();
	long long s=0;
	while(n--){
		x=read();s+=x;
	}
	write(s);
}
int main(){
	
	solve();
	return 0;
}
