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

#define Size 100005
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
LL ql,qr,pos;


LL gcd(LL a,LL b)//gcd
{
    return b == 0?a:gcd(b,a%b);
}

LL multi(LL a, LL b, LL mod)//快速乘法取模，防止两个过大的数相乘爆LL, 速度比原生乘法要慢
{
    LL ans = 0;
    a %= mod;
    while(b)//原理与快速幂类似，将一个数装换为二进制，按位相乘再求和
    {
        if(b&1)
        {
            ans = (ans + a) % mod;
        }
        b >>= 1;
        a = (a + a) % mod;
    }
    return ans;
}

LL quickMod(LL a, LL b, LL mod)//基于快速乘法取模的快速幂取模
{
    if(b == 0)
        return 1%mod;
    LL c = a%mod;
    LL ans = 1;
    while(b)
    {
        if(b&1)
        {
//            ans = multi(ans,c,mod);//根据题目要求选择乘法方式
            ans = ans * c % mod;
        }
//        c = multi(c,c,mod);
        c = c * c % mod;
        b >>= 1;
    }
    return ans;
}

LL exGcd(LL a, LL b, LL &x, LL &y)///扩展欧几里得，返回a b的gcd，x，y分别为a b的系数
{
    if(a==0&&b==0) return -1;
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    else
    {
       LL tmp = exGcd(b,a%b,y,x);
       y-=x*(a/b);
       return tmp;
    }
}

LL modInverPrime(LL a, LL mod)///乘法逆元 快速幂法，对于mod是质数时有效
{
    return quickMod(a,mod-2,mod);
}

LL modInver(LL a, LL mod)///乘法逆元 扩展欧几里得法，对于mod不是质数但与a 互质使有效
{
    LL x,y,g;
    LL gcd = exGcd(a,mod,x,y);
    if(gcd == 1)
        return (x%mod+mod)%mod;
    return -1;
}

LL com(LL n, LL m, LL mod)///组合数取模，对于n，m 较小时较有效 复杂度O(m)
{
    if(m > n)
        return 0;
    LL ans = 1;
    for(LL i = 1; i <= m; ++i)
    {
        LL a = (n + i -m) % mod;
        LL b = i % mod;
        ans = ans * (a * modInverPrime(b, mod) % mod) % mod;
//        ans = ans * (a * modInver(b, mod) % mod) % mod;
    }
    return ans;
}

LL lucas(LL n, LL m,LL mod)///基于lucas定理的组合数取模，对于n，m较大时有效，复杂度O(mod*log(m)), 当mod非常大时无效
{
    if(m == 0)
        return 1;
    return com(n % mod, m % mod, mod) * lucas(n / mod, m / mod, mod) % mod;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
    LL mod;
//    cin>>t;
//    while(t--)
    while(scanf("%lld%lld%lld",&n,&m,&mod)==3)
    {
        printf("%lld\n",lucas(n - m + 1,m,mod));
    }
    return 0;
}
