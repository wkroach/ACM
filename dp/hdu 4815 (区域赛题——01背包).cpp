//吴柯
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
int arr[100];
int dp[40005];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t,n;
    double p;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d%lf",&n,&p);
        for(int i=1;i<=n;++i)
            scanf("%d",&arr[i]);
        dp[0]=1;
        ///dp——01背包问题
        for(int i=1;i<=n;++i)///枚举每一个题（物品）
            for(int j=40000;j>=arr[i];--j)///枚举分数（重量），从后往前扫，否则会判重
                if(dp[j-arr[i]])///如果 当前枚举的分数 减去 当前枚举的题目分数 的情况存在
                    dp[j]+=dp[j-arr[i]];///则加上此题目（物品），即j值存在的方案数再加上j-arr[i]的方案数，否则跳过（不加如背包），
        double sum=0,k=(1LL<<n);
        for(int i=0;i<=40000;++i)
        {
            sum+=((double)dp[i]/k);
            if(sum>=p)
            {
                printf("%d\n",i);
                break;
            }
        }
//        for(int i=0;i<=20;++i)
//            printf("%d ",dp[i]);
//        puts("");
    }
    return 0;
}

