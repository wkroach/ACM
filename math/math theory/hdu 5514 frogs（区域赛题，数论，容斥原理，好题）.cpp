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
#define LL long long int
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
///ע�������ȫ��ʹ����long long ��û��ʹ��int
using namespace std;
LL n,m,k;
LL ql,qr,pos;

vector<LL>factors;
LL vis[Size];
LL num[Size];

LL gcd(LL a,LL b)
{
    return b == 0?a:gcd(b,a%b);
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        factors.clear();
        memset(vis,0,sizeof(vis));
        memset(num,0,sizeof(num));

        scanf("%lld%lld",&n,&m);
        for(LL i=1; i * i <= m; ++i)//Ҫͳ�������߹���ʯͷ��ֻ��ͳ��m����������Щ��gcd(x,m)�������������Щ���ӵı������������кͼ��ɣ��ǵ�ȥ��m����
        {
            if(!(m%i))
            {
                factors.push_back(i);
                if(i * i != m)
                {
                    factors.push_back((m/i));
                }
            }
        }
        sort(factors.begin(),factors.end());
        factors.pop_back();

        LL ans = 0;
        for(LL i=0;i<n;++i)//�������ӿ��ܱ��ظ�ͳ�ƣ�Ҫ�����ݳ��˼�룬��¼ÿ��Ҫ��ͳ�ƵĴ����Լ�ʵ��
        {
            LL x;
            scanf("%lld",&x);
            LL tmp = gcd(x,m);
            for(LL j = 0;j<factors.size();++j)
            {
                if(factors[j] % tmp == 0)///�ص㣡��������������Լ���Ĺ�Լ��һ��Ҳ��m��Լ��
                                        ///����С��m������һ������һ�����߹����Σ�����������Լ�����߹�����ôһ��Ҳ������Լ���Ĺ�Լ��������Լ���ұ��߹���
                                        ///�ұ�ͳ�ƹ����Σ����Ҫ����������������Լ��ͨͬ���ݳ�ԭ��
                {
                    vis[j] = 1;
                }
            }
        }
            for(LL j=0;j < factors.size();++j)
            {
                    if(vis[j] == num[j])
                        continue;
                    LL t = (m-1)/factors[j];
                    ans += (t*(t+1) / 2 * factors[j] * (vis[j] - num[j]));//ͳ�����������С��m�ķ�Χ�ڵı���֮�ͣ��������ظ�����Ĵ��������ݳ�
                    LL tmp2 = vis[j] - num[j];
                    for(LL k = j; k < factors.size(); ++k)
                    {
                        if(factors[k] % factors[j] == 0)
                            num[k] += tmp2;//�����ظ���¼����
                    }
            }
        printf("Case #%lld: %lld\n",++Case,ans);
    }
    return 0;
}
