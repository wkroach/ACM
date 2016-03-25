
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
#define N 100000
#define M 50
#define INF 0x3f3f3f3f
using namespace std;


int n,m,t;
double dp[N+5];
int main()
{
//    freopen("input.txt","r",stdin);
    scanf("%d",&t);
    int Case=1;
    while(t--)
    {
        double ans=0;
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        dp[0]=0;
        for(int i=0;i<n;++i)
        {

                dp[i+1] = dp[i] + 1.0*n/(n-i);///原始式：dp[i+1]=(n-i/n)*dp[i]+i/n*dp[i+1]+1
            //dp[i+1]由dp[i]推过来的概率为(n-i)/n,由它自己dp[i+1]推过来的概率为(i/n),再加上1
            ///概率系数之和为1
//            cout<<dp[i]<<endl;
        }
        printf("Case %d: ",Case++);
        printf("%lf\n",dp[n]);
    }
    return 0;
}
