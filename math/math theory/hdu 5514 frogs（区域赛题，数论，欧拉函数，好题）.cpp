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

#define Size 100050
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
int prime[Size];
int Euler[100050];
vector<int> frogs;

int gcd (int a,int b)
{
    return b == 0? a: gcd(b,a%b);
}

void euler()///ŷ��ɸ�����Ӷ�O(nloglogn)
{
    memset(Euler,0,sizeof(Euler));
    Euler[1] = 1;
    for(int i = 2; i <= 100010; ++i)
    {
        if(!Euler[i])
        {
            for(int j = i; j <= 100010; j += i)
            {
                if(!Euler[j])
                    Euler[j] = j;
                Euler[j] = Euler[j] / i *(i-1);
            }
        }
    }
}

LL getEuler (LL n)
{
    LL ans = n;
    for(LL i = 2; i * i <= n; ++i)
    {
        if( !(n%i) )
        {
            while( !(n % i))
                n /= i;
            ans = ans / i * (i-1);
        }

    }
    if(n > 1)
        ans = ans / n * (n-1);
    return ans;
}

bool good(int x)
{
    for(int i=0;i<frogs.size();++i)
    {
        if(x % frogs[i] == 0)
            return true;
    }
    return false;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int a,b,c,d;
    int Case=0;
//    prime_init();
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        frogs.clear();
        scanf("%d%d",&n,&m);
        int frog;
        LL ans = 0;
        int fac;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&frog);
            frogs.push_back(gcd(frog,m)); //�ص�3��frog�����ߵ���ʯͷ���ض�����gcd(frog,m)Ϊ������ʯͷ�������ʯͷ�ı��a%gcd(frog,m) == 0, ��m % gcd(frog,m) == 0, ���gcd(a,m) % gcd(frog,m) == 0
        }
        for(int i=1; i * i <= m; ++i)//��ˣ�ֻ��ö��m���е�Լ�����Դ���Ϊgcd�ļ����У����Ǹ��ȼۻ��֣���Ϊ�������������Լ��Ψһ�����жϵ�ǰԼ���Ƿ�frog�ȵ�������һ�¶������������������ĺ�
        {
           if(m % i == 0)
           {
               fac = i;
               if(good(fac))// �ص�1����ģn����n��gΪgcd������С��n����x���ڵļ��ϣ���Ϊn����g���ģ��������(n/g)���ʵ�������phi(n/g)�ļ��ϣ���Ϊgcd(x,n) == g, �����߳�g���޸���Լ������˳���g�����µ����ض����ʣ�����g��Ϊgcd��
               {
                   ans += (getEuler((LL)(m/fac)) * (LL)m / 2); // �ص�2������!!!!!!!!!��С��x����x���ʵ�����ģx����Ԫ�ļ����У��ĺ� = phi(x) * x / 2,
                                                                //֤�������a �� x���ʣ���ôx - aҲ��x���ʣ���֤���ɣ�����ô�ɶԵĿ���Ԫ���Ϊx���ܵĹ�ģΪphi(x),��λ�������ٳ���2���ƵĴ�ʽ
               }
               fac = m/i;
               if(i * i == m || i == 1)
               {
                   continue;
               }
               if(good(fac))
               {
                   ans += (getEuler((LL)(i)) * (LL)m / 2);
               }
           }
        }
        printf("Case #%d: %I64d\n",++Case,ans);
    }
    return 0;
}

