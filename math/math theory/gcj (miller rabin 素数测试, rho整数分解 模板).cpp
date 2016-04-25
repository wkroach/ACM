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

#define Size 1000005
#define inf 2e9
#define INF 2e18
#define LL long long int
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define Max(a,b) (a)>(b)?(a):(b)
using namespace std;
int n,m,k;
int ql,qr,pos;
vector<LL> arr;

LL multi(LL a, LL b, LL mod)//���ٳ˷�ȡģ����ֹ�������������˱�LL
{
    LL ans = 0;
    a %= mod;
    while(b)//ԭ������������ƣ���һ����װ��Ϊ�����ƣ���λ��������
    {
        if(b&1)
        {
            ans = (ans + a) % mod;
        }
        b >>= 1;
        a = (a + a) % mod;
    }
    return ans;
}

LL QuickMod(LL a, LL b, LL mod)//�����˿��ٳ˷��Ŀ����ݣ���ֹ��LL
{
    if(b == 0)
        return 1;
    LL ans = 1;
    a %= mod;
    while(b)
    {
        if(b&1)
        {
            ans = multi(ans, a, mod);
        }
        b >>= 1;
        a = multi(a, a, mod);
    }
    return ans;
}

bool witness(LL a, LL n, LL x, int t)//�жϺ������ж��ǲ��Ǻ���������������ԭ��1. x*x = 1 mod(����),xֻ��Ϊ1��-1������Ϊ���� 2.x^n-1 = 1 mod n(����)������Ϊ1����һ����������
{
    LL tmp = QuickMod(a, x, n);
    LL tmp2 = tmp;
    for(int i=1; i <= t; ++i)
    {
        tmp = multi(tmp, tmp, n);
        if(tmp == 1 && tmp2 != 1 && tmp2 != n-1)
            return true;
        tmp2 = tmp;
    }
    if(tmp != 1)
        return true;
    return false;
}

bool miller_rabin(LL n, int s)//mr���㷨��sΪ���Դ�����Խ����ȷ��Խ�ߣ����Ӷ�ΪO(s*log(n))
{
    if(n<2)
        return false;
    if(n == 2)
        return true;
    if(!(n&1))
        return false;
    LL x = n - 1;
    int t = 0;
    while(!(x&1))//��n-1����x * 2^t����ʽ
    {
        t++;
        x >>= 1;
    }
    for(int i=0; i < s; ++i)
    {
        LL a = rand() % (n-1) + 1;
        if(witness(a, n, x, t))
            return false;
    }
    return true;
}

LL gcd(LL a, LL b)
{
    return b? gcd(b, a % b) : a;
}

LL pollard_rho(LL n, LL c)//rho���������ĳһ�����㷨������Ϊ1��n����cΪ���������
{
    LL i = 1, k = 2;
    LL x0 = rand() % (n - 1) + 1;
    LL y = x0;
    while(1)
    {
        i++;
        x0 = (multi(x0, x0, n) + c) % n;
        LL d = gcd((y - x0 + n) % n, n);
        if(d!=1 && d!=n)
            return d;
        if(y == x0)
            return n;
        if(i == k)
        {
            y = x0;
            k += k;
        }
    }
}

bool solve2(LL n)
{
    LL ans = n;
    while(ans >= n)
    {
        ans = pollard_rho(ans, rand() % (n-1) +1);
    }
    arr.push_back(ans);
}

bool solve(LL x)
{
    arr.clear();
    LL tmp = 0;
    LL ans = 0;
    LL x2 = x;
    vector<int> s;
    s.clear();
    while(x2)
    {
        s.push_back(x2 % 2);
        x2 /= 2;
    }
    for(int i=s.size()-1;i>=0;--i)
    {
        ans = ans*10 +s[i];
    }
    for(int i=2; i<=10; ++i)
    {
        for(int j=s.size()-1;j>=0;--j)
        {
            tmp = tmp*i + s[j];
        }
//        cout<<tmp<<endl;
        if(miller_rabin(tmp,20))
        {
//            cout<<tmp<<endl;
            return false;
        }
        solve2(tmp);
        tmp = 0;
        x2 = x;
    }
    cout<<ans<<" ";
    for(int i=0; i < arr.size(); ++i)
    {
        cout<<arr[i];
        if(i == arr.size() - 1)
            cout<<endl;
        else
            cout<<" ";
    }
    return true;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    srand(time(NULL));
    int Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        cin>>n>>k;
        printf("Case #%d:\n",++Case);
        int cnt = 0;
        LL start = (1LL<<(n-1)) + 1;
//        cout<<start<<endl;
        LL endt = 1LL<<(n);
//        cout<<start<<" "<<endt<<endl;
        for(LL i = start; i < endt; ++i)
        {
            if(!(i&1))
                continue;
            if(cnt == k)
                break;
            if(solve(i))
            {
                cnt++;
            }
        }
    }
    return 0;
}

