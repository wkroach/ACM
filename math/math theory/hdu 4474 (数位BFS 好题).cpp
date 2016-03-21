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
    vector <int>s;///��һ����̬����洢��λ����ֹ������ULL���ҷ������
};

node bfs(int mod)///��λBFS����ģ�����ж��Ƿ���n�ı���
{
    queue <node> q;
    while(!q.empty())
        q.pop();
    for(int i=1;i<=9;++i)///��ʼ������λ��Ϊ0
    {
        if(num[i]) continue;
        node a;
        a.x=i%mod;///���ǵ�nΪ1�������ҲҪȡģ
        a.s.clear();
        a.s.push_back(i);
        q.push(a);
        visit[a.x]=1;///���ڱ�ǽڵ㣬����ʹ��ģ���㣬���ֻ��n�ֽڵ�
    }
    while(!q.empty())
    {
       node a=q.front();
        if(a.x==0) return a;
        q.pop();
        for(int i=0;i<=9;++i)///ÿ�ζ�����ǰ���ֺ����ټ�1λ��ͬʱ�ٳ�10��iȡģ
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
