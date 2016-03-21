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
const int N=100;
int arr[N+5];
double dp[N+5];///期望dp
int n,m;


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
        scanf("%d",&n);
        int cnt=n,sum=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&arr[i]);
            dp[i]=arr[i];
        }
        for(int i=n;i>=1;--i)///求起始点能得到的金钱，所以像背包一样倒着遍历
        {
            if(n-i<=6)
            {
                for(int j=n;j>i;--j)
                {
                    dp[i]+=dp[j]/(n-i);
                }
            }
            else
            {
                for(int j=i+6;j>i;--j)
                {
                    dp[i]+=dp[j]/6;
                }
            }
        }
        printf("Case %d: ",T-t);
        printf("%.6lf\n",dp[1]);
    }
    return 0;
}
