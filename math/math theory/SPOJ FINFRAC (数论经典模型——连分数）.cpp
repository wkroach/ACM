
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

LL dfs(LL a,LL b,LL c,LL d)
{
    if(a<b&&c>d)
        return 1;
    else if(a<b&&c<=d)
        return dfs(d,c,b,a)*d/c+1;
    else if(a>=b)
    {
        LL k=a/b;
        return dfs(a-k*b,b,c-k*d,d);
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    LL a,b,c,d,p,q;
    while(scanf("%lld%lld%lld%lld",&a,&b,&c,&d)==4)
    {
        q=dfs(a,b,c,d);
        p=q*a/b+1;
        printf("%lld/%lld\n",p,q);
    }
    return 0;
}
///explaination:

///If a/b < 1 and c/d > 1 the answer is p = q = 1.
///If [a/b]+1 < c/d, the answer is p = [a/b]+1, q = 1.
///If a < b, transform the inequalities like this: d/c < q/p < b/a.

///Otherwise, we need this reduction:
///a/b < p/q < c/d
///a/b - 1 < p/q - 1 < c/d - 1
///(a-b)/b < (p-q)/q < (c-d)/d

///Or, to speed things up, let k = [a/b] = [c/d]
///a/b < p/q < c/d
///a/b - k < p/q - k < c/d - k
///(a-kb)/b < (p-kq)/q < (c-kd)/d , p-kq=[(a-kb)/b]+1=0+1 -> p=kq+1;

///input statistic
/*1 3 1 2
2 1 3 1
2 1 4 1
1000 1001 1001 1002
100000 1 1000000 2
3 2 2 1
9999999 10000000 10000001 10000000
5 1 50000001 10000000
1 10000000 1 1
50000000 10000000 50000001 10000000
10000003 10000000 10000004 10000000*/

