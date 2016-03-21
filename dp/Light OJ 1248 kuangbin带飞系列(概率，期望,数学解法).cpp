#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define eps 1e-9
#define N 50
#define M 50
#define INF 0x3f3f3f3f
using namespace std;


int n,m,t;

int main()
{
//    freopen("input.txt","r",stdin);
    scanf("%d",&t);
    int Case=1;
    while(t--)
    {
        double ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            ans+=(1.0*n/i);///数学表达式：ans=n*(1/1+1/2+1/3+1/4......+1/n)
        }
        printf("Case %d: ",Case++);
        printf("%lf\n",ans);
    }
    return 0;
}
