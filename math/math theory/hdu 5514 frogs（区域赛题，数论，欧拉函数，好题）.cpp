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
vector<int> frogs;

int gcd (int a,int b)
{
    return b == 0? a: gcd(b,a%b);
}

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

LL getEuler (LL n)
{
    LL ans = n;
    for(LL i = 2; i * i <= n; ++i)
    {
        if( !(n%i) )
        {
            while( !(n % i))
                n /= i;
            ans = ans / i * (i-1);
        }

    }
    if(n > 1)
        ans = ans / n * (n-1);
    return ans;
}

bool good(int x)
{
    for(int i=0;i<frogs.size();++i)
    {
        if(x % frogs[i] == 0)
            return true;
    }
    return false;
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
//    prime_init();
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        frogs.clear();
        scanf("%d%d",&n,&m);
        int frog;
        LL ans = 0;
        int fac;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&frog);
            frogs.push_back(gcd(frog,m)); //重点3：frog可以走到的石头，必定是以gcd(frog,m)为步长的石头，即这个石头的编号a%gcd(frog,m) == 0, 又m % gcd(frog,m) == 0, 因此gcd(a,m) % gcd(frog,m) == 0
        }
        for(int i=1; i * i <= m; ++i)//因此，只需枚举m所有的约数的以此数为gcd的集合中（这是个等价划分，因为任意两数的最大公约数唯一），判断当前约数是否被frog踩到，并由一下定理计算这个集合中数的和
        {
           if(m % i == 0)
           {
               fac = i;
               if(good(fac))// 重点1，在模n中与n以g为gcd的所有小于n的数x所在的集合，即为n除以g后的模集合中与(n/g)互质的数，即phi(n/g)的集合（因为gcd(x,n) == g, 即两者除g外无更大公约数，因此除以g后余下的数必定互质，否则g不为gcd）
               {
                   ans += (getEuler((LL)(m/fac)) * (LL)m / 2); // 重点2：神定理!!!!!!!!!：小于x且与x互质的数（模x可逆元的集合中）的和 = phi(x) * x / 2,
                                                                //证明：如果a 与 x互质，那么x - a也与x互质（反证即可），那么成对的可逆元相加为x，总的规模为phi(x),首位相加求和再除以2可推的此式
               }
               fac = m/i;
               if(i * i == m || i == 1)
               {
                   continue;
               }
               if(good(fac))
               {
                   ans += (getEuler((LL)(i)) * (LL)m / 2);
               }
           }
        }
        printf("Case #%d: %I64d\n",++Case,ans);
    }
    return 0;
}

