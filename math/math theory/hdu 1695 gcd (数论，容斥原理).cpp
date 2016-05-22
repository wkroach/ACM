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

void prime_init()///����ɸ,���ӶȽӽ�O(n),������Χȡsqrt(n)�����������������
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
void euler()///ŷ��ɸ�����Ӷ�O(nloglogn)
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


void getfactors()///�����1��size��ÿ������������������vector�У�ע�⣡������ÿ������Ҫ���ɾ�����Ȼ�����ǳ���ʱ��©�⣬�Ҳ��ų�������Ǵ������Ŀ����ԣ����ʣ�²�Ϊ1ʱҲҪ����
{
    for(LL j = 2; j <= 100000; ++j)
    {
        LL tmp = j;
        for(int i = 1; i<=prime[0] && prime[i] <= j/prime[i]; ++i)
        {
            if(tmp % prime[i] == 0)
            {
                factors[j].push_back(prime[i]);
                while(tmp % prime[i] == 0)///���ɾ�
                {
                    tmp /= prime[i];
                }
            }
        }
        if(tmp != 1)///��ֹ©��
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

int solve(int n, int m)///�����ݳ�ԭ�������m����nʱ��m��x (1<x<n)���صĸ���
{
    int ans = 0;
//    getfactors(m);
    for(int i = 1; i < (1 << factors[m].size()); ++i)///�ݳ�ԭ��������n��������m���ص����ĸ���= n - 1�����ӱ����ĸ��� + 2�����ӳ˻��ı����ĸ��� - 3������
        ///����λ����������ƽ�ÿ�������ӵ�������ģ��һ�飬i�Ķ�����λ��ʾ��ǰ������Щ������
    {
        int cnt = 0;
        int tmp = 1;
        for(int j = 0; j < factors[m].size(); ++j)///j��ʾ��ǰ��Ӧ����һ��������
        {
            if(i & (1<<j))//ͳ�������ӵ���Ŀ
            {
                cnt++;
                tmp *= factors[m][j];
            }
        }
        if(cnt & 1)//�����ӣ�ż�ؼ����ݳ�ԭ��������㣬������ǲ����ʵ���Ŀ��
        {
            ans += n / tmp;
        }
        else
        {
            ans -= n / tmp;
        }
    }
    return n - ans;//������ʵ���Ŀ;
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
        for(int i=1;i<=n;++i)//����ÿһ��y(y����m��yС��n),���gcd(x,y) == 1����Ŀ����Ҫ��xС��y����ֹ�����ظ�������yС��n�������Ŀ����euler(y)
        {
            ans += Euler[i];
        }
        for(int i=n+1;i<=m;++i)//����m����n�������ݳ�ԭ�����
        {
            ans += (LL)solve(n,i);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

