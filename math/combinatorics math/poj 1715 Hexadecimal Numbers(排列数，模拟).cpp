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
#define LL long long
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
LL n,m,k;

LL com[20][20];
char figure[20];
LL sum[10];
int vis[20];

LL fac(int a)
{
    if(!a) return (LL)1;
    LL ans=1;
    for(int i=a;i>=1;--i)
    {
        ans *= (LL)i;
    }
    return ans;
}

void init()
{
    char cnt = '0';
    for(int i=1;i<=10;++i)
    {
        figure[i] = cnt++;
    }
    cnt = 'A';
    for(int i=11;i<=16;++i)
    {
        figure[i] = cnt++;
    }

    memset(com,0,sizeof(com));
    for(int i=0;i<=16;++i)
    {
        com[i][0] = 1;
    }
    com[1][1] = 1;
    for(int i=2;i<=16;++i)
    {
        for(int j=1;j<=8;++j)
        {
            com[i][j] = com[i-1][j] + com[i-1][j-1];
        }
    }
    for(int i=1;i<=16;++i)
    {
        for(int j=1;j<=min(i,8);++j)
        {
            com[i][j] *= fac((LL)j);
        }
    }
    memset(sum, 0, sizeof(sum));
    for(int i = 8; i >= 2; --i)
    {
        sum[i] = 15*com[15][i - 1];
    }
    sum[1] = 16;
}

char get_figure(int tmp3)
{
    int cnt2 = 0;
    for(int i=16;i>=1;--i)
    {
        if(vis[i])
        {
            continue;
        }
        if(cnt2++ == tmp3)
        {
            vis[i] = 1;
            return figure[i];
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    init();
    int t;
    int x,y,z;
//    int Case=0;
//    cin>>t;
//    while(t--)
//    cin>>n;
    while(scanf("%I64d",&n)==1)
    {
        n--;
        memset(vis,0,sizeof(vis));
        int sum1 = 0;
        int cnt=8;
        int cnt2 = 16;
        int cnt3 = 0;
        int cnt4 = 0;
        string s;
        s.clear();
        while(cnt)
        {
            if(n >= sum[cnt])
            {
                n -= sum[cnt];
                cnt--;
                cnt4++;
            }
            else
            {
                cnt3++;
                LL tmp = com[16-cnt3][8-cnt3-cnt4];
                LL tmp2 = n/tmp;
                LL tmp3 = n%tmp;
                s.push_back(get_figure((int)tmp2));
                n = tmp3;
                cnt--;
            }
        }
        cout<<s<<endl;
    }
    return 0;
}
