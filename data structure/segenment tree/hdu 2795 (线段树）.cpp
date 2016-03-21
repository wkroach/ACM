
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
LL h,w,n,a;
LL Max[900020];
LL build(LL now,LL l,LL r)///ÿһ����Ϊһ���㣬Max[i]�д���߶����е�i���ڵ�ı�ʾ��Χ�����Ŀ��೤��
{
    LL mid=l+(r-l)/2;
    if(l==r) return Max[now]=w;
    else
    {
        build (now*2,l,mid);
        build (now*2+1,mid+1,r);
        Max[now]=max(Max[now*2],Max[now*2+1]);
    }
}
LL push_up(LL now,LL l,LL r)///��ѯ���󣬸��½ڵ�
{
    LL mid=l+(r-l)/2;
    if(l==r) Max[now]=Max[now]-a;
    else
    {
        if(Max[now*2]>=a) push_up(now*2,l,mid);
        else push_up(now*2+1,mid+1,r);
        Max[now]=max(Max[now*2],Max[now*2+1]);
    }
}
LL quire(LL now,LL l,LL r)///�ҵ�һ����a�����ڵĵ㣬��a���룬Max[i]�Ĵ�С��ΪMax[i]-a
{
    LL ans=0;
    LL mid=l+(r-l)/2;
    if(l==r) return ans=l;
    else
    {
        if(Max[now*2]>=a) ans = quire(now*2,l,mid);
        else ans = quire(now*2+1,mid+1,r);
    }
//    Max[now]=max(Max[now*2],Max[now*2+1]);
    return ans;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%I64d%I64d%I64d",&h,&w,&n)==3)
    {
        memset(Max,0,sizeof(Max));
        h=min(h,n);
        build(1,1,h);
//        for(int i=1;i<=2*n+1;++i)
//            printf("%d ",Max[1]);
        for(int i=0;i<n;++i)
        {
            scanf("%I64d",&a);
            if(a>Max[1])
            {
                printf("-1\n");
                continue;
            }
            printf("%I64d\n",quire(1,1,h));
            if(i!=n-1)
                push_up(1,1,h);
        }
    }
    return 0;
}

