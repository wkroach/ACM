#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cctype>//C常用头文件
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<iostream>
#include<sstream>//C++常用头文件
#define ll long long;
using namespace std;
int PowerMod(long long a, long long b, int c)
{
    int ans = 1;
    a = a % c;
    while(b)
    {
    if(b&1)
    ans = (ans * a) % c;
    b>>=1;
    a = (a * a) % c;
    }
    return ans;
}
int main()
{
    long long n,x,y,ans,c=1000000007;
    while(scanf("%I64d",&n)==1)
    {
        if(n==0){
            printf("1\n");
            goto there;
        }
        x=y=2;
        x=PowerMod(x,n-1,c);
        //y=PowerMod(y,2*n-1,c);
        y=(x%c)*(x%c)*2;
        x=(x+y)%c;
        printf("%I64d\n",x);
        there:;
    }
    return 0;
}
