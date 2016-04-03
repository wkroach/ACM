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
using namespace std;
int n,m,k;
int ql,qr,pos;
double dp2[20005];
vector<int> arr;
vector<double> arr2;
double p;
void zero_one_pack(int n, int v, int c, int w, double pol)///01背包的变形版本，将物品的价值总量作背包容量，物品价值作重量，逃出的概率作价值
{
    for(int i=v;i>=c;--i)///保证最优子结构的逃出概率最大，那么结果即为概率大于p的背包的最大重量（物品的价值）
    {
        if(dp2[i - c] * pol > dp2[i])
        {
            dp2[i] = dp2[i-c] * pol;
        }
    }
    /* 一种典型的错误解法：不改变原始的01背包，背包重量与价值均为物品原本的价值，总量为价值总量，多加一个判断概率是否满足大于p
        错误所在，dp[i-c] + w 与dp[i] 相等时，此状态转移方程失效，无法求得最优解。因为，显然仅仅是概率大于p是不够的，在价值相同时要选择概率大的一个
    for(int i=v;i>=c;--i)
    {
        if(dp[i - c] + w > dp[i])
        {
            if(dp2[i - c] * pol > p)
            {
                dp2[i] = dp2[i - c] * pol;
                dp[i] = dp[i - c] + w;
            }
        }
    }*/
}

//void complete_pack(int n, int v, int c, int w)///完全背包模板
//{
//    for(int i = c; i<=v; ++i)
//    {
//        dp[i] = max(dp[i], dp[i-c] + w);
//    }
//}

//void multiy_pack(int n, int v, int c, int w, int k)///多重背包模板
//{
//    if(k*c > v)
//    {
//        complete_pack(n,v,c,w);
//    }
//    else
//    {
//        int t = 1;
//        while(t < k)
//        {
//            zero_one_pack(n, v, t*c, t*w);
//            k -= t;
//            t *= 2;
//        }
//        zero_one_pack(n, v, k*c, k*w);
//    }
//}

int solve(int n,int sum)
{
    memset(dp2,0,sizeof(dp2));///由于概率初始化为0，所以相当于普通背包的初始化为-inf，即将包装满的01背包
    dp2[0] = 1;///什么也没有偷时，逃跑的概率显然为1
    for(int i=0;i<n;++i)
    {
        zero_one_pack(n,sum,arr[i],arr[i],arr2[i]);
    }
    int ans = 0;
    for(int i=sum;i>=0;--i)///由于背包是装满的，所以一定是有序的，倒序找到的满足条件的第一个一定是最多的解
    {
        if(dp2[i] >= p)
        {
            return i;
        }
    }
    return ans;
}
//int solve2(int n, int sum)///多重背包解法，复杂度O(v*sum(log(k)))
//{
//    memset(dp,0,sizeof(dp));
//    for(int i = 0; i<n; ++i)
//    {
//        multiy_pack(n, sum, arr2[i], arr2[i], arr3[i]);
//    }
//    return dp[sum];
//}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        cin>>p>>n;
        p = 1-p;
        int sum=0;
        arr.clear();
        arr2.clear();
        for(int i=0;i<n;++i)
        {
            int tmp;
            double tmp2;
            cin>>tmp>>tmp2;
            sum += tmp;
            arr.push_back(tmp);
            arr2.push_back(1-tmp2);
        }
       int ans = solve(n,sum);
        cout<<ans<<endl;
    }
    return 0;
}

