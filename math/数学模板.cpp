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

///基本数学常数求解：

LL prime[Size + 10];///素数
LL primePos[Size + 10];///素数的位置
LL euler[Size + 10];///欧拉函数
LL u[Size + 10];///莫比乌斯函数

void mathInit()///线性筛求质数, 欧拉函数, 莫比乌斯函数 (逆元单独用函数来计算，故不放在此函数中)
{
    memset(prime,0,sizeof(prime));
    memset(euler,0,sizeof(euler));
    euler[1] = 1;
    memset(u,0,sizeof(u));
    u[1] = 1; ///u[1] = 1; u[n] = (-1)^k (n = p1p2p3...pk); 其余情况u[n] = 0
    for(LL i=2; i <= Size; ++i)
    {
        if(!prime[i])
        {
            prime[++prime[0]] = i;
            euler[i] = i - 1;///质数的欧拉函数为自己减一
            u[i] = -1;
            primePos[i] = prime[0];///记录素数的位置
        }
        for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
        {
            prime[i * prime[j]] = 1;
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

///乘法逆元：

    ///直接求逆元：
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

    ///筛法求1~Size之间所有逆元
    LL inv[Size];

    LL inverInitPrime(LL mod)///线性筛逆元，在同时筛素数的基础上筛出逆元
    {
        memset(prime,0,sizeof(prime));
        inv[1] = 1 % mod;
        for(LL i=2; i <= Size; ++i)
        {
            if(!prime[i])
            {
                prime[++prime[0]] = i;
                inv[i] = modInverPrime(i, mod);
            }
            for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
            {
                prime[i * prime[j]] = 1;
                inv[i * prime[j]] = inv[i] * inv[prime[j]] % mod;
                if(i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    }

    LL inverInit(LL mod)///已有素数表的情况下线性求逆元
    {
        LL cnt = 0;///cnt表示当前数之前有多少个素数
        inv[1] = 1;
        for(LL i = 2; i <= Size; ++i)
        {
            if(primePos[i])///利用素数的位置判断是否为素数，同时更新cnt
            {
                cnt = primePos[i];
                inv[i] = modInverPrime(i, mod);
            }
            for(LL j = 1; j <= cnt && prime[j] <= Size / i; ++j)
            {
                inv[i * prime[j]] = inv[i] * inv[prime[j]] % mod;
                if(i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    }

    ///最强公式法，线性筛1~mod中所有对mod的逆元，p为奇质数
    LL inverInit_ex(LL mod)
    {
        inv[1] = 1;
        for(LL i = 2; i <= mod; ++i)
        {
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
    }


///组合数取模：

    ///打表法：
    LL facMod[Size + 10][Size];
    LL facInver[Size + 10][Size];

    void facModInit()///包含了阶乘对小于Size的素数取模与阶乘逆元，复杂度O(nlog(n)log(n))
    {
        for(LL i = 1; i <= prime[0]; ++i)
        {
            facMod[i][0] = facInver[i][0] = 1;
            for(LL j = 1; j <= prime[i]; ++j)
            {
                facMod[i][j] = (facMod[i][j - 1] * j) % prime[i];
                facInver[i][j] = modInverPrime(facMod[i][j], prime[i]);
            }
        }
    }

    ///直接求解
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
        return facMod[t][n] * (facInver[t][n-m] * facInver[t][m] % mod) % mod;
    }

    ///lucas定理：
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

    ///质数分解法：
    LL facFactor(LL n, LL p)///求n的阶乘的中因子p的个数，利用计数的思想求，O(log(n))
    {
        LL ans = 0;
        while(n)
        {
            ans += n / p;///每次统计n的范围内p的倍数，即有p^i作为因子的数的个数
            n /= p;///每次缩小n的规模（等价于i++，统计p的更高次幂的倍数）
        }
        return ans;
    }

    LL com_nprime(LL n, LL m, LL mod)///对于mod不是素数时的组合数求模的解法O(n),对于n<1e8有效，因为要打n范围的素数表
    {
        LL ans = 1;
        for(LL i = 1; i <= prime[0] && prime[i] <= n; ++i)
        {
            LL x = facFactor(n, prime[i]);
            LL y = facFactor(n - m, prime[i]);
            LL z = facFactor(m, prime[i]);
            x -= (y + z);
            ans *= quickMod(prime[i], x, mod);
            ans %= mod;
        }
        return ans;
    }

///计算素因子：
    //直接计算：
    vector<LL> factors;
    void getFactors(LL n)///利用sqrt(n)范围内的素数表即可求出n的素因子，O(sqrt(n))
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


///连续和公式：
    /// 1^k + 2^k + 3^k +.....n^k 的和对mod求模公式及函数
    /// 推导见hdu 4059题解cxlove的博客

    LL sumPow2(LL n, LL mod)///计算1^2 + 2^2 + 3^2 +.......n^2 的和对mod求模
    ///公式：n*(n+1)*(2*n+1)/6;
    {
        LL ans = n;
        ans = ans * (n + 1) % mod;
        ans = ans * (2 * n + 1) % mod;
        return ans * modInverPrime(6, mod) % mod;
    }

    LL sumPow3(LL n, LL mod)///计算1^3 + 2^3 + 3^3 +.......n^3 的和对mod求模
    ///公式：n^2*(n+1)^2/4
    {
        LL ans = 1;
        ans = n * n % mod;
        ans = (ans * (n + 1) % mod) * (n + 1) % mod;
        return ans * modInverPrime(4, mod) % mod;
    }

    LL sumPow4(LL n, LL mod)///计算1^4 + 2^4 + 3^4 +.......n^4 的和对mod求模
    ///公式：(n*(n+1)*(2*n+1)*(3*n^2+3*n-1))/30
    {
        LL ans = 1;
        ans = n * (n + 1) % mod;
        ans = ans * (2 * n + 1) % mod;
        ans = ans * (3 * quickMod(n, 2, mod) + 3 * n % mod - 1) % mod;
        return ans * modInverPrime(30, mod) % mod;
    }

///容斥：
    ///求解互质关系
    ///位运算解法：对范围有限制，不能太大，否则位运算会超过LL的范围 O(2^n)
        LL solveRC(LL n)///在计算数m的质因子后计算小于等于n与m互质的数的某些性质，若是两个数之间，则分别计算再相减
        {
            LL ans = 0;
            LL ans2 = 0;
            LL tmp3 = 0;
            for(LL i = 1; i < (1 << factors.size()); ++i)
            {
                LL cnt = 0;
                LL tmp2 = 1;
                for(LL j = 0; j < factors.size(); ++j)
                {
                    LL tmp = 1 << j;
                    if(tmp & i)
                    {
                        cnt++;
                        tmp2 *= factors[j];///统计当前状态下素因子的乘积
                    }
                }
                if(cnt & 1)
                {
                    tmp3 = n / tmp2;///表示n的范围内有多少素数乘积的倍数，即要进行容斥的那些数
                    ans += tmp3;///计算数目
                    ans2 += (tmp3) * (tmp3 + 1) / 2 * tmp2; ///计算和，计算类似属性同理可得（如高次方的和等）
                }
                else
                {
                    tmp3 = n / tmp2;
                    ans -= tmp3;
                    ans2 -= (tmp3) * (tmp3 + 1) / 2 * tmp2; ///计算和
                }
            }
            return n - ans;///ans为与n不互质的数目个数，因此要减去求互质数的个数
            return n * (n + 1) / 2  - ans2;///ans2为与n不互质的数的和，对n个数求和再减去得与之互素的和
        }

    ///dfs解法 （lcm为多个数的最小公倍数），对范围无限制, 且可以适当剪枝，O(2^n)

        LL dfs(LL& ans, LL cur, LL lcm, LL flag)///对当前状态，cur表示当前数的位置，lcm表示从开始到当前数之前的lcm，flag表示取到当前数时的所取数的数目，
        {
            lcm = lcm / gcd(factors[cur], lcm) * arr[cur];///对当前状态递推计算lcm，而不是像位运算那样对所有数重复计算
            if(flag & 1)
            {
                ans += (n - 1) / lcm;///ans的处理同位运算，这里不重复说明
            }
            else
            {
                ans -= (n - 1) / lcm;
            }

            for(LL i = cur + 1; i < m; ++i)///从后一个数开始，分别从每个数开始深搜，表示取这个数，且数目加1
            {
                dfs(ans, i, lcm, flag + 1);
            }
        }

        for(LL i = 0; i < m; ++i)///从每一个数开始深搜，表示取当前这个数，只考虑取数而不考虑不取的状态
        ///dfs比位运算暴力要快，因为位运算暴力对于每一个状态都要统计所取的数并计算lcm，dfs是从前往后顺推，因此不用重复计算lcm
        {
            dfs(ans, i, 1, 1);///初始时lcm，所取数的数目均为1
        }

    ///一般情况：
        ///将factors替换为arr，存放需要容斥求解的问题数据项，按同样步骤求解即可
        ///每次要计算当前多个数的“交”，如lcm，矩形面积交等等，如果dfs中出现交集为空，则可以剪枝
        ///通常奇加，偶减

    ///灵活运用，可以搭配二分，状态压缩，计算几何，记忆化搜索（不会。。。。。。）
