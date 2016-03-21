//吴柯
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
#define N 105
#define M 100005
#define MAX 1000000000
int n,m,ans;
int f[N],sg[M];
///SG函数，具体参见丰神的模板
int SG_dfs(int x)
{
    int i;
    if(sg[x]!=-1)
        return sg[x];
    bool mex[N];
    memset(mex,0,sizeof(mex));
    for(i=0;i<n&&x>=f[i];i++)
    {
        if(sg[x-f[i]]==-1)
            SG_dfs(x-f[i]);
        mex[sg[x-f[i]]]=1;
    }
    int e;
    for(i=0;;i++)
        if(!mex[i])
            return sg[x]=i;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d",&n)==1&&n)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&f[i]);
        sort(f,f+n);
        memset(sg,-1,sizeof(sg));
        sg[0]=0;
        scanf("%d",&m);
        while(m--)
        {
            int m2,t;
            ans=0;
            scanf("%d",&m2);
            for(int i=0;i<m2;++i)
            {
                scanf("%d",&t);
                sg[t]=SG_dfs(t);
                ans^=sg[t];
            }
            if(ans)
                printf("W");
            else printf("L");
        }
        puts("");
    }
    return 0;
}

