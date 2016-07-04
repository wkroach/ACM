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

#define Size 10000005
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
LL totFacNum[Size + 10];///所有质因子的个数
LL difFacNum[Size + 10];///所有互不相同质因子的个数
LL p[Size + 10];///

void mathInit()///线性筛求质数, 欧拉函数, 莫比乌斯函数 (逆元单独用函数来计算，故不放在此函数中)
///原理：记录每个合数的最小质因子，以此来筛去合数，保证每个核数只被筛一次
{
//    memset(prime,0,sizeof(prime));
//    memset(euler,0,sizeof(euler));
    euler[1] = 1;
//    memset(u,0,sizeof(u));
    u[1] = 1; ///u[1] = 1; u[n] = (-1)^k (n = p1p2p3...pk); 其余情况u[n] = 0
    for(LL i=2; i <= Size; ++i)
    {
        if(!prime[i])
        {
            prime[++prime[0]] = i;
//            euler[i] = i - 1;///质数的欧拉函数为自己减一///由于此题复杂度卡得非常严，故必需精简初始化线性筛
            u[i] = -1;
//            primePos[i] = prime[0];///记录素数的位置
            totFacNum[i] = 1;
            difFacNum[i] = 1;
        }
        for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
        {
            prime[i * prime[j]] = 1;///prime[j]为i * prime[j]这个合数的最小质因子
            totFacNum[i * prime[j]] = totFacNum[i] + 1;
            difFacNum[i * prime[j]] = difFacNum[i];///记录所有质因子的数目以及互不相等的质因子数目
            if(i % prime[j] == 0)
            {
//                euler[i * prime[j]] = euler[i] * prime[j];///如果i的分解中p^k中k>=1，即p|i，
                /// 那么由于euler[p^k] = (p-1)*p^(k-1),所以euler[i*p] = euler[i]*p;
                u[i * prime[j]] = 0; ///i * p中存在p的幂大于1
                break;
            }
            else
            {
//                euler[i * prime[j]] = euler[i] * (prime[j] - 1);
                /// 反之，即i与p互质，euler[i * p] = euler[i]*euler[p] = euler[i]*(p-1)
                u[i * prime[j]] = -u[i]; /// 根据奇偶性，直接取反
                difFacNum[i * prime[j]] += 1; ///如果当前质数不是i的质因子，则再加一，表示有新的质因子
            }
        }
    }

    p[1] = 0;
    for(LL i = 2; i <= Size; ++i)///O(n)计算p[i] = sum(u[i / prime]) (prime|i)
    {
        if(totFacNum[i] == difFacNum[i])///如果此数是无平方因子数，则可按因子数推算结果
        {
            p[i] = ((totFacNum[i] - 1) & 1? -1: 1) * totFacNum[i];
        }
        else if(totFacNum[i] - difFacNum[i] == 1)///如果此数是有一个平方因子的数，则只有当prime为平方因子时才有结果
        {
            p[i] = difFacNum[i] & 1? -1: 1;
        }
        else///其余情况根据u的性质均为0
        {
            p[i] = 0;
        }
        p[i] += p[i - 1];///由于要分段优化处理，因此要计算前缀和
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

LL sum[Size];
LL solve(LL n, LL m)///利用莫比乌斯反演计算1~n，1~m之间互质对的个数
{
    LL e = min(n, m);
    LL ans = 0;
    LL last = 1;
    for(LL i = 1; i <= e; i = 1 + last)///分段计算，复杂度O(2*(sqrt(n) + sqrt(m)),由于n/i只有sqrt(n)种)
    ///若n/i=t,则t是满足a*i<=n的a的最大值，则n/(n/i)就是满足商为n/i的i的最大值
    ///i为n/2到n/3之间时，n/i值均为2，借助这个想法找到n/i为x的最小i与最大i，它们之间u[i]的和再计算
    {
        last = min(n / (n / i), m / (m / i));
        ans += (sum[last] - sum[i - 1]) * (n / i) * (m / i);
    }
//    for(LL i = 1; i <= e; ++i)///暴力计算，复杂度O(n)
//    {
//        ans += u[i] * (n / i) * (m / i);
//    }
    LL ans2 = 0;
//    for(LL i = 1; i <= e; ++i)///若不考虑互质对的x，y顺序，则要减去重复的答案
//    {
//        ans2 += u[i] * (e / i) * (e / i);
//    }
    for(LL i = 1; i <= e; i = 1 + last)///同上，将暴力换成了分段计算
    {
        last = min(n / (n / i), m / (m / i));
        ans2 += (sum[last] - sum[i - 1]) * (e / i) * (e / i);
    }
    ans2 /= 2;
    return ans - ans2;
}

LL ans[Size];
LL solvePrime(LL n, LL m)///计算1~n，1~m之间gcd为质数的个数,分段优化版
{
    LL e = min(n, m);
    LL ans = 0;
    LL last;
    for(LL i = 1; i <= e; i = 1 + last)///计算sum(sum((n/(p*i)) * (m/(p*i)) * u[i]) (i < min(n,m))) (p为所有小于n和m的质数)
    {
        last = min(n / (n / i), m / (m / i));
        ans += (p[last] - p[i -1]) * (n / i) * (m / i);///变换公式：sum((n/i) * (m/i) * sum(u[i/p])(p|i)) (i < min(n,m))
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
    sum[1] = u[1];
//    for(LL i = 2; i < Size; ++i)///计算莫比乌斯函数的分段和，用来进行分段计算
//    {
//        sum[i] = sum[i - 1] +u[i];
//    }

    cin>>t;
    while(t--)
//    while(scanf("%I64d%I64d",&n, &m) == 2 && (m + n))
    {
        scanf("%lld%lld",&a, &b);
        LL ans = solvePrime(a, b);
//        printf("%lld\n",ans);
//        printf("Case %I64d: ", ++Case);
        printf("%lld\n",ans);

    }
    return 0;
}
