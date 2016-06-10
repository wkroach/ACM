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

void primeInit()///ŷ������ɸ������ɸ����������׼�������ɸ��Ԫ��ע���ڣ�
{
    memset(prime,0,sizeof(prime));
    memset(primePos,0,sizeof(primePos));///��¼������λ�ã�����������������ڴ��������ã��������в��Ǳ����
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

LL multi(LL a, LL b, LL mod)//���ٳ˷�ȡģ����ֹ�������������˱�LL, �ٶȱ�ԭ���˷�Ҫ��
{
    LL ans = 0;
    a %= mod;
    while(b)//ԭ������������ƣ���һ����װ��Ϊ�����ƣ���λ��������
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

LL quickMod(LL a, LL b, LL mod)//���ڿ��ٳ˷�ȡģ�Ŀ�����ȡģ
///�ص㣡������������ܹ��ĳ�LL��������ĿҪ��һ��Ҫ�ģ��ٶȱ�LL������
{
    if(b == 0)
        return 1%mod;
    LL c = a%mod;
    LL ans = 1;
    while(b)
    {
        if(b&1)
        {
//            ans = multi(ans,c,mod);//������ĿҪ��ѡ��˷���ʽ
            ans = ans * c % mod;
        }
//        c = multi(c,c,mod);
        c = c * c % mod;
        b >>= 1;
    }
    return ans;
}

LL exGcd(LL a, LL b, LL &x, LL &y)///��չŷ����ã�����a b��gcd��x��y�ֱ�Ϊa b��ϵ��
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

LL modInverPrime(LL a, LL mod)///�˷���Ԫ �����ݷ�������mod������ʱ��Ч
{
    return quickMod(a,mod-2,mod);
}

LL modInver(LL a, LL mod)///�˷���Ԫ ��չŷ����÷�������mod������������a ����ʹ��Ч
{
    LL x,y,g;
    LL gcd = exGcd(a,mod,x,y);
    if(gcd == 1)
        return (x%mod+mod)%mod;
    return -1;
}

LL facMod[Size + 10][Size];
LL facInver[Size + 10][Size];

void facModInit()///�׳�ȡģ�����Ԫ����ɸ������Ӷ�O(nlogn)
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
        LL cnt = 0;///���ڼ�¼��ǰ��֮ǰ���ж�������
        for(LL k=2; k <= mod; ++k)///O(n)��ע�������������������������ʵ�֣�����ͨ������ɸ��ͬ
        {
            if(primePos[k])///��������λ���ж�k�ǲ�������
            {
                cnt = primePos[k];///����cnt
                facInver[i][k] = modInverPrime(k, mod);
            }
            for(LL j = 1; j <= cnt && prime[j] <= mod / k; ++j)///ע��jҪС��cnt����ͬ�ڱ�׼����ɸ��jС��prime[0]����ʾjҪö��С��k����������
            {
                facInver[i][k * prime[j]] = facInver[i][k] * facInver[i][prime[j]] % mod;///��Ԫ����f(n)��ʾn��mod����Ԫ������ȫ���Ժ���
                if(k % prime[j] == 0)
                {
                    break;
                }
            }
        }
    }
}

LL com(LL n, LL m, LL mod)///�����ȡģ��ֱ�Ӽ���汾������n��m ��Сʱ����Ч ���Ӷ�O(m)
{
    if(m > n)
        return 0;
    LL ans = 1;
    for(LL i = 1; i <= m; ++i)
    {
        LL a = (n + i -m) % mod;
        LL b = i % mod;
        ans = ans * (a * modInverPrime(b, mod) % mod) % mod; ///mod������
//        ans = ans * (a * modInver(b, mod) % mod) % mod; ///mod��������
    }
    return ans;
}

LL com_init(LL n, LL m, LL mod)///�����Ѿ���õı����汾, n,mҪС��mod, ���Ӷ�O(1)
{
    if(m > n)
        return 0;
    LL t = primePos[mod];
    return facMod[t][n] * (facInver[t][facMod[t][n-m]] * facInver[t][facMod[t][m]] % mod) % mod;
}

LL lucas(LL n, LL m,LL mod)///����lucas����������ȡģ������n��m�ϴ�ʱ��Ч�����Ӷ�O(mod*log(m)), ��mod�ǳ���ʱ��Ч
{
    if(m == 0)
        return 1;
    return com(n % mod, m % mod, mod) * lucas(n / mod, m / mod, mod) % mod;
}

LL lucas_init(LL n, LL m, LL mod)///�����Ѿ���õı����lucas�����Ӷ�O(log(m))
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
