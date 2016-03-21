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
int n=0,m=0,ql=0,qr=0,h=0,a=0,b=0;
int arr[M],arr2[M],arr3[M],sum[M*10];

struct node
{
    int l;
    int r;
    int h;
    int t;
}q[M];

bool cmp1(int a,int b)///间接排序
{
    return arr[a]<arr[b];
}

bool cmp2(node a,node b)
{
    return a.h<b.h;
}

void push_up(int now)
{
    sum[now]=sum[now*2]+sum[now*2+1];
}

void build(int now,int l,int r)
{
    if(l==r)
    {
        sum[now]=0;
        return ;
    }
    build(lson);
    build(rson);
    push_up(now);
}

void update(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(l==r)
    {
        sum[now]++;
        return ;
    }
    if(a<=mid) update(lson);
    if(a>mid) update(rson);
    push_up(now);
}

int quire(int now,int l,int r)
{
    int ans=0;
    int mid=l+(r-l)/2;
    if(ql<=l&&r<=qr)
    {
        return ans+=sum[now];
    }
    if(ql<=mid) ans+=quire(lson);
    if(qr>mid) ans+=quire(rson);
    return ans;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(arr,0,sizeof(arr));
        memset(arr2,0,sizeof(arr2));
        memset(sum,0,sizeof(sum));
        memset(arr3,0,sizeof(arr3));
        build(1,0,n-1);
        for(int i=0;i<n;++i)
            scanf("%d",&arr[i]),arr2[i]=i;///离线处理，保存从小到大每个数的位置
        sort(arr2,arr2+n,cmp1);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].h);///离线处理，保存输入的顺序
            q[i].t=i;
        }
        printf("Case %d:\n",T-t);
        sort(q,q+m,cmp2);///将询问从小到大排序
        int tmp=0;
        for(int i=0;i<m;++i)
        {
            if(tmp<n)///注意tmp的枚举范围，小心数组越界
            {
                while(arr[arr2[tmp]]<=q[i].h)///从小到大比较当前更新(插入)的数
                    ///和询问的数，如果比询问的数小，即放入线段树(更新节点)
                {
                    a=arr2[tmp];b=arr[arr2[tmp]];
                    update(1,0,n-1);
                    tmp++;
                    if(tmp==n) break;
                }
            }
            ql=q[i].l;qr=q[i].r;h=q[i].h;
           arr3[q[i].t]=quire(1,0,n-1);///直到没有再比当前查询数小的数，查询，并将结果放入它的输入位置
        }
        for(int i=0;i<m;++i)
            printf("%d\n",arr3[i]);
    }
    return 0;
}
