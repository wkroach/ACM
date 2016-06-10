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

#define Size 10005
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
LL n, m, k, mod;
LL ql, qr, pos;

LL prime[Size+10];
LL primePos[Size+10];

void primeInit()///欧拉素数筛（线性筛），附带标准版的线性筛逆元（注释内）
{
    memset(prime,0,sizeof(prime));
    memset(primePos,0,sizeof(primePos));///记录素数的位置，可用来标记素数，在此题中有用，其他题中不是必须的
//    memset(facInver,0,sizeof(facInver));
    for(LL i=2; i <= Size; ++i)
    {
        if(!prime[i])
        {
            prime[++prime[0]] = i;
            primePos[i] = prime[0];
//            facInver[i] = modInverPrime(i, mod);
        }
        for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
        {
            prime[i * prime[j]] = 1;
//            facInver[i * prime[j]] = facInver[i] * facInver[prime[j]] % mod;
            if(i % prime[j] == 0)
            {
                break;
            }
        }
    }
}

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
///重点！！！！！如果能够改成LL且满足题目要求一定要改，速度比LL快两倍
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

LL facMod[Size + 10][Size];
LL facInver[Size + 10][Size];

void facModInit()///阶乘取模打表，逆元线性筛打表，复杂度O(nlogn)
{
    for(LL i = 1; i <= prime[0]; ++i)///O(logn)
    {
        facMod[i][0] = 1;
        for(LL j = 1; j <= prime[i]; ++j)///O(n)
        {
            facMod[i][j] = (facMod[i][j - 1] * j) % prime[i];
//            facInver[i][j] = modInverPrime(facMod[i][j], prime[i]);///O(logn)
        }

        LL mod = prime[i];
        facInver[i][1] = 1;
        LL cnt = 0;///用于记录当前数之前已有多少素数
        for(LL k=2; k <= mod; ++k)///O(n)，注意这个是在已有素数表的情况下实现，与普通的线性筛不同
        {
            if(primePos[k])///利用素数位置判断k是不是素数
            {
                cnt = primePos[k];///更新cnt
                facInver[i][k] = modInverPrime(k, mod);
            }
            for(LL j = 1; j <= cnt && prime[j] <= mod / k; ++j)///注意j要小于cnt，等同于标准线性筛中j小于prime[0]，表示j要枚举小于k的所有素数
            {
                facInver[i][k * prime[j]] = facInver[i][k] * facInver[i][prime[j]] % mod;///逆元函数f(n)表示n对mod的逆元，是完全积性函数
                if(k % prime[j] == 0)
                {
                    break;
                }
            }
        }
    }
}

LL com(LL n, LL m, LL mod)///组合数取模，直接计算版本，对于n，m 较小时较有效 复杂度O(m)
{
    if(m > n)
        return 0;
    LL ans = 1;
    for(LL i = 1; i <= m; ++i)
    {
        LL a = (n + i -m) % mod;
        LL b = i % mod;
        ans = ans * (a * modInverPrime(b, mod) % mod) % mod; ///mod是素数
//        ans = ans * (a * modInver(b, mod) % mod) % mod; ///mod不是素数
    }
    return ans;
}

LL com_init(LL n, LL m, LL mod)///利用已经打好的表计算版本, n,m要小于mod, 复杂度O(1)
{
    if(m > n)
        return 0;
    LL t = primePos[mod];
    return facMod[t][n] * (facInver[t][facMod[t][n-m]] * facInver[t][facMod[t][m]] % mod) % mod;
}

LL lucas(LL n, LL m,LL mod)///基于lucas定理的组合数取模，对于n，m较大时有效，复杂度O(mod*log(m)), 当mod非常大时无效
{
    if(m == 0)
        return 1;
    return com(n % mod, m % mod, mod) * lucas(n / mod, m / mod, mod) % mod;
}

LL lucas_init(LL n, LL m, LL mod)///利用已经打好的表计算lucas，复杂度O(log(m))
{
    if(m == 0)
        return 1;
    return com_init(n % mod, m % mod, mod) * lucas_init(n / mod, m / mod, mod) % mod;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output2.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
//    cin>>t;
//    while(t--)
    primeInit();
    facModInit();
    while(scanf("%I64d%I64d%I64d",&n,&m,&mod) == 3)
    {
        LL ans = 0;
        if(m > n / 2)
        {
            m  = n - m;
        }
        if(m == 0)
        {
            ans = (n + 1) % mod;
        }
        else
        {
            ans = n - m + lucas_init(n + 1, m, mod);
            ans %= mod;
        }
        printf("Case #%I64d: %I64d\n", ++Case, ans);
    }
    return 0;
}
