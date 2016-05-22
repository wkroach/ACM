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


LL vis[10010];
vector<LL> arr;
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        memset(vis,0,sizeof(vis));
        arr.clear();
        scanf("%I64d%I64d%I64d%I64d",&x,&m,&k,&y);
        printf("Case #%I64d:\n", ++Case);
        LL ans = 0;
        LL len1, len2;
        len1 = len2 = 0;
        LL tmp = x%k;
        for(LL i = 0;i<100010;++i)///重点，对于任意m，在小于n的范围内，必定能找到m的幂的模n循环节，但这个循环节是无规律的,长度最大不超过n（抽屉原理，n个以上的数对n取模一定有重复的模数）
                                    ///重点，要与模n循环群相区别，若m与n互质，那么m的幂对于模n存在循环节，且这些模的数必定存在于模n 的循环群中，且满足欧拉定理
        {
            if(vis[tmp])//找出初始不在循环节的部分以及循环节的起始于终止位置，并保存两个长度
            {
                len2 = i + 1 - vis[tmp];
                len1 = vis[tmp]-1;
                break;
            }
            else
            {
                vis[tmp] = i+1;
            }
            arr.push_back(tmp);///记录每个模值
            tmp *= 10;
            tmp %= k;
        }
//        cout<<len1<<" "<<len2<<endl;
        if(m < len1 + len2)///注意！！！！！在m的范围内可能没有循环节，即m小于最小循环节长度和未循环部分和只能暴力求解
        {
            for(LL i=0;i<m;++i)
            {
                ans += arr[i];
                ans %= k;
            }
//            cout<<ans<<endl;
        }
        else
        {
            for(LL i=0;i<len1;++i)///反之，先对未循环求解
            {
                ans += arr[i];
                ans %= k;
            }
            LL tmp = 0;
            for(LL i = len1;i < len1 + len2;++i)///再单独对循环节求解
            {
                tmp += arr[i];
                tmp %= k;
            }
            LL num = (m-len1)/len2;//判断有几个循环节，并求和
            LL len3 = (m-len1)%len2;
            tmp = tmp * num % k;
            ans += tmp;
            ans %= k;
            for(LL i = len1;i<len1 + len3;++i)//对于之后剩余的部分再求和即是结果
            {
                ans += arr[i];
                ans %= k;
            }
        }
        if(ans != y)
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
        }
    }
    return 0;
}
