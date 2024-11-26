#include <cstdio>
#include <algorithm>
#include<cmath>

using namespace std;
int n;
double a[12];
int main() {
    int n,t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;++tt) {
    	// while(scanf("%d",&n)&&n){
        scanf("%d",&n);
    	for(int i=0;i<n;i++)  scanf("%lf",&a[i]); 
        // sort(a,a+n);
        double  X=(a[0]+a[n-1])/2.0, Y=1.0;
        for(int i=0;i<n-1;i++) Y+=sqrt(4-(a[i+1]-a[i])*(a[i+1]-a[i])/4.0);
        
        printf("%d: ",tt);
        printf("%.4lf %.4lf\n",X,Y);
    }
    return 0;
}


