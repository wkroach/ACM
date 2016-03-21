
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define N 100005
int n,m;
char arr[1005][35];
int root[1005];
vector <int> mst;
struct e
{
    int a;
    int b;
    int len;
}edge[500510];
bool cmp(e a,e b)
{
    return a.len<b.len;
}
void init()
{
    for(int i=1;i<=n;++i)
        root[i]=i;
}

int Findroot(int n)
{
    return root[n]==n?n:(root[n]=Findroot(root[n]));
}

void uino(int x,int y)
{
    int a=Findroot(x);
    int b=Findroot(y);
    if(a!=b)
        root[b]=a;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d%d",&n,&m)==2)
    {
        memset(arr,0,sizeof(arr));
        memset(root,0,sizeof(root));
        mst.clear();
        int p=0;
        for(int i=1;i<=n;++i)
            scanf("%s",arr[i]);
        init();
        ///预处理，找到所有的边，并将边以长度排序
        for(int i=1;i<=n;++i)
        {
            for(int j=i+1;j<=n;++j)
            {
                int Max=abs(arr[i][0]-arr[j][0]);
                for(int k=1;k<m;++k)
                    Max=max(Max,abs(arr[i][k]-arr[j][k]));
                edge[p].len=Max,edge[p].a=i,edge[p].b=j;
                //printf("%d ",edge[p].len);
                p++;
            }
        }
        sort(edge,edge+p,cmp);
        ///Kruskal算法
        for(int i=0;i<p;++i)
        {
            int x=Findroot(edge[i].a),y=Findroot(edge[i].b),l=edge[i].len;
            if(x!=y)
                root[x]=y,
                mst.push_back(l);
        }
//        puts("");
//        for(int i=0;i<mst.size();++i)
//            printf("%d ",mst[i]);
        ///最小生成树的最后一个边即是树中最大的权值，即题目要求的答案
        printf("%d\n",mst.back());
    }
    return 0;
}

