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

LL com(LL n, LL m, LL mod)///�����ȡģ������n��m ��Сʱ����Ч ���Ӷ�O(m)
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

LL lucas(LL n, LL m,LL mod)///����lucas����������ȡģ������n��m�ϴ�ʱ��Ч�����Ӷ�O(mod*log(m)), ��mod�ǳ���ʱ��Ч
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
