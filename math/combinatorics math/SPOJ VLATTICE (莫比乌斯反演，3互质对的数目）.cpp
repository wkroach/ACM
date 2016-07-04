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

///������ѧ������⣺
LL prime[Size + 10];///����
LL primePos[Size + 10];///������λ��
LL euler[Size + 10];///ŷ������
LL u[Size + 10];///Ī����˹����

void mathInit()///����ɸ������, ŷ������, Ī����˹���� (��Ԫ�����ú��������㣬�ʲ����ڴ˺�����)
///ԭ����¼ÿ����������С�����ӣ��Դ���ɸȥ��������֤ÿ������ֻ��ɸһ��
{
    euler[1] = 1;
    u[1] = 1; ///u[1] = 1; u[n] = (-1)^k (n = p1p2p3...pk); �������u[n] = 0
    for(LL i=2; i <= Size; ++i)
    {
        if(!prime[i])
        {
            prime[++prime[0]] = i;
            euler[i] = i - 1;///������ŷ������Ϊ�Լ���һ///���ڴ��⸴�Ӷȿ��÷ǳ��ϣ��ʱ��辫���ʼ������ɸ
            u[i] = -1;
            primePos[i] = prime[0];///��¼������λ��
        }
        for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
        {
            prime[i * prime[j]] = 1;///prime[j]Ϊi * prime[j]�����������С������
            if(i % prime[j] == 0)
            {
                euler[i * prime[j]] = euler[i] * prime[j];///���i�ķֽ���p^k��k>=1����p|i��
                /// ��ô����euler[p^k] = (p-1)*p^(k-1),����euler[i*p] = euler[i]*p;
                u[i * prime[j]] = 0; ///i * p�д���p���ݴ���1
                break;
            }
            else
            {
                euler[i * prime[j]] = euler[i] * (prime[j] - 1);
                /// ��֮����i��p���ʣ�euler[i * p] = euler[i]*euler[p] = euler[i]*(p-1)
                u[i * prime[j]] = -u[i]; /// ������ż�ԣ�ֱ��ȡ��
            }
        }
    }
}


///���ú�����

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
///�ص㣡������������ܹ��ĳ�int��������ĿҪ��һ��Ҫ�ģ��ٶȱ�LL������
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




///���������ӣ�
    //ֱ�Ӽ��㣺
    vector<LL> factors;
    void getFactors(LL n)///����sqrt(n)��Χ�ڵ������������n��������
    {
        factors.clear();
        LL tmp = n;
        for(LL i = 1; i <= prime[0] && prime[i] <= n / prime[i]; ++i)
        {
            if(tmp % prime[i] == 0)
            {
                factors.push_back(prime[i]);
            }
            while(tmp % prime[i] == 0)///���ڴ���sqrt(n)�󻹿�����Ψһ�Ľϴ�������ӣ����ǰ���������Ҫ���ɾ�
            {
                tmp /= prime[i];
            }
        }
        if(tmp != 1)///���Ľ������Ϊ1��˵�����������ӣ�Ҫ����
        {
            factors.push_back(tmp);
        }
    }




///��Ŀ���룺

LL calPrime(LL n, LL m)///����Ī����˹���ݼ���1~n��1~m֮�以�ʶԵĸ���
{
    LL e = min(n, m);

    ///Ҫ���ʶ�˳��(x,y),(y,x)��Ϊ���飩
    LL ans = 0;
    for(LL i = 1; i <= e; ++i)///�������㣬���Ӷ�O(n)
    {
        ans += u[i] * (n / i) * (m / i);
    }

    ///��Ҫ���ʶ�˳��(x,y),(y,x)��Ϊһ�飩,��Ҫ�����ظ���ans2/2�� ����ȥ
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
    for(LL i = 2; i < Size; ++i)///����Ī����˹�����ķֶκͣ��������зֶμ���
    {
        sum[i] = sum[i - 1] +u[i];
    }

}

LL quickCalPrime(LL n, LL m)
{
    LL e = min(n, m);
    LL last = 0;

    ///Ҫ���ʶ�˳��(x,y),(y,x)��Ϊ���飩
    LL ans = 0;
    for(LL i = 1; i <= e; i = 1 + last)///�ֶμ��㣬���Ӷ�O(2*(sqrt(n) + sqrt(m)),����n/iֻ��sqrt(n)��)
    ///��n/i=t,��t������a*i<=n��a�����ֵ����n/(n/i)����������Ϊn/i��i�����ֵ
    ///iΪn/2��n/3֮��ʱ��n/iֵ��Ϊ2����������뷨�ҵ�n/iΪx����Сi�����i������֮��u[i]�ĺ��ټ���
    {
        last = min(n / (n / i), m / (m / i));
        ans += (sum[last] - sum[i - 1]) * (n / i) * (m / i);
    }

    ///��Ҫ���ʶ�˳��(x,y),(y,x)��Ϊһ�飩,��Ҫ�����ظ���ans2/2�� ����ȥ
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

LL quickCalPrime3(LL n, LL m, LL k)///���ٷֶ�����n,m,k��Χ�ڵ���������ϵ���Ŀ
{
    LL e = min(n, min(m, k));
    LL last = 0;

    ///Ҫ���ʶ�˳��(x,y),(y,x)��Ϊ���飩
    LL ans = 0;
    for(LL i = 1; i <= e; i = 1 + last)///�ֶμ��㣬���Ӷ�O(2*(sqrt(n) + sqrt(m)),����n/iֻ��sqrt(n)��)
    ///��n/i=t,��t������a*i<=n��a�����ֵ����n/(n/i)����������Ϊn/i��i�����ֵ
    ///iΪn/2��n/3֮��ʱ��n/iֵ��Ϊ2����������뷨�ҵ�n/iΪx����Сi�����i������֮��u[i]�ĺ��ټ���
    {
        last = min(n / (n / i), min(m / (m / i), k / (k / i)));
        ans += (sum[last] - sum[i - 1]) * (n / i) * (m / i) * (k / i);///ԭ��ͬ��ά���ʶԵ��Ƶ�
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
