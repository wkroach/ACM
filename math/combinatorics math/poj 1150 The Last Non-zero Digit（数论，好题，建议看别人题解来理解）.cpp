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

int get2(int n)///��n�����ҳ��ܹ�2���ӵ���Ŀ
{
    if(n<2) return 0;
    return n/2+get2(n/2);
}

int get5(int n)///��n�����ҳ��ܹ�5���ӵ���Ŀ
{
    if(n<5) return 0;
    return n/5+ get5(n/5);
}

int g(int n, int x)///��n�������������ҳ��ܹ�ĩβΪx�ĳ�����Ŀ��xΪ1,3,7,9��
{
    if(n==0) return 0;
    return n/10 + (n%10 >= x) + g(n/5, x);
}

int getx(int n, int x)///��n�����ҳ��ܹ�ĩβΪx�ĳ��ִ�����xΪ1,3,7,9��
{
    if(n==0) return 0;
    return getx(n/2, x) + g(n, x);
}

int quick_pow(int x, int p, int mod)///������
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
        m = n-m;///�ҳ�n���루n-m)����3,7,9��β�Ĵ�����2,5�������Ĳ�ֵ
        int num2 = get2(n) - get2(m);
        int num5 = get5(n) - get5(m);
        int num3 = getx(n, 3) - getx(m, 3);
        int num7 = getx(n, 7) - getx(m, 7);
        int num9 = getx(n, 9) - getx(m, 9);
        if(num5>num2)///���5����Ŀ��2�࣬���һ����Ϊ0����һ����5
        {
            cout<<5<<endl;
            continue;
        }
        int ans = quick_pow(3, num3, 10) * quick_pow(7, num7, 10) * quick_pow(9, num9, 10);
        int tmp = num2 - num5;///ע��2���ܱ�5��
        ans = (ans * quick_pow(2,tmp,10))%10;///������϶������2
        cout << ans << endl;
    }
    return 0;
}







