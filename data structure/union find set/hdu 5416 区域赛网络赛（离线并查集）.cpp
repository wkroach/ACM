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
#define MOD 1000000007
#define N 100000
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,q;
struct edge
{
    int x;
    int y;
    int len;
}e[N+5];
int arr[10005],arr2[10005];
int vis[20005];
int num[20005];
int root[20005];
bool cmp(edge a,edge b)
{
    return a.len<b.len;
}

bool cmp2(int a,int b)
{
    return arr[a]<arr[b];
}
void init()///初始化，并查集，统计数组，间接排序均要初始化
{
    for(int i=1;i<=n;++i)
    {
        root[i]=i;
        num[i]=1;
    }
    for(int i=0;i<q;++i)
        arr2[i]=i;
}

int Findroot(int n)
{
    return root[n]==n?n:(root[n]=Findroot(root[n]));
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    scanf("%d",&t);
    while(t--)
    {
//        for(int i=1;i<=n;++i)
//            printf("%d ",root[i]);
        memset(vis,0,sizeof(vis));
        memset(num,0,sizeof(num));
        memset(arr,0,sizeof(arr));
        scanf("%d%d%d",&n,&m,&q);
        init();
        int p=0;
        for(int i=0;i<m;++i)
            scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
        for(int i=0;i<q;++i)
            scanf("%d",&arr[i]);
        sort(arr2,arr2+q,cmp2);///间接排序，不改变原询问的位置
        sort(e,e+m,cmp);
//        for(int i=0;i<m;++i)
//            printf("%d %d %d ",e[i].x,e[i].y,e[i].len);
        int sum=0;
        p=0;
        for(int i=0;i<q;++i)
        {
            while(p<m&&e[p].len<=arr[arr2[i]])///从小到大进行和并，查询
            {
//                printf("%d ",e[p].len);
                int tmpx=Findroot(e[p].x),tmpy=Findroot(e[p].y);
                p++;
//                printf("%d %d ",tmpx,tmpy);
                if(tmpx!=tmpy)///合并后将数量加上
                {
                    root[tmpx]=tmpy;
                    sum+=(num[tmpy]*num[tmpx])*2;///因为是双向，要乘二
                    num[tmpy]+=num[tmpx];
                    num[tmpx]=num[tmpy];                }
                else
                    continue;
            }
            arr[arr2[i]]=sum;///为省事，直接用当前数组记录答案
        }
        for(int i=0;i<q;++i)///输出依然按照原询问的顺序输出
            printf("%d\n",arr[i]);
        for(int i=0;i<m;++i)
            e[i].x=e[i].y=e[i].len=0;
    }
    return 0;
}
