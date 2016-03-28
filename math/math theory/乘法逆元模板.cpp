#include<cstdio>
#include<cstdlib>
#include<time.h>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<stack>
#include<vector>
#include<algorithm>

//#include<bits/c++std.h>

#define Size 1000005
#define inf 2e9
#define INF 2e18
#define LL long long int
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
using namespace std;
LL n,m,k;

LL quick(LL x, LL p)///费马小定理+快速幂，p为Mod-2时为x模Mod的乘法逆元, 前提是Mod是素数
{
    if(p==0)
        return 1;
    if(p==1)
        return x;
    LL tmp = p;
    LL ans = 1;
    while(tmp)
    {
        if(tmp&1)
        {
            ans = ans*x%Mod;
        }
        tmp>>=1;
        x = (x%Mod)*(x%Mod)%Mod;
    }
    return ans%Mod;
}


LL ex_gcd(LL a, LL b, LL &x, LL &y)///利用扩展欧几里得求逆元，不要求模为素数
{
    if(a==0&&b==0) return -1;
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    else
    {
       LL tmp = ex_gcd(b,a%b,y,x);
       y-=x*(a/b);
       return tmp;
    }
}

LL mod_inverse(LL a,LL mod)
{
    LL x,y,g;
    LL gcd = ex_gcd(a,mod,x,y);
    if(gcd == 1) return (x%mod+mod)%mod;
    return -1;
}
