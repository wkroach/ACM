//Îâ¿Â
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
#define LL long long
#define MOD 1000000007
vector <int> tree[110];
int arr2[110],ans[110];
int n,k;
void dfs(int m)
{
        for(int i=0;i<tree[m].size();++i)
        {
            ans[m]++;
            dfs(tree[m][i]);
            ans[m]+=ans[tree[m][i]];
        }
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int a,b;
    int sum;
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        memset(arr2,0,sizeof(arr2));
        memset(ans,-1,sizeof(ans));
        if(n==1&&k!=0)
        {
            printf("0\n");
            continue;
        }
        else if(n==1&&k==0)
        {
            printf("1\n");
            continue;
        }
        for(int i=0;i<=n;++i)
            tree[i].clear();
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&a,&b);
            tree[a].push_back(b);
            arr2[b]=1;ans[a]=0;ans[b]=0;
        }
        int m;
        for(int i=1;i<=n;++i)
            if(arr2[i]!=1) m=i;
        dfs(m);
        sum=0;
        for(int i=1;i<=n;++i)
            if(ans[i]==k) sum++;
//        for(int i=1;i<=n;++i)
//            printf("%d ",ans[i]);
        printf("%d\n",sum);
    }
    return 0;
}
