

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#define N 50
#define M 50
#define INF 0x3f3f3f3f
using namespace std;
int n,m,t;
int arr[55];
int dp[55][1<<20];///一维表示当前取第i个数为止，二维表示当前异或值为j，存放的是达到当前i，j的方案数
///标准解法是使用滚动数组，节省空间
int main()
{
//    freopen("input.txt","r",stdin);
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;++i)
        {
            scanf("%d",&arr[i]);
        }
        sort(arr,arr+n);
        for(int i=0;i<n;++i)
            dp[1][arr[i]]=1;
        dp[0][0]=1;
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<=1<<20;++j)
            {
                if((j^arr[i])>1<<20) continue;
//                if(dp[i][j^arr[i]])
//                {
//                    printf("%d %d %d %d   ",dp[j^arr[i]],j^arr[i],j,arr[i]);
                    dp[i+1][j^arr[i]]=dp[i][j^arr[i]]+dp[i][j];
//                }
            }
        }
//        cout<<endl;
        long long sum=0;
//        for(int i=0;i<n;++i)
//        {
            for(int j=1<<20;j>=m;--j)
            {
//            if(dp[j])
//                printf("%d %d ",dp[j],j);
                sum+=dp[n][j];
            }
//        }
        printf("Case #%d: ",T-t);
        printf("%lld\n",sum);
    }
    return 0;
}
