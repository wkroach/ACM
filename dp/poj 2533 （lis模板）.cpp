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
int dp[Size];
vector<int> arr;

int lis(vector<int> & arr)///lis模板
{
    memset(dp,0,sizeof(dp));
    dp[0] = 1;
    int ans = dp[0];
    for(int i = 1; i < arr.size(); ++i) ///对于每一个数，dp[i]为以它为结尾的最长子序列
    {
        for(int j = 0; j < i; ++j)///在前i-1个数中找出结尾比他小前长度最长的值
        {
            if(arr[i] > arr[j])
            {
                dp[i] = max(dp[i], dp[j]);
            }
        }
        dp[i] += 1;///
        ans = max(ans, dp[i]);///保持所有子序列中最大的值
    }
    return ans;
}

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
    while(scanf("%d",&n)==1)
    {
        arr.clear();
        for(int i=0;i<n;++i)
        {
            scanf("%d",&x);
            arr.push_back(x);
        }
        cout<<lis(arr)<<endl;
    }
    return 0;
}

