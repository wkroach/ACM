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
#define MOD 1000003
#define N 1000000000000
LL r,k,n;
LL arr[40][1000005],arr2[40];
LL quick(LL a,LL b)
{
    LL c=1;
    if(b==0) return 1;
    while(b)
    {
        if(b&1) c*=a;
        a*=a;
        b>>=1;
    }
    return c;
}
LL cal(LL k,LL r)
{
    return k*(quick(k,r)-1)/(k-1);
}
LL b_search(LL a,LL b,LL n,LL r)
{
    LL s=a,e=b,mid=s+(b-s)/2;
    while(s<e)
    {
        mid=s+(e-s)/2;
        if(n==arr[r][mid]) return mid;
        if(n<arr[r][mid]) e=mid;
        else if(n>arr[r][mid]) s=mid+1;
    }
    return 0;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    ///打表，找到第一个大于1e6的值并再用一个数组标记位置
    for(int i=1;i<40;++i)
    {
        arr[i][1]=1;
        for(int j=2;j<=1000000;++j)
        {
            LL k=cal(j,i);
            arr[i][j]=k;
            if(k>=N)
            {
                arr2[i]=j;
                break;
            }
        }
    }
//    for(int i=1;i<40;++i)
//    {
//        for(int j=1;j<10;++j)
//            printf("%lld ",arr[i][j]);
//        puts("");
//    }
//    for(int i=1;i<40;++i)
//        printf("%lld ",arr2[i]);
    while(scanf("%lld",&n)==1)
    {
        LL mk=n-1,mr=1,ans=n-1,sum;
        for(r=2;r<40;++r)
        {
            LL tmp;
            tmp=b_search(1,arr2[r],n-1,r);///二分查找
            if(tmp)
            {
                sum=tmp*r;
                if(ans>sum)
                {
                    mk=tmp;
                    mr=r;
                    ans=sum;
                }
            }
            else
            {
                tmp=b_search(1,arr2[r],n,r);
                if(tmp)
                {
                    sum=tmp*r;
                    if(ans>sum)
                    {
                        mk=tmp;
                        mr=r;
                        ans=sum;
                    }
                }
            }
        }
        printf("%lld %lld\n",mr,mk);
    }
    return 0;
}


