//Îâ¿Â
#include<cstdio>
#include<cstdlib>
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
using namespace std;
#define LL long long int
#define ULL unsigned long long int
#define MOD 1000000007
#define N 105
#define M 100005
#define MAX 1000000000
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int sum[M*4],arr[M*4],arr2[M];
int a=1,b,ql,qr;
int n,d;

void push_up(int now)///sum[now]中存放的是以l~r中的数结尾的最长
///上升序列的长度
{
    sum[now]=max(sum[now*2],sum[now*2+1]);
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        sum[now]=0;///初始化全为0
        return ;
    }
    build(lson);
    build(rson);
    push_up(now);
}

int update(int now,int l,int r)///更新节点
{
    int mid=l+(r-l)/2;
    if(l==r) return sum[now]=b;
    if(a<=mid) update(lson);
    if(a>mid) update(rson);
    push_up(now);
}

int quire(int now,int l,int r)///查询比now小的数中的最长上升序列
{
    int ans1=0,ans2=0;
    int mid=l+(r-l)/2;
    if(ql<=l&&r<=qr)
    {
        return sum[now]+1;
    }
    if(ql<=mid) ans1=quire(lson);
    if(qr>mid) ans2=quire(rson);
    return max(ans1,ans2);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d%d",&n,&d)==2)
    {
        memset(arr,0,sizeof(arr));
        memset(sum,0,sizeof(sum));
        memset(arr2,0,sizeof(arr2));
        build(1,0,M);
        for(int i=0;i<n;++i)
            scanf("%d",&arr[i]);
        int ans=1;
        for(int i=1+d;i<n;++i)
        {
            if(arr2[i-d-1]==0)
                arr2[i-d-1]=1;///用arr2存放以当前节点为结尾的最长序列的长度
            b=arr2[i-d-1];
            a=arr[i-d-1];
            arr2[i-d-1]=update(1,0,M);///每次更新的点的输入位置要比查询的点早d+1
            if(arr[i]==0)///当查查询值为0时，显然没有以它为结尾的最长上升序列(它本身除外)
                goto there;///跳过0
            ql=0,qr=arr[i]-1;///查询区间为比当前查询的数小的数
                arr2[i]=max(arr2[i],quire(1,0,M));///若节点有重复的情况，每次查询要保留最大值
            there:
            ans=max(ans,arr2[i]);///更新答案
        }
        printf("%d\n",ans);
//        for(int i=1;i<n*2+1;++i)
//            printf("%d ",sum[i]);
    }
    return 0;
}
