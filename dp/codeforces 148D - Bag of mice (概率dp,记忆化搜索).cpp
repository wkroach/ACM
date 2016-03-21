
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define eps 1e-9
#define N 1005
#define M 50
#define ULL unsinged long long
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;


int n,m,k,t;
double dp[N][N][3][2];

double dfs(int n,int m,int p)///记忆化搜索,p表示当前是龙(0)还是公主(1)
///注意！！考虑到计算公主的胜率时，1，公主捉到了白鼠，2，公主捉到的黑鼠，龙再捉到黑鼠。。。
///情况为1时可直接计算概率，为2时需要递归计算龙不胜利的概率，再将两者相加
///由于当都没有抓到白鼠而老鼠数量为0时，龙胜利，所以当老鼠数量为0时，应返回0，即这种情况下的公主胜率为0
{
    if(n+m==0) return 0;
    if(n<0||m<0) return 0;
    if(dp[n][m][p][0]) return dp[n][m][p][1];
    if(p)
    {
        dp[n][m][p][0]=1;
        double pro=(double)n/(n+m);
        return dp[n][m][p][1]=pro+(double)m/(n+m)*dfs(n,m-1,0);
    }
    else
    {
        dp[n][m][p][0]=1;
        double pro=(double)m/(n+m);
        if(m+n-1==0) return dp[n][m][p][1]=0;///注意当分母为0时，表示龙刚好取完老鼠，公主失败，所以返回0
        return dp[n][m][p][1]=pro*((double)n/(n+m-1)*dfs(n-1,m-1,1)+(double)(m-1)/(n+m-1)*dfs(n,m-2,1));
    }
}

int main()
{
    freopen("input.txt","r",stdin);
//    scanf("%d",&t);
    int Case=1;
//    while(t--)
//    {
    while(scanf("%d%d",&n,&m)==2)
    {
        memset(dp,0,sizeof(dp));
        double ans=dfs(n,m,1);
//        printf("Case %d: ",Case++);
        printf("%.9lf\n",ans);
    }
//    }
    return 0;
}
