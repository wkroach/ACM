
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

                dp[i+1] = dp[i] + 1.0*n/(n-i);///ԭʼʽ��dp[i+1]=(n-i/n)*dp[i]+i/n*dp[i+1]+1
            //dp[i+1]��dp[i]�ƹ����ĸ���Ϊ(n-i)/n,�����Լ�dp[i+1]�ƹ����ĸ���Ϊ(i/n),�ټ���1
            ///����ϵ��֮��Ϊ1
//            cout<<dp[i]<<endl;
        }
        printf("Case %d: ",Case++);
        printf("%lf\n",dp[n]);
    }
    return 0;
}
