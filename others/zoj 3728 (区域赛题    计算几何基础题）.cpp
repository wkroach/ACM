
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
//#define LL long long
#define MOD 1000000007
#define N 10005
double Rm,R,r,x,y,vx,vy,k,s,c,v,l1;
double t;
int judge1(double x,double y)
{
    if(k==1000000) l1=fabs(x);
    else if(k==0.000001) l1=fabs(y);
    else
        l1=fabs(y-k*x)*s;
    if(l1>=R+r) return 0;
    if((l1<R+r)&&(l1>=Rm+r)) return 1;
    if(l1<Rm+r) return -1;
}
int judge2(double x,double y)
{
    if(x*vx+y*vy>=0) return 0;
    return 1;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%lf%lf%lf%lf%lf%lf%lf",&Rm,&R,&r,&x,&y,&vx,&vy)==7)
    {
        t=0;
        if(vx==0)
            k=1000000;
        else if(vy==0)
            k=0.000001;
        else k=vy/vx;
        if(vx==0) s=0,c=1;
        else if(vy==0) s=1,c=0;
        else s=1/sqrt(1+k*k),c=1/sqrt(1+1/(k*k));
        v=sqrt(vx*vx+vy*vy);
        int ju1=judge1(x,y);
        int ju2=judge2(x,y);
        double l2=sqrt((R+r)*(R+r)-l1*l1);
        if(ju1==0||ju2==0) {printf("0.000\n");continue;}
        if(ju1==1)
        {
            double L=sqrt((R+r)*(R+r)-l1*l1)*2;
            t=L/v;
            printf("%.3lf\n",t);
            continue;
        }
        if(ju1==-1)
        {
            double L=sqrt((Rm+r)*(Rm+r)-l1*l1);
            double L2=l2-L;
            t=2*L2/v;
            printf("%.3lf\n",t);
            continue;
        }
    }
    return 0;
}

