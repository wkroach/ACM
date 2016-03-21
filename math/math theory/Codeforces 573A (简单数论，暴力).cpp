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
#define N 100005
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m;
ULL arr[N];
ULL tmp;
ULL gcd(ULL a,ULL b)
{
    return b==0?a:gcd(b,a%b);
}

ULL lcm(ULL a,ULL b)
{
    return a/gcd(a,b)*b;
}

ULL judge(ULL a)
{
    ULL cnt=a;
//    printf("%I64u ",cnt);
    if(cnt==1) return 1;
    while(cnt)
    {
        if(cnt%2==0)
            cnt/=2;
        else
            break;
    }
    if(cnt==1) return 1;
    while(cnt)
    {
        if(cnt%3==0)
            cnt/=3;
        else
            break;
    }
    if(cnt==1) return 1;
//    printf("%I64u ",cnt);
    return cnt;
}

bool good(ULL a)
{
    if(a==1) return true;
    if(a==2) return true;
    if(a==3) return true;
    return false;
}
bool judge(ULL a,ULL b)
{
    ULL g=gcd(a,b);
    ULL a1=a/g;
    ULL a2=b/g;
    if(good(a1)&&good(a2))
        return true;
    return false;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int a,b;
    int c;
    int t;
    while(scanf("%d",&n)==1)
    {
        memset(arr,0,sizeof(arr));
        for(int i=0;i<n;++i)
        {
            scanf("%I64u",&arr[i]);
            arr[i]=judge(arr[i]);
        }
        tmp=arr[0];
        for(int i=0;i<n-1;++i)
        {
//            printf("%I64u\n",gcd(arr[i],arr[i+1]));
            tmp=lcm(tmp,arr[i+1]);
        }
//        printf("%I64u ",tmp);
        int flag=1;
        for(int i=0;i<n;++i)
        {
//            printf("%I64d ",flag);
            arr[i]=tmp/arr[i];
            if(judge(arr[i])!=1)
            {
                flag=0;
                break;
            }
        }
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
