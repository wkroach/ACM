//wuke
#include<cstdio>
#include<cstdlib>
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
using namespace std;
#define LL long long int
#define MOD 1000000007
#define M 30
#define INF 3000000000
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
const int N=10000;
double p[N+5];
struct node
{
    int v;
    double p;
    bool friend operator <(node a,node b)
    {
        return a.v<b.v;
    }
}arr[N+5];
double dp[N+5];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif// ONLINE_JUDGE
    int t;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(dp,0,sizeof(dp));
        memset(p,0,sizeof(p));
        double lim=0.0;
        int n;
        scanf("%lf %d\n",&lim,&n);
        lim=1-lim;
        int sum=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%lf",&arr[i].v,&arr[i].p);
            arr[i].p=1-arr[i].p;
            sum+=arr[i].v;
        }
        sort(arr,arr+n);
//        cout<<1;
        dp[0]=1;
        for(int i=0;i<n;++i)
        {
            for(int j=arr[i].v;j<=sum;j++)///01背包，优化成一维时要倒着扫
            {
                if(dp[j-arr[i].v])
                    dp[j]=max(dp[j],dp[j-arr[i].v]*arr[i].p);
            }
        }
        int ans=0;
        for(int i=sum;i>=0;--i)
        {
//            cout<<dp[i]<<endl;
            if(dp[i]>lim)
            {
                ans=i;
                break;
            }
        }
        printf("Case %d: ",T-t);
        printf("%d\n",ans);
    }
    return 0;
}
