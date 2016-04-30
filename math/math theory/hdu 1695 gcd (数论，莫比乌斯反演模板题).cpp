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

#define Size 100050
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
#define Max(a,b) (a)>(b)?(a):(b)
using namespace std;
int n,m,k;
int ql,qr,pos;
int prime[Size];
int Euler[100050];
vector<LL> factors[100005];
int u[Size];
//用莫比乌斯反演求[1,n]与[1,m]间gcd为1的无序对数目
//根据莫比乌斯在模上的反演规则2：F(n) = sum(f(d)) (n|d) => f(n) = sum(u(d/n)*F(d)) (n|d) d的取值有范围限制，
//设f(d) 为 gcd(x,y) == d 且 1<=x<=n&&1<=y<=m的(x,y)的对数，F(d) 为 满足 d|gcd(x,y)且1<=x<=n&&1<=y<=m的(x,y)的对数
//在考虑次序的前提下，F(x) == (n/x)*(m/x), 反演后得到f(x) = sum(u(d/x) * F(d)) (x|d)
//所以 当x = 1时，f(1) = for d in range(min(n,m)) : u(d) * (n/d) * (m/d)

void prime_init()///欧拉线性筛,复杂度接近O(n),素数范围取sqrt(n)即可求出所有质因数,同时求出莫比乌斯函数
{
    memset(prime,0,sizeof(prime));
    memset(u,0,sizeof(u));
    u[1] = 1;
    int cnt = 0;
    for(int i=2; i <= Size; ++i)
    {
        if(!prime[i])
        {
            prime[++prime[0]] = i;
            u[i] = -1;
        }
        for(int j = 1; j <= prime[0] && prime[j] <= Size/i; ++j)
        {
            prime[i * prime[j]] = 1;
            if(i % prime[j] == 0)
            {
                u[i * prime[j]] = 0;
                break;
            }
            else
            {
                u[i * prime[j]] = -u[i];
            }
        }
    }
}


int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int a,b,c,d;
    int Case=0;
    prime_init();
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        printf("Case %d: ",++Case);
        n = min(b,d);
        m = max(b,d);
        if(k == 0 || k > n || k > m)
        {
            cout<<0<<endl;
            continue;
        }
        n /= k;
        m /= k;
        LL ans = 0;
        for(int i=1;i<=n;++i)
        {
            ans += (LL)u[i] * (n/i) * (m/i);
        }
        LL ans2 = 0;
        for(int i=1;i<=n;++i)//由于不需要考虑次序， 需要在对(1,n)时去重，即将n和m相等时的gcd为1的对数的一半减掉,以下两种写法都对，一种对结果去重，一种对中间的每一步去重
        {
            ans -= (LL)u[i] * ((LL)(n/i) * (LL)((n/i)-1)/2);
//            ans2 += (LL)u[i] * (n/i) *(n/i);
        }
//        ans -= ans2 / 2;
        printf("%I64d\n",ans);
    }
    return 0;
}

