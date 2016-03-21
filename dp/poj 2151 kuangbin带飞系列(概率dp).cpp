
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
#define N 1000
#define M 30
#define ULL unsinged long long
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
///此题需要许多概率的基本知识(最好回顾一下课本):
///基础知识1,：p(ab)=p(a)-P(a(~b))
///基础知识2：p(a)=p(a1)+p(a2)+p(a3)+......p(an),a1,a2,a3..an均属于a且相互独立
///做题最多的队伍至少做出n题==至少有一个队伍做出至少n题（两者逆否命题相等，所以等价）
int n,m,k,t;
double dp[N+5][M+5][M+5];///当前第i个队伍，做第j道题时，已经做出k道题的概率
double arr[N+5][M+5];///第i个队伍做出第j道题的概率
double s[N+5][M+5];///第i个队伍做出不超过j道题的概率
int main()
{
//    freopen("input.txt","r",stdin);
//    scanf("%d",&t);
    int Case=1;
//    while(t--)
//    {
    while(scanf("%d%d%d",&m,&t,&n)==3)
    {
        if(!m&&!n&&!t) break;
        memset(dp,0,sizeof(dp));
        memset(arr,0,sizeof(arr));
        memset(s,0,sizeof(s));
        double ans=1.0;
        for(int i=1;i<=t;++i)
        {
            for(int j=1;j<=m;++j)
            {
                scanf("%lf",&arr[i][j]);
            }
        }
        for(int i=1;i<=t;++i)
        {
            double tmp=1.0;
            dp[i][0][0]=1.0;///在第0道题时做出0道题的概率显然为0
            for(int j=1;j<=m;++j)
            {
                tmp*=(1-arr[i][j]);
                dp[i][j][0]=tmp;
                for(int k=1;k<=j;++k)///分为1，在j-1题时已经做出了k题，第j题未做出来
                    ///2，在j-1题时已经做出k-1题，第j题做出来
                {
                    dp[i][j][k]=dp[i][j-1][k]*(1-arr[i][j])+dp[i][j-1][k-1]*arr[i][j];
                }
            }
            ans*=(1-dp[i][m][0]);///每个队伍至少做出一题的概率,即p(a)
        }
        double tmp=1.0;
        for(int i=1;i<=t;++i)
        {
            s[i][0]=dp[i][m][0];
            for(int j=0;j<=n-1;++j)///基础知识2
            {
                s[i][n-1]+=dp[i][m][j];
            }
            tmp*=(s[i][n-1]-s[i][0]);///tmo表示所有队伍均为做出n道题且均做出至少1题
            ///基础知识1，tmp即p(a(~b))
        }
        printf("%.3lf\n",ans-tmp);///即p(ab),每个队伍都做出至少1题，且存在一支队伍做出至少n题
    }
//    }
    return 0;
}
