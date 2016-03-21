#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
void ex_gcd(ll a,ll b,ll &d,ll &x,ll &y)
{
    if(!b){
        d=a,x=1,y=0;
    }
    else{
        ex_gcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}

int main()
{
    ll n;
    while(scanf("%I64d",&n)==1)
    {
        int flag=0;
        ll m1,r1,m2,r2;
        scanf("%I64d%I64d",&m1,&r1);
        n--;
        while(n--)
        {
            ll x=0,y=0,d=0,ans;
            scanf("%I64d%I64d",&m2,&r2);
            ll cur=r2-r1;
            if(!flag){
                ex_gcd(m1,m2,d,x,y);
                ll lcm=m1/d*m2;
                if(cur%d){
                    flag=1;
                    continue;
                }
                else{
                x=x*(cur/d)%m2;
                x<0?x+=m2:x;
                x=x*m1+r1;
                x<0?(x%=lcm+lcm):x%=lcm;
                m1=lcm,r1=x;
                }
            }
        }
        if(flag) printf("-1\n");
        else printf("%I64d\n",r1);
    }
    return 0;
}
