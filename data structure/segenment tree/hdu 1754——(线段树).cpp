
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
LL n,m;
char ch;
LL a,b,ql,qr,c,d;
LL arr[200005];
LL Max[900000];
LL build(LL now,LL l,LL r)
{
    LL mid=l+(r-l)/2;
    if(l==r) Max[now]=arr[l];
    else
    {
        build (now*2,l,mid);
        build (now*2+1,mid+1,r);
        Max[now]=max(Max[now*2],Max[now*2+1]);
    }
}
LL push_up(LL now,LL l,LL r)
{
    LL mid=l+(r-l)/2;
    if(l==r) Max[now]=b;
    else
    {
        if(a<=mid) push_up(now*2,l,mid);
        else push_up(now*2+1,mid+1,r);
        Max[now]=max(Max[now*2],Max[now*2+1]);
    }
}
LL quire(LL now,LL l,LL r)
{
    LL ans=0;
    LL mid=l+(r-l)/2;
    if(ql<=l&&qr>=r) return Max[now];
    if(ql<=mid) ans=max(ans,quire(now*2,l,mid));
    if(qr>mid) ans=max(ans,quire(now*2+1,mid+1,r));
//    Max[now]=max(Max[now*2],Max[now*2+1]);
    return ans;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%I64d%I64d",&n,&m)==2)
    {
        memset(Max,0,sizeof(Max));
//        h=min(h,n);
        for(int i=1;i<=n;++i)
            scanf("%I64d",&arr[i]);
        build(1,1,n);
//        for(int i=1;i<=2*n-1;++i)
//            printf("%I64d ",Max[i]);
        for(int i=1;i<=m;++i)
        {
            getchar();///由于第一个输入的是字符，需要先用getchar吃掉回车
            scanf("%c%I64d%I64d",&ch,&c,&d);
//            printf("%c",ch);
            if(ch=='Q')
            {
                ql=c,qr=d;
                printf("%I64d\n",quire(1,1,n));
            }
            else if(ch=='U')
            {
                a=c,b=d;
                push_up(1,1,n);
            }
        }
//        printf("%I64d %c %I64d %I64d",m,ch,ql,qr);
    }
    return 0;
}

