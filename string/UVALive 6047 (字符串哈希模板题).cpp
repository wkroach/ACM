
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
#define MOD 1000000007
#define N 100005
#define seed 31
#define ULL unsigned long long int
ULL k[100005];
ULL Hash[100005];
ULL Hash2[100005];
char s[1005][1005];
char ss[1005];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int m,l;
    int t,n;
    k[0]=1;
    for(int i=1;i<1005;++i)
        k[i]=k[i-1]*seed;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(s,0,sizeof(s));
        memset(Hash,0,sizeof(Hash));
        memset(Hash2,0,sizeof(Hash2));
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            if(i==0) getchar();
            gets(s[i]);
            int len=strlen(s[i]);
            for(int j=0;j<=len-1;++j)
                Hash[i]+=(s[i][j]-'a'+1)*k[len-1-j];
            for(int j=len-1;j>=0;--j)
                Hash2[i]+=(s[i][j]-'a'+1)*k[j];
        }
        printf("Case #%d: ",T-t);
        if(n==1)
        {
            printf("0\n");
            continue;
        }
        int sum=0;
        for(int i=0;i<n-1;++i)
            for(int j=i+1;j<n;++j)
            {
                int len1=strlen(s[j]),len2=strlen(s[i]);
                if(Hash[i]*k[len1]+Hash[j]==Hash2[j]*k[len2]+Hash2[i])
                    sum++;
                if(Hash[j]*k[len2]+Hash[i]==Hash2[i]*k[len1]+Hash2[j])
                    sum++;
            }
        printf("%d\n",sum);
    }
    return 0;
}

