
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

double dfs(int n,int m,int p)///���仯����,p��ʾ��ǰ����(0)���ǹ���(1)
///ע�⣡�����ǵ����㹫����ʤ��ʱ��1������׽���˰���2������׽���ĺ�������׽�����󡣡���
///���Ϊ1ʱ��ֱ�Ӽ�����ʣ�Ϊ2ʱ��Ҫ�ݹ��������ʤ���ĸ��ʣ��ٽ��������
///���ڵ���û��ץ���������������Ϊ0ʱ����ʤ�������Ե���������Ϊ0ʱ��Ӧ����0������������µĹ���ʤ��Ϊ0
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
        if(m+n-1==0) return dp[n][m][p][1]=0;///ע�⵱��ĸΪ0ʱ����ʾ���պ�ȡ�����󣬹���ʧ�ܣ����Է���0
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
