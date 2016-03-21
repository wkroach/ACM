#include<cstdio>
#include<cstdlib>
#include<time.h>
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

//#include<bits/c++std.h>

#define Size 100005
#define inf 2e9
#define INF 2e18
#define LL long long
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
LL n,m,k;

LL get_2(LL x)
{
    if(!x)
        return 0;
    return x/2 + get_2(x/2);
}

LL up(LL x)
{
    x++;
    if(x&1)
        return (x>>1)+1;
    return x>>1;
}

LL down(LL x)
{
    return (x-1)/2;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
//    int Case=0;
    cin>>t;
    while(t--)
//    cin>>n;
//    while(scanf("%I64d%I64d",&n,&m)==2)
    {
        cin>>n>>m;
        LL z = n - up(m);
        LL w = down(m);
        LL ans = get_2(z) - get_2(w) - get_2(z-w);
        if(ans)
        {
            cout<<0<<endl;
        }
        else
        {
            cout<<1<<endl;
        }
    }
    return 0;
}

/* 一个很冷但很吊的定理：strlin2(n,k) = combination(z,w) (mod 2) , z = n - ceil((k+1)/2) //四舍五入，k = floor((k-1)/2)
    之后就求组合数的2因子数是否存在，在即0，无即1*/
