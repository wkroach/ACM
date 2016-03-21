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
#define N 205
#define INF 0x3f3f3f3f
#define seed 31
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,vis[N],dis[N];
int e[N][N];///�������϶�ʱ��Ϊ�ڽӾ���
vector <int> v[N];///�ڽӱ����ڱ�ʾ�ڵ���ǰ��̹�ϵ

void init()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=N;++i)
        dis[i]=INF;
}

void dijkstra(int a,int b)///��������ͼ
///�㷨˼�룺̰��
///ʱ�临�Ӷȣ�O(V^2+E)
{
    dis[a]=0;
    for(int i=1;i<=n;++i)///ִ��n��ѭ����nΪ�ڵ����
    {
        int m=INF,s;///ÿ��ѭ����Ҫ�ҳ�һ��δ����������dis��С�Ľڵ㣬�����
        for(int j=1;j<=n;++j)///��ѯ��Сdis�Ľڵ���Ҫ�������нڵ㣬��ѭ��n��
            if(!vis[j]&&dis[j]<m) m=dis[j],s=j;
        vis[s]=1;///���
        for(int j=0;j<v[s].size();++j)///���ڵ�ǰ�����С�ڵ㣬������ÿ����̽ڵ����ɳڲ���
            dis[v[s][j]]=min(dis[v[s][j]],dis[s]+e[s][v[s][j]]);///�ɳڲ�����������һ��״̬ת�Ʒ���
            ///����ά��ÿ���ڵ����Сdis

            ///tips:�ɳڲ���ʵ�ʽ�dis���Ͻ硰�ս����ˣ���ȴ���ڵ�֮������ǲ���ʽ���������ɡ��ˣ���˽����ɳڲ���
    }
}

int main()
{

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int a,b,c,k=0;
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=N;++i)
            v[i].clear();
        for(int i=1;i<=N;++i)
            for(int j=1;j<=N;++j)
            {
                if(i==j) e[i][j]=0;
                e[i][j]=INF;
            }
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            e[a][b]=c;
            v[a].push_back(b);
        }
            init();///��vis��dis��ʼ��
            dijkstra(1,n);///�ɸ�����ĿҪ�����ʼĩ�ڵ�
            printf("%d\n",dis[n]);
    }
    return 0;
}

