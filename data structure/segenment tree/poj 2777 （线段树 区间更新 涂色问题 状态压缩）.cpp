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
int n,m,k;
int ql,qr,pos,val;
int sum[Size*4];
int lazy[Size*4];

void push_up(int now,int l,int r)///利用位运算或，统计两个区间颜色，即两个数中二进制1相或
{
    if(l>=r)
        return;
    sum[now] = sum[now*2] | sum[now*2+1];
}

void push_down(int now,int l,int r)
{
    if(l>=r)
        return;
    if(lazy[now]!=-1)
    {
        lazy[now*2] = lazy[now*2+1] = lazy[now];
        sum[now*2] = sum[now*2+1] = lazy[now];
        lazy[now] = -1;
    }
}

void build(int now,int l,int r)///初始时每个格子均为1，即最低位有一个1，即1
{
    sum[now] = 1;
    if(l>=r)
    {
        return;
    }
    build(lson);
    build(rson);
}
void update(int now,int l,int r)
{
    int mid = (l+r)/2;
    if(ql<=l&&r<=qr)
    {
        lazy[now] = val;
        sum[now] = val;
        return ;
    }
    push_down(now,l,r);
    if(ql<=mid) update(lson);
    if(qr>mid) update(rson);
    push_up(now,l,r);
}


int quire(int now,int l,int r)///统计区间内的颜色数，即将查询到的区间的值或运算的结果中1的数目即是结果
{
    int mid = (l+r)/2;
    push_down(now,l,r);
    if(ql<=l&&qr>=r)
    {
        return sum[now];
    }
    int ans = 0;
    if(ql<=mid) ans |= quire(lson);
    if(qr>mid) ans |= quire(rson);
    return ans;
    push_up(now,l,r);
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
    while(scanf("%d%d%d",&n,&t,&k)==3)
    {
        char s[10];
        memset(lazy,-1,sizeof(lazy));
        build(1,1,n);
        for(int i=0;i<k;++i)
        {
            scanf("%s",s);
            if(s[0] == 'C')
            {
                scanf("%d%d%d",&ql,&qr,&val);
                ql = min(ql,qr);
                qr = max(ql,qr);
                val = 1<<(val-1);///状态压缩，由于颜色只有30种，且只统计不同种颜色数，利用一个int型的数存放，每种颜色对应二进制上的一位1，不同颜色数即1的个数
//                cout<<val<<endl;
                update(1,1,n);
            }
            else if(s[0] == 'P')
            {
                scanf("%d%d",&ql,&qr);
                ql = min(ql,qr);
                qr = max(ql,qr);
                int ans = quire(1,1,n);
                int tmp = 0;
//                cout<<ans<<endl;
                while(ans)
                {
                    if(ans&1)
                        tmp++;
                    ans >>= 1;
                }
                cout<<tmp<<endl;
            }
        }
    }
    return 0;
}

