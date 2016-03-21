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
#define Size 105
#define inf 2e9
#define INF 2e18
#define LL long long
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
///并查集经典题
int n,m,k;
int fa[50005],relate[50005];///fa同普通并查集，relate[i]表示i的根节点到i的偏移量
///本题中i到j偏移量为0表示两者同类，为1表示i吃j，为2表示j吃i

void init()///初始化
{
    for(int i=1;i<=n;++i)
    {
        fa[i]=i;
    }
    memset(relate,0,sizeof(relate));///初始时，每个节点根节点都是自己，偏移量为0
}

int find_fa(int a)///重点！！！带路径压缩的查询
{
    if(fa[a]==a)
    {
        return fa[a];
    }
    int tmp=fa[a];///先保存节点的当前父节点，因为后面递归压缩有可能使父（根）节点不为当前的父节点
    fa[a] = find_fa(fa[a]);
    relate[a]=(relate[a]+relate[tmp])%3;///重点，向量偏移的向量表达式
    ///grandfa->son = grandfa->fa + fa->son
    ///回溯更新根节点对链上所有节点的偏移量
    ///由于偏移量的范围是3，结果要对3取模
    return fa[a];
}

void unio(int a,int b,int x,int y,int d)///重点！！！带按权（秩）合并的合并
{
    fa[b]=a;
    relate[b]=(relate[x]+d-1+3-relate[y])%3;///向量偏移
    ///b->a = b->x + x->y +y->a
    ///x->y可以由输入数据时的D推出来，应该是d-1
    ///重点！！fa->son = (3 - son->fa)%3 由对称性可得，
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int d,x,y;
    scanf("%d%d",&n,&m);///注意，本题只有一组输入数据
    init();
    int ans=0;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&d,&x,&y);
        if(x>n||y>n)
        {
            ans++;
        }
        else if(d==2&&x==y)
        {
            ans++;
        }
        else
        {
            int a,b;
            a=find_fa(x);
            b=find_fa(y);
            if(a!=b)///如果a,b本身不在同一集中，先合并，且默认合并后的偏移量为真
            {
                unio(a,b,x,y,d);
            }
            else
            {
                int tmp=(3-relate[x]+relate[y])%3;///如果已经在同一集中，判断两者实际的向量偏移量是否与输入量相同
                if(d-1!=tmp)
                {
                    ans++;
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}








