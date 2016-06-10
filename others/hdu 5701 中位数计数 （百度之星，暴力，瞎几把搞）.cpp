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

#define Size 100005
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
LL n,m,k;
LL ql,qr,pos;

LL arr[10005];
LL rsum1[20005];///记录从当前数往右走到相距为奇数的点时比它大和小的数，以10000为中值，每次都加10000，则正负数均分布在10000两边
LL rsum2[20005];///记录向右走相距为偶数的数
LL ans[10005];

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
//    cin>>t;
//    while(t--)
    while(scanf("%I64d",&n) == 1)
    {
        for(LL i = 0; i < n; ++i)
        {
            scanf("%I64d",&arr[i]);
        }
        for(LL i = 0; i < n;++i)///O(n^2)对每个数进行暴力
        {
            memset(rsum1,0,sizeof(rsum1));
            memset(rsum2,0,sizeof(rsum2));
            ans[i] = 0;
            LL rtmp = 0;//计算右边大于arr[i]的数的数目与小于arr[i]的数的数目的差值
            for(LL j = i;j<n;j++)///从当前位置往右扫，只存储记录，不计算
            {
                if(arr[j] > arr[i])
                {
                    rtmp++;
                }
                else if(arr[j]<arr[i])
                {
                    rtmp--;
                }
                if((j-i)&1)///注意！！！！奇偶要分开算，因为偶数长度的中位数一定不符合要求
                    rsum1[rtmp+10000]++;///每次都加10000，即可将正负区分开
                else
                    rsum2[rtmp+10000]++;///每次计算比它大或小的数有多少个
            }
            LL ltmp = 0;///从当前位置往左扫时的记录
            for(LL j = i;j>=0;--j)///扫左边直接计算不需要存储，而且arr[i]已包含在rsum2[10000]中，不会重复计算
            {
                if(arr[j] > arr[i])
                {
                    ltmp++;
                }
                else if(arr[j]<arr[i])
                {
                    ltmp--;
                }
                LL flag = (i-j)&1;
                if(flag)///只有左右两端奇偶性相同才能相连，保证整段数目为奇数
                {
                    ans[i] += rsum1[10000 - ltmp];///当左右两边的记录之和为0时，即这段数列中，比arr[i]大的数和小的数数目一样
                }
                else///那么只需要找到右边对应的与左边记录相反的数即可，
                {
                    ans[i] += rsum2[10000 - ltmp];
                }
            }
        }
        for(LL i = 0;i<n;++i)
        {
            if(i<n-1)
                printf("%I64d ",ans[i]);
            else
            {
                printf("%I64d\n",ans[i]);
            }
        }
    }
    return 0;
}
