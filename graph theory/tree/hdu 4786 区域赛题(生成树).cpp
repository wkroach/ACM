
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define N 50
#define M 50
#define INF 0x3f3f3f3f
using namespace std;
int n,m,t;
int rt[100005];
struct edge
{
    int u;
    int v;
    int len;
     bool operator < (const edge& b)const
    {
        return len<b.len;
    }
};

//bool cmp1(edge a,edge b)
//{
//    return a.len<b.len;
//}

//bool cmp2(edge a,edge b)
//{
//    return a.len>b.len;
//}
vector <int> f;
void fab()
{
    f.push_back(1);
    f.push_back(2);
    for(int i=1;i<=40;++i)
    {
        f.push_back(f[i]+f[i-1]);
    }
}

int root(int x)
{
    return rt[x]==x?x:rt[x]=root(rt[x]);
}

bool unit(int x,int y)
{
    int rx=root(x),ry=root(y);
    if(rx!=ry)
    {
        rt[rx]=ry;
        return true;
    }
    else
        return false;
}

vector <edge> e;

void init()
{
//    e.clear();
    for(int i=1;i<=n;++i)
        rt[i]=i;
}

int main()
{
//    freopen("input.txt","r",stdin);
    scanf("%d",&t);
    int T=t;
    fab();
//    for(int i=0;i<f.size();++i)
//        printf("%d\n",f[i]);
    while(t--)
    {
        int flag=0;
        scanf("%d%d",&n,&m);
        init();
        e.clear();
        for(int i=0;i<m;++i)
        {
            edge tmp;
            scanf("%d%d%d",&tmp.u,&tmp.v,&tmp.len);
            e.push_back(tmp);
//            tmp.u=tmp.u^tmp.v;
//            tmp.v=tmp.u^tmp.v;
//            tmp.u=tmp.u^tmp.v;
//            e.push_back(tmp);
        }
        int sum1=0,sum2=0;
        sort(e.begin(),e.end());///kruskal要跑2遍，一遍找最多的白边，一遍找最少的白边
        for(int i=0;i<e.size();++i)
        {
            int u=e[i].u,v=e[i].v,len=e[i].len;
            if(unit(u,v))
            {
                if(len==1)
                {
                    sum1++;
                }
            }
        }
//        sort(e.begin(),e.end(),cmp2);///fuck?
        init();
        for(int i=e.size()-1;i>=0;--i)
        {
            int u=e[i].u,v=e[i].v,len=e[i].len;
            if(unit(u,v))
            {
                if(len==1)
                {
                    sum2++;
                }
            }
        }
        for(int i=1;i<=n;++i)///可能存在没有生成树的情况，要对于所有节点进行判断是不是都在同一集内，是则继续，否则输出No
        {
            if(unit(i,1))
            {
                flag=1;
                break;
            }
        }
        if(flag)
        {
            printf("Case #%d: ",T-t);
            printf(flag?"No\n":"Yes\n");
            continue;
        }
//        vector <int> ::iterator it1=f.begin();///二分找
//        vector <int> ::iterator it2=f.begin();
//        it1=lower_bound(f.begin(),f.end(),sum1);
//        it2=lower_bound(f.begin(),f.end(),sum2);
////        printf("%d %d %d %d",*it1,sum1,*it2,sum2);
//        if(*it1==*it2)
//        {
//            flag=1;
//            if(*it1==sum1||*it2==sum2)
//                flag=0;
//        }
//        else
//        {
//            flag=0;
//        }
        for(int i=0;i<f.size();++i)///暴力找，因为数据量比较小（40），二分产生的stl开销比暴力要大
        {
            if(f[i]<=sum2&&f[i]>=sum1)
            {
                flag=1;
                break;
            }
        }
       printf("Case #%d: ",T-t);
       printf(!flag?"No\n":"Yes\n");
    }
    return 0;
}
