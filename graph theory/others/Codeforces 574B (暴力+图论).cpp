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
#define N 4005
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m;
vector <int> v[N];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int a,b;
    int c;
    int t;
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;++i)
            v[i].clear();
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&a,&b);
            v[a].push_back(b);
            v[b].push_back(a);
        }
        int ans=N;
        for(int i=1;i<=n;++i)///大暴力，因为m<=N，暴力最多循环m*m次，时间复杂度O(m^2)
        {
            int a1=i;
            for(int j=0;j<v[a1].size();++j)
            {
                int b1=v[i][j];
                for(int k=0;k<v[b1].size();++k)
                {
                    int c1=v[b1][k];
                    if(c1==a1) continue;
                    for(int d=0;d<v[c1].size();++d)
                    {
                        int d1=v[c1][d];
                        if(d1==a1)
                        {
//                            printf("%d\n",ans);
                            int len=v[a1].size()+v[b1].size()+v[c1].size()-6;
                            if(ans>len) ans=len;
                            break;
                        }
                        else
                            continue;
                    }

                }
            }
        }
        if(ans==N) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}
