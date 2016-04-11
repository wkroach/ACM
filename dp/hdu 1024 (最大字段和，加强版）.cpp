#include<cstdio>
#include<cstdlib>
#include<time.h>
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

//#include<bits/c++std.h>

#define Size 1000005
#define inf 2e9
#define INF 2e18
#define LL long long int
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define Max(a,b) (a)>(b)?(a):(b)
using namespace std;
int n,m,k;
int ql,qr,pos;
LL arr[Size];
LL marr[Size];
LL dp[Size];

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int Case=0;
//    cin>>t;
//    while(t--)
    while(scanf("%d%d",&m,&n)==2)
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%I64d",&arr[i]);
            marr[i] = 0;
            dp[i] = 0;
        }
        dp[0] = 0;///滚动数组，dp[i][j]表示对前j个数，取i段的最大值
        marr[0] = 0;
        LL ans;
        for(int i=1;i<=m;++i)
        {
            ans = -INF;///对于每段，要求出当前所有情况的最大值
            for(int j=i;j<=n;++j)
            {
                dp[j] = Max(dp[j-1] + arr[j],marr[j-1] + arr[j]);///状态转移方程，dp[i][j] = max(dp[i][j-1] + arr[j], max(dp[i-1][k])(k<j) + arr[j])分别对应第i个数放在前i段中还是新开一段并加在前i-1段中的最大的情况
                ///marr[j-1]为上一段数的j之前所有数的最大值
                marr[j-1] = ans;///保存当前段数的前一个数即之前的最大值
                ans = Max(ans,dp[j]);///更新当前段数当前数即之前的最大值
            }
        }
//        cout<<dp[m]<<endl;
        printf("%I64d\n",ans);
    }
    return 0;
}

