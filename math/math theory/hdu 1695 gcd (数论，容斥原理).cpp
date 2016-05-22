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
#define Max(a,b) (a)>(b)?(a):(b)
using namespace std;
int n,m,k;
int ql,qr,pos;

vector<LL> factors[100005];

int prime[Size];

void prime_init()///线性筛,复杂度接近O(n),素数范围取sqrt(n)即可求出所有质因数
{
    memset(prime,0,sizeof(prime));
    int cnt = 0;
    for(int i=2; i < Size; ++i)
    {
        if(!prime[i])
            prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0] && prime[j] <= Size/i; ++j)
        {
            prime[i * prime[j]] = 1;
            if(i % prime[j] == 0)
                break;
        }
    }
}

int Euler[100050];
void euler()///欧拉筛，复杂度O(nloglogn)
{
    memset(Euler,0,sizeof(Euler));
    Euler[1] = 1;
    for(int i = 2; i <= 100010; ++i)
    {
        if(!Euler[i])
        {
            for(int j = i; j <= 100010; j += i)
            {
                if(!Euler[j])
                    Euler[j] = j;
                Euler[j] = Euler[j] / i *(i-1);
            }
        }
    }
}


void getfactors()///打表，将1到size的每个数的质因数保存在vector中，注意！！！！每个因数要除干净，不然当数非常大时会漏解，且不排除本身就是大素数的可能性，最后剩下不为1时也要保留
{
    for(LL j = 2; j <= 100000; ++j)
    {
        LL tmp = j;
        for(int i = 1; i<=prime[0] && prime[i] <= j/prime[i]; ++i)
        {
            if(tmp % prime[i] == 0)
            {
                factors[j].push_back(prime[i]);
                while(tmp % prime[i] == 0)///除干净
                {
                    tmp /= prime[i];
                }
            }
        }
        if(tmp != 1)///防止漏解
        {
            factors[j].push_back(tmp);
        }
    }
}

//void getfactors(int n)
//{
//    if(factors[n].size() != 0)
//        return;
//    int tmp = n;
//    for(int i = 1; i <= prime[0] && prime[i] <= n/prime[i]; ++i)
//    {
//        if(tmp % prime[i] == 0)
//        {
//            factors[n].push_back(prime[i]);
//            while(tmp % prime[i] == 0)
//            {
//                tmp /= prime[i];
//            }
//        }
//    }
//    if(tmp != 1)
//    {
//        factors[n].push_back(tmp);
//    }
////    for(int i=0;i<factors[n].size();++i)
////        cout<<factors[n][i]<<endl;
//}

int solve(int n, int m)///利用容斥原理求出当m大于n时，m与x (1<x<n)互素的个数
{
    int ans = 0;
//    getfactors(m);
    for(int i = 1; i < (1 << factors[m].size()); ++i)///容斥原理，数集合n中所有与m互素的数的个数= n - 1个因子倍数的个数 + 2个因子乘积的倍数的个数 - 3个……
        ///利用位运算与二进制将每个素因子的组合情况模拟一遍，i的二进制位表示当前用了哪些素因子
    {
        int cnt = 0;
        int tmp = 1;
        for(int j = 0; j < factors[m].size(); ++j)///j表示当前对应的哪一个素因子
        {
            if(i & (1<<j))//统计素因子的数目
            {
                cnt++;
                tmp *= factors[m][j];
            }
        }
        if(cnt & 1)//奇数加，偶素减（容斥原理的逆运算，算出的是不互质的数目）
        {
            ans += n / tmp;
        }
        else
        {
            ans -= n / tmp;
        }
    }
    return n - ans;//求出互质的数目;
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
//    getPrime();
//    for(int i=0;i<=prime[0];++i)
//        cout<<prime[i]<<endl;
    getfactors();
//    cout<<1;
    euler();
//    for(int i=100;i<2000;++i)
//    {
//        for(int j=0;j<factors[i].size();++j)
//            cout<<factors[i][j]<<" ";
//        cout<<endl;
//    }
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
        for(int i=1;i<=n;++i)//对于每一个y(y属于m且y小于n),求出gcd(x,y) == 1的数目，且要求x小于y，防止出现重复，由于y小于n，这个数目即是euler(y)
        {
            ans += Euler[i];
        }
        for(int i=n+1;i<=m;++i)//对于m大于n，利用容斥原理求解
        {
            ans += (LL)solve(n,i);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

