//吴柯
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
#define ULL unsigned long long int
#define MOD 1000000007
#define N 1000005
#define INF 0x3f3f3f3f
#define seed 31
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int s[N],p[10005],n,m;
int Next[10005];
void  getnext()///生成Next数组
{
    int k=-1,j=0;
    Next[0]=-1;
    while(j<m-1)
    {
        if(k==-1||p[k]==p[j])
        {
            k++;
            j++;
           /// if(p[k]!=p[j])
             ///   Next[j]=k;
           /// else
              ///  Next[j]=Next[k];///优化后的getnext（）
            Next[j]=k;
        }
        else
            k=Next[k];
    }
}

int kmp()///kmp主算法
{
    int i=0,j=0;
    while(i<n&&j<m)
    {
        if(j==-1||s[i]==p[j])
        {
            i++;
            j++;
        }
        else
            j=Next[j];
    }
    if(j==m)
        return i-j+1;
    else
        return -1;
}

void init()
{
    memset(Next,0,sizeof(Next));
    memset(s,0,sizeof(s));
    memset(p,0,sizeof(p));
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    scanf("%d",&t);
    while(t--)
    {
        init();
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;++i)
            scanf("%d",&s[i]);
        for(int i=0;i<m;++i)
            scanf("%d",&p[i]);
        getnext();
        printf("%d\n",kmp());
    }
    return 0;
}
