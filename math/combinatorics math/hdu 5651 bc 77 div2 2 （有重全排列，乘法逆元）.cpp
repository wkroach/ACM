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
int ql,qr,pos;
int vis[30];

LL fac(LL x)
{
    LL tmp = 1;
    for(LL i = 1; i<=x ; ++i)
    {
        tmp = (tmp%Mod)*(i%Mod)%Mod;
        tmp %= Mod;
    }
    return tmp;
}

LL quick(LL x, LL p)
{
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


int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int Case=0;
    string s;
    cin>>t;
    while(t--)
//    while(scanf("%d",&t)&&t)
    {
        memset(vis,0,sizeof(vis));
        cin>>s;
        for(int i=0; i<s.length();++i)
        {
            vis[s[i]-'a']++;
        }
        LL len = (LL)s.length();
        int flag=0;
        int tmp=-1;
        for(int i=0;i<30;++i)///对字符串的一半，先判断能否成为回文，在对一半求重复全排列数，注意除法取模要用逆元
        {
            if(vis[i])
            {
                if(vis[i]%2)
                {
                    flag++;
                    tmp = i;
                }
            }
        }
        if(flag>1)
        {
            cout<<0<<endl;
            continue;
        }
        else
        {
            if(len == 1)
            {
                cout<<1<<endl;
                continue;
            }
            LL tmp2 = 1;
            LL ans = fac(len/2);
            for(int i=0;i<30;++i)
            {
                if(vis[i])
                {
                    tmp2 = (tmp2%Mod)*(fac(((LL)vis[i])/2));
                    tmp2 %= Mod;
                }
            }
            LL tmp3 = mod_inverse(tmp2, (LL)Mod);
//            LL tmp3 = quick(tmp2,Mod-2);
            ans = ans * tmp3 % Mod;
            cout<<ans<<endl;
        }
    }
    return 0;
}

