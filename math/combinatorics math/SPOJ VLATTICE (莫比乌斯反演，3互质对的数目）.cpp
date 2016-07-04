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
LL n, m, k, mod;
LL ql, qr, pos;

///基本数学常数求解：
LL prime[Size + 10];///素数
LL primePos[Size + 10];///素数的位置
LL euler[Size + 10];///欧拉函数
LL u[Size + 10];///莫比乌斯函数

void mathInit()///线性筛求质数, 欧拉函数, 莫比乌斯函数 (逆元单独用函数来计算，故不放在此函数中)
///原理：记录每个合数的最小质因子，以此来筛去合数，保证每个合数只被筛一次
{
    euler[1] = 1;
    u[1] = 1; ///u[1] = 1; u[n] = (-1)^k (n = p1p2p3...pk); 其余情况u[n] = 0
    for(LL i=2; i <= Size; ++i)
    {
        if(!prime[i])
        {
            prime[++prime[0]] = i;
            euler[i] = i - 1;///质数的欧拉函数为自己减一///由于此题复杂度卡得非常严，故必需精简初始化线性筛
            u[i] = -1;
            primePos[i] = prime[0];///记录素数的位置
        }
        for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
        {
            prime[i * prime[j]] = 1;///prime[j]为i * prime[j]这个合数的最小质因子
            if(i % prime[j] == 0)
            {
                euler[i * prime[j]] = euler[i] * prime[j];///如果i的分解中p^k中k>=1，即p|i，
                /// 那么由于euler[p^k] = (p-1)*p^(k-1),所以euler[i*p] = euler[i]*p;
                u[i * prime[j]] = 0; ///i * p中存在p的幂大于1
                break;
            }
            else
            {
                euler[i * prime[j]] = euler[i] * (prime[j] - 1);
                /// 反之，即i与p互质，euler[i * p] = euler[i]*euler[p] = euler[i]*(p-1)
                u[i * prime[j]] = -u[i]; /// 根据奇偶性，直接取反
            }
        }
    }
}


///常用函数：

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
///重点！！！！！如果能够改成int且满足题目要求一定要改，速度比LL快两倍
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




///计算素因子：
    //直接计算：
    vector<LL> factors;
    void getFactors(LL n)///利用sqrt(n)范围内的素数表即可求出n的素因子
    {
        factors.clear();
        LL tmp = n;
        for(LL i = 1; i <= prime[0] && prime[i] <= n / prime[i]; ++i)
        {
            if(tmp % prime[i] == 0)
            {
                factors.push_back(prime[i]);
            }
            while(tmp % prime[i] == 0)///由于大于sqrt(n)后还可能有唯一的较大大素因子，因此前面的素因子要除干净
            {
                tmp /= prime[i];
            }
        }
        if(tmp != 1)///最后的结果若不为1，说明还有素因子，要保存
        {
            factors.push_back(tmp);
        }
    }




///题目代码：

LL calPrime(LL n, LL m)///利用莫比乌斯反演计算1~n，1~m之间互质对的个数
{
    LL e = min(n, m);

    ///要求互质对顺序（(x,y),(y,x)视为两组）
    LL ans = 0;
    for(LL i = 1; i <= e; ++i)///暴力计算，复杂度O(n)
    {
        ans += u[i] * (n / i) * (m / i);
    }

    ///不要求互质对顺序（(x,y),(y,x)视为一组）,还要计算重复的ans2/2， 并减去
//    LL ans2 = 0;
//    for(LL i = 1; i <= e; ++i)
//    {
//        ans2 += u[i] * (e / i) * (e / i);
//    }
//    ans2 /= 2;
//    ans = ans - ans2;

    return ans;
}


LL sum[Size];

void init()
{
    sum[0] = 0;
    sum[1] = u[1];
    for(LL i = 2; i < Size; ++i)///计算莫比乌斯函数的分段和，用来进行分段计算
    {
        sum[i] = sum[i - 1] +u[i];
    }

}

LL quickCalPrime(LL n, LL m)
{
    LL e = min(n, m);
    LL last = 0;

    ///要求互质对顺序（(x,y),(y,x)视为两组）
    LL ans = 0;
    for(LL i = 1; i <= e; i = 1 + last)///分段计算，复杂度O(2*(sqrt(n) + sqrt(m)),由于n/i只有sqrt(n)种)
    ///若n/i=t,则t是满足a*i<=n的a的最大值，则n/(n/i)就是满足商为n/i的i的最大值
    ///i为n/2到n/3之间时，n/i值均为2，借助这个想法找到n/i为x的最小i与最大i，它们之间u[i]的和再计算
    {
        last = min(n / (n / i), m / (m / i));
        ans += (sum[last] - sum[i - 1]) * (n / i) * (m / i);
    }

    ///不要求互质对顺序（(x,y),(y,x)视为一组）,还要计算重复的ans2/2， 并减去
//    LL ans2 = 0;
//    for(LL i = 1; i <= e; i = 1 + last)
//    {
//        last = min(n / (n / i), m / (m / i));
//        ans2 += (sum[last] - sum[i - 1]) * (e / i) * (e / i);
//    }
//    ans2 /= 2;
//    ans = ans - ans2;

    return ans;
}

LL quickCalPrime3(LL n, LL m, LL k)///快速分段求在n,m,k范围内的三互质组合的数目
{
    LL e = min(n, min(m, k));
    LL last = 0;

    ///要求互质对顺序（(x,y),(y,x)视为两组）
    LL ans = 0;
    for(LL i = 1; i <= e; i = 1 + last)///分段计算，复杂度O(2*(sqrt(n) + sqrt(m)),由于n/i只有sqrt(n)种)
    ///若n/i=t,则t是满足a*i<=n的a的最大值，则n/(n/i)就是满足商为n/i的i的最大值
    ///i为n/2到n/3之间时，n/i值均为2，借助这个想法找到n/i为x的最小i与最大i，它们之间u[i]的和再计算
    {
        last = min(n / (n / i), min(m / (m / i), k / (k / i)));
        ans += (sum[last] - sum[i - 1]) * (n / i) * (m / i) * (k / i);///原理同二维互质对的推导
    }

    return ans;
}

LL calPrime3(LL n, LL m, LL k)
{
    LL e = min(n, min(m, k));

    LL ans = 0;
    for(LL i = 1; i <= e; i++)
    {
        ans += u[i] * (n / i) * (m / i) * (k / i);
    }

    return ans;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL a, b;
    LL Case=0;
    mathInit();
    init();
    cin>>t;
    while(t--)
//    while(scanf("%I64d%I64d",&n, &m) == 2 && (m + n))
    {
        scanf("%lld",&n);
        LL ans = quickCalPrime3(n, n, n);
        ans += 3 * quickCalPrime(n, n);
//        printf("%lld\n",ans);
//        printf("Case %I64d: ", ++Case);
        printf("%lld\n",ans + 3);

    }
    return 0;
}
