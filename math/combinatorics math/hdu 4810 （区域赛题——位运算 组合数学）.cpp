
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
#define LL long long int
#define MOD 1000003
#define N 500005
LL comb[1005][1005];
LL arr[1005],bit[1005];
void init()
{
    comb[0][0]=1;
    for(int i=1;i<=1000;++i)
        comb[i][i]=comb[i][0]=1;
    for(int i=2;i<=1000;++i)
        for(int j=1;j<i;++j)
        {
            comb[i][j]=comb[i-1][j-1]%MOD+comb[i-1][j]%MOD;
            comb[i][j]%=MOD;
        }
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    init();
//    for(int i=0;i<=10;++i)
//    {
//        for(int j=0;j<=i;++j)
//            printf("%lld ",preu[i][j]);
//        puts("");
//    }
    int n;
    while(scanf("%d",&n)==1)
    {
        memset(bit,0,sizeof(bit));
        memset(arr,0,sizeof(arr));
        for(int i=1;i<=n;++i)
        {
            scanf("%I64d",&arr[i]);
            int cnt=0;
            LL m=arr[i];
            while(m)
            {
                if(m&1)
                    bit[cnt]++;
                cnt++;
                m>>=1;
            }
        }
        LL ans=0;
        for(int i=1;i<=n;++i)
        {
            ans=0;
            for(int j=0;j<32;++j)
                for(int k=1;k<=bit[j]&&k<=i;k+=2)
                {
                    ans=(ans+((1LL)<<j)%MOD*comb[bit[j]][k]%MOD*comb[n-bit[j]][i-k]%MOD)%MOD;
                }
            printf("%I64d",ans);
            if(i==n)
                printf("\n");
            else printf(" ");
        }

    }
    return 0;
}


