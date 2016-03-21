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
#define LL long long int
#define MOD 1000000007
#define N 50005
int arr[N],sum[2*N+5];
int n,m,ql,qr,a,b;
int build(int x,int L,int R)
{
    int M=L+(R-L)/2;
    if(L==R) return sum[x]=arr[L];
    else{
        build(2*x,L,M);
        build(2*x+1,M+1,R);
        sum[x]=sum[2*x]+sum[2*x+1];
    }
}
int query(int x,int L,int R)
{
    int M=L+(R-L)/2;
    int ans=0;
    if(L>=ql&&R<=qr) return ans+=sum[x];
    if(M>=ql) ans+=query(2*x,L,M);
    if(M<qr) ans+=query(2*x+1,M+1,R);
    return ans;
}
void push_up(int x,int L,int R)
{
    int M=L+(R-L)/2;
    if(L==R) sum[x]+=b;
    else
    {
        if(a<=M) push_up(2*x,L,M);
        else push_up(2*x+1,M+1,R);
        sum[x]=sum[2*x]+sum[2*x+1];
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t,T;
    scanf("%d",&t);
    T=t;
    while(t--)
    {
        memset(sum,0,sizeof(sum));
        memset(arr,0,sizeof(arr));
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&arr[i]);
        build(1,1,n);
        printf("Case %d:\n",T-t);
        string s;
        cin >> s;
        while(s!="End")
        {
            scanf("%d%d",&a,&b);
            if(s=="Query")
                ql=a,qr=b,printf("%d\n",query(1,1,n));
            else if(s=="Add")
                push_up(1,1,n);
            else if(s=="Sub")
                b=-b,push_up(1,1,n);
            s.clear();
            cin >> s;
        }
    }
    return 0;
}


