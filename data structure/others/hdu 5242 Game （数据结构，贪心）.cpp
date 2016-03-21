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
vector<LL> tree[Size];///正向建树
LL root[Size];///反向建边，记录当前节点的父节点是谁
LL len[Size];///记录从当前节点到根节点的权值
LL vis[Size];///记录当前节点是否访问过


bool cmp(LL a,LL b)
{
    return len[a]>len[b];
}


void dfs(LL x)///递归记录每个节点的权值
{
    for(LL i=0;i<tree[x].size();++i)
    {
        len[tree[x][i]] += len[x];
        dfs(tree[x][i]);
    }
}

LL dfs2(LL x)///递归访问并标记节点，直至遇到访问过的节点
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
        LL arr3[Size];///间接排序，将所有节点按权值排序，大的在前
        for(LL i=1;i<=n;++i)
        {
            arr3[i] = i;
        }
        sort(arr3+1,arr3+n+1,cmp);
        LL ans = 0;
        priority_queue<LL> q;///对排好序的节点依次深搜计算这次'Game'中获得的值，由于已排好序，若两个节点有公共祖先，则排在前面的节点到根的链上得到的值的和更大，且标记vis数组后不影响后续节点
        for(LL i=1;i<=n;++i)
        {
            LL tmp = arr3[i];
            LL tmp2 = dfs2(tmp);
            q.push(len[tmp] - tmp2);///由于只能保证有公共祖先的叶子节点一次深搜的结果是上升的，非公共祖先不一定，因此将每次搜链的到的值的和存入优先队列，取前K个
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
