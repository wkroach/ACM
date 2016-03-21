//Îâ¿Â
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define N 100005
double arr[200][200];
int ai[10005];
double dp[10005][200];///dp[i][j]表示用第j组队打败第i个（实际是倒着数）ai的概率
int p(int n)
{
    return n*(n-1)*(n-2)/6;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int m,n;
    while(scanf("%d",&m)==1)
    {
        memset(arr,0,sizeof(arr));
        memset(dp,0,sizeof(dp));
        int t=p(m);
        for(int i=0;i<t;++i)
            for(int j=0;j<t;++j)
                scanf("%lf",&arr[i][j]);
        scanf("%d",&n);
        ///预处理ai，因为要从后往前dp，所以倒着输入ai
        for(int i=n;i>0;--i)
            scanf("%d",&ai[i]);
        ///预处理dp数组，使用第i个队打败第0个ai的概率为1
        for(int i=0;i<t;++i)
            dp[0][i]=1;
        ///dp过程，从后往前枚举每一个ai，用状态转移方程判断换队与否
        for(int i=1;i<=n;++i)
            for(int j=0;j<t;++j)
            {
                dp[i][j]=arr[j][ai[i]]*max(dp[i-1][j],dp[i-1][ai[i]]);///状态转移方程
            }
        double Max=-1;
        for(int i=0;i<t;++i)
            Max=max(Max,dp[n][i]);
        printf("%.6lf\n",Max);
    }
    return 0;
}

