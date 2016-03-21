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
#define LL long long
#define i64 __LL64
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
LL n,m,k;
LL arr[Size];
vector<LL> tree[Size];///������
LL root[Size];///���򽨱ߣ���¼��ǰ�ڵ�ĸ��ڵ���˭
LL len[Size];///��¼�ӵ�ǰ�ڵ㵽���ڵ��Ȩֵ
LL vis[Size];///��¼��ǰ�ڵ��Ƿ���ʹ�


bool cmp(LL a,LL b)
{
    return len[a]>len[b];
}


void dfs(LL x)///�ݹ��¼ÿ���ڵ��Ȩֵ
{
    for(LL i=0;i<tree[x].size();++i)
    {
        len[tree[x][i]] += len[x];
        dfs(tree[x][i]);
    }
}

LL dfs2(LL x)///�ݹ���ʲ���ǽڵ㣬ֱ���������ʹ��Ľڵ�
{
    if(x == 0)
        return 0;
//    cout<<" "<<len[x]<<endl;
    if(vis[x])
        return len[x];
    vis[x] = 1;
    return dfs2(root[x]);
}

int main()
{

    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
    cin>>t;
    while(t--)
//    cin>>n;
//    while(cin>>s)
    {
        scanf("%I64d%I64d",&n,&m);
        for(LL i=0;i<=n;++i)
            tree[i].clear();
        memset(root,0,sizeof(root));
        memset(vis,0,sizeof(vis));
        for(LL i=1;i<=n;++i)
        {
            scanf("%d",&arr[i]);
            len[i] = (LL)arr[i];
        }
        for(LL i=1;i<n;++i)
        {
            scanf("%I64d%I64d",&x,&y);
            tree[x].push_back(y);
            root[y] = x;
        }
        dfs(1);
        LL arr3[Size];///������򣬽����нڵ㰴Ȩֵ���򣬴����ǰ
        for(LL i=1;i<=n;++i)
        {
            arr3[i] = i;
        }
        sort(arr3+1,arr3+n+1,cmp);
        LL ans = 0;
        priority_queue<LL> q;///���ź���Ľڵ��������Ѽ������'Game'�л�õ�ֵ���������ź����������ڵ��й������ȣ�������ǰ��Ľڵ㵽�������ϵõ���ֵ�ĺ͸����ұ��vis�����Ӱ������ڵ�
        for(LL i=1;i<=n;++i)
        {
            LL tmp = arr3[i];
            LL tmp2 = dfs2(tmp);
            q.push(len[tmp] - tmp2);///����ֻ�ܱ�֤�й������ȵ�Ҷ�ӽڵ�һ�����ѵĽ���������ģ��ǹ������Ȳ�һ������˽�ÿ�������ĵ���ֵ�ĺʹ������ȶ��У�ȡǰK��
        }
        for(LL i=0;i<m;++i)
        {
            ans += q.top();
            q.pop();
            if(q.empty())
                break;
        }
        printf("Case #%d: ",++Case);
        printf("%I64d\n",ans);
    }
    return 0;
}
