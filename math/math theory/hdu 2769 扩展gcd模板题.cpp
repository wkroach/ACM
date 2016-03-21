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
int arr[210];
const int mod=10001;
typedef long long ll;
void ex_gcd(ll a,ll b,ll &t,ll &x,ll &y)
{
    if(!b) {t=a,x=1,y=0;}
    else {ex_gcd(b,a%b,t,y,x);y-=x*(a/b);}
}

int clu(ll a,ll b,ll x)
{
    return ((a*x)+b)%mod;
}
int main()
{
    ll n,a=0,b=0,g=0,t=0,k=0,judge=0;
    scanf("%d",&n);
    memset(arr,0,sizeof(arr));
    for(int i=1;i<=2*n-1;i+=2)
        scanf("%d",&arr[i]);
    for(int i=0;i<=10000;++i)
    {
        a=i;
        t=arr[3]-a*a*arr[1];
        ex_gcd(a+1,-1*mod,g,b,k);
        if(t%g) continue;
        else b*=(t/g);
        ll cur=0;
        judge=1;
        for(int j=2;j<=2*n;++j)
        {
            cur=clu(a,b,arr[j-1]);
            if(j&1)
            {
                if(cur!=arr[j]){
                    judge=0;
                    break;
                }
            }
            else
                arr[j]=cur;
        }
        if(judge) break;
    }
    for(int j=2;j<=2*n;j+=2)
        printf("%d\n",arr[j]);
    return 0;
}
