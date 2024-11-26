#include<bits/stdc++.h>
using namespace std;
#define eps 1e-6
const double pi = acos(-1.0);
struct Point{
    double x,y,v;
    Point rotate(double deta){
        return (Point){ x * cos(deta) - y*sin(deta),x*sin(deta) + y * cos(deta)};
    }
}a,b;
double dist(Point a,Point b){
    return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y-b.y));
}
double cross(Point a,Point b,Point c){
    return (b.x - a.x) * (c.y-a.y) - (c.x - a.x) * (b.y - a.y);
}
struct Circle{
    Point o;
    double r;
    //圆心出发的射线的交点
    Point getPoint(double deta){
        return (Point){o.x + cos(deta)*r , o.y + sin(deta)*r};
    }
    //两个圆上的点的最短圆弧
    double getPointDis(Point a,Point b){
        double deta = fabs( atan2(a.y - o.y,a.x - o.x) - atan2(b.y - o.y,b.x - o.x));
        deta = min(deta,2*pi - deta);
        return deta * r;
    }
    //ab线段和圆是否相交
    bool is_insert(Point a,Point b){
        double ab = dist(a,b);
        double d = fabs(cross(o,a,b)) / ab;
        if( d > r - eps) return 0;
        double oa = dist(a,o) , ob = dist(o,b);
        double ta = (oa*oa + ab*ab - ob*ob)/2*oa*ab;
        double tb = (ob*ob + ab*ab - oa*oa)/2*oa*ab;
        if(ta < -eps || tb < -eps) return 0;
        return 1;
    }
}cir;
//求切点
void getTangentPoints(Point p,Circle C , Point& r1,Point& r2){
    double d = dist(p,C.o);
    double base = atan2(p.y - C.o.y,p.x - C.o.x);
    double deta = acos( C.r/d );
    r1 = C.getPoint(base - deta);
    r2 = C.getPoint(base + deta);
}
int sgn(double x){
    if( fabs(x) < eps) return 0;
    if( x > 0) return 1;
    return -1;
}
bool judge(double t){
    double R = sqrt( a.x * a.x + a.y * a.y);
    double w = a.v / R ;
    Point c = a.rotate(w * t);
    if(cir.is_insert(b,c) == 0 ) return dist(b,c) < t*b.v + eps;
    Point cutb1 , cutb2;
    getTangentPoints(b,cir,cutb1,cutb2);
    Point cutc1 , cutc2;
    getTangentPoints(c,cir,cutc1,cutc2);
    double tem1 = dist(b,cutb2) + dist(c,cutc1) + cir.getPointDis(cutb2,cutc1);
    double tem2 = dist(b,cutb1) + dist(c,cutc2) + cir.getPointDis(cutb1,cutc2);
    return min( tem1,tem2 ) < t*b.v + eps;
}
int main(){
    scanf("%lf %lf %lf",&a.x,&a.y,&a.v);
    scanf("%lf %lf %lf %lf",&b.x,&b.y,&b.v,&cir.r);
    cir.o = (Point){0,0};
    double le = 0 , ri = 100000000;
    double res;
    while( ri - le > eps){
        double m = (ri+le)/2;
        if(judge(m)){
            res = m;
            ri = m;
        }
        else le = m;
    }
    printf("%.9f",res);
    return 0;
}