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

#define Size 1005
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
using namespace std;
int n,m,k;
int ql,qr,pos,val;
int dp[Size][Size];
int lcs(const string& s1,  const string& s2)///lcs（最长公共子序列）模板
{
    memset(dp,0,sizeof(dp));
    for(int i=0;i<s1.length();++i)
    {
        for(int j=0;j<s2.length();++j)
        {
            if(s1[i] == s2[j])///若两个当前数位相等，则结果为前一最长长度加一
            {
                dp[i+1][j+1] = dp[i][j] + 1;
            }
            else
            {
                dp[i+1][j+1] = max(dp[i][j+1],dp[i+1][j]);///若不等，则为任意序列前一个阶段最长长度
            }
        }
    }
    return dp[s1.size()][s2.size()];
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
    string s1,s2;
    while(cin>>s1>>s2)
    {
       cout<<lcs(s1,s2)<<endl;
    }
    return 0;
}

