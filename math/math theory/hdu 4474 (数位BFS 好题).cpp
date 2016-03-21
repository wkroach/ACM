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
#define N 10005
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m;
int num[10];
int visit[N];
struct node
{
    int x;
    vector <int>s;///用一个动态数组存储数位，防止数过大爆ULL，且方便添加
};

node bfs(int mod)///数位BFS，用模运算判断是否是n的倍数
{
    queue <node> q;
    while(!q.empty())
        q.pop();
    for(int i=1;i<=9;++i)///初始化，首位不为0
    {
        if(num[i]) continue;
        node a;
        a.x=i%mod;///考虑到n为1的情况，也要取模
        a.s.clear();
        a.s.push_back(i);
        q.push(a);
        visit[a.x]=1;///用于标记节点，由于使用模运算，最多只有n种节点
    }
    while(!q.empty())
    {
       node a=q.front();
        if(a.x==0) return a;
        q.pop();
        for(int i=0;i<=9;++i)///每次都往当前数字后面再加1位，同时再乘10加i取模
        {
            if(num[i]) continue;
            node tmp=a;
            tmp.x=((a.x%mod*(10%mod))%mod+i%mod)%mod;
            tmp.s.push_back(i);
            if(!visit[tmp.x])
                q.push(tmp),
                visit[tmp.x]=1;
        }
    }
    node f;
    f.x=-1;
    return f;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t=0;
    while(scanf("%d%d",&n,&m)==2)
    {
        memset(visit,0,sizeof(visit));
        memset(num,0,sizeof(num));

        for(int i=1;i<=m;++i)
        {
            int a;
            scanf("%d",&a);
            num[a]=1;
        }
        printf("Case %d: ",++t);
       node ans=bfs(n);
       if(ans.x==-1) printf("-1\n");
       else
       {
           for(int i=0;i<ans.s.size();++i)
                printf("%d",ans.s[i]);
           puts("");
       }
    }
    return 0;
}
