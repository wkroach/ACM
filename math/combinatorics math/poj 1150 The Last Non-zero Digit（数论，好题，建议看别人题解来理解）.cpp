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

#define Size 105
#define inf 2e9
#define INF 2e18
#define LL long long
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
int n,m,k;

const int spe_num = 2;
int solve(int n)
{
    if(n<spe_num) return 0;
    return n/spe_num+solve(n/spe_num);
}

int get2(int n)///在n！中找出总共2因子的数目
{
    if(n<2) return 0;
    return n/2+get2(n/2);
}

int get5(int n)///在n！中找出总共5因子的数目
{
    if(n<5) return 0;
    return n/5+ get5(n/5);
}

int g(int n, int x)///在n！的奇子列中找出总共末尾为x的出现数目（x为1,3,7,9）
{
    if(n==0) return 0;
    return n/10 + (n%10 >= x) + g(n/5, x);
}

int getx(int n, int x)///在n！中找出总共末尾为x的出现次数（x为1,3,7,9）
{
    if(n==0) return 0;
    return getx(n/2, x) + g(n, x);
}

int quick_pow(int x, int p, int mod)///快速幂
{
    int ans=1;
    if(x==1) return 1;
    if(x==0) return 0;
    while(p)
    {
        if(p&1)
        {
            ans *= x;
            ans %= mod;
        }
        x *= x;
        x %= mod;
        p>>=1;
    }
    return ans % mod;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int a,b;
//    int Case=0;
//    cin>>t;
//    while(t--)
//    cin>>n;
    while(scanf("%d%d",&n,&m)==2)
    {
        m = n-m;///找出n！与（n-m)！中3,7,9结尾的次数与2,5因子数的差值
        int num2 = get2(n) - get2(m);
        int num5 = get5(n) - get5(m);
        int num3 = getx(n, 3) - getx(m, 3);
        int num7 = getx(n, 7) - getx(m, 7);
        int num9 = getx(n, 9) - getx(m, 9);
        if(num5>num2)///如果5的数目比2多，最后一个不为0的数一定是5
        {
            cout<<5<<endl;
            continue;
        }
        int ans = quick_pow(3, num3, 10) * quick_pow(7, num7, 10) * quick_pow(9, num9, 10);
        int tmp = num2 - num5;///注意2可能比5多
        ans = (ans * quick_pow(2,tmp,10))%10;///最后算上多出来的2
        cout << ans << endl;
    }
    return 0;
}







