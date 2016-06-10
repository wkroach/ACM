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

#define Size 400005
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

using namespace std;
LL n, m, k, mod;
LL ql, qr, pos;

///������ѧ������⣺
LL prime[Size + 10];///����
LL primePos[Size + 10];///������λ��
LL euler[Size + 10];///ŷ������
LL u[Size + 10];///Ī����˹����

void mathInit()///����ɸ������, ŷ������, Ī����˹���� (��Ԫ�����ú��������㣬�ʲ����ڴ˺�����)
{
    memset(prime,0,sizeof(prime));
    memset(euler,0,sizeof(euler));
    euler[1] = 1;
    memset(u,0,sizeof(u));
    u[1] = 1; ///u[1] = 1; u[n] = (-1)^k (n = p1p2p3...pk); �������u[n] = 0
    for(LL i=2; i <= Size; ++i)
    {
        if(!prime[i])
        {
            prime[++prime[0]] = i;
            euler[i] = i - 1;///������ŷ������Ϊ�Լ���һ
            u[i] = -1;
            primePos[i] = prime[0];///��¼������λ��
        }
        for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
        {
            prime[i * prime[j]] = 1;
            if(i % prime[j] == 0)
            {
                euler[i * prime[j]] = euler[i] * prime[j];///���i�ķֽ���p^k��k>=1����p|i��
                /// ��ô����euler[p^k] = (p-1)*p^(k-1),����euler[i*p] = euler[i]*p;
                u[i * prime[j]] = 0; ///i * p�д���p���ݴ���1
                break;
            }
            else
            {
                euler[i * prime[j]] = euler[i] * (prime[j] - 1);
                /// ��֮����i��p���ʣ�euler[i * p] = euler[i]*euler[p] = euler[i]*(p-1)
                u[i * prime[j]] = -u[i]; /// ������ż�ԣ�ֱ��ȡ��
            }
        }
    }
}



///���ú�����

LL gcd(LL a,LL b)//gcd
{
    return b == 0?a:gcd(b,a%b);
}

LL multi(LL a, LL b, LL mod)//���ٳ˷�ȡģ����ֹ�������������˱�LL, �ٶȱ�ԭ���˷�Ҫ��
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

LL quickMod(LL a, LL b, LL mod)//���ڿ��ٳ˷�ȡģ�Ŀ�����ȡģ
///�ص㣡������������ܹ��ĳ�int��������ĿҪ��һ��Ҫ�ģ��ٶȱ�LL������
{
    if(b == 0)
        return 1%mod;
    LL c = a%mod;
    LL ans = 1;
    while(b)
    {
        if(b&1)
        {
//            ans = multi(ans,c,mod);//������ĿҪ��ѡ��˷���ʽ
            ans = ans * c % mod;
        }
//        c = multi(c,c,mod);
        c = c * c % mod;
        b >>= 1;
    }
    return ans;
}

LL exGcd(LL a, LL b, LL &x, LL &y)///��չŷ����ã�����a b��gcd��x��y�ֱ�Ϊa b��ϵ��
{
    if(a==0&&b==0) return -1;
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    else
    {
       LL tmp = exGcd(b,a%b,y,x);
       y-=x*(a/b);
       return tmp;
    }
}

///�˷���Ԫ��

    ///ֱ������Ԫ��
    LL modInverPrime(LL a, LL mod)///�˷���Ԫ �����ݷ�������mod������ʱ��Ч
    {
        return quickMod(a,mod-2,mod);
    }

    LL modInver(LL a, LL mod)///�˷���Ԫ ��չŷ����÷�������mod������������a ����ʹ��Ч
    {
        LL x,y,g;
        LL gcd = exGcd(a,mod,x,y);
        if(gcd == 1)
            return (x%mod+mod)%mod;
        return -1;
    }

    ///ɸ����1~Size֮��������Ԫ
    LL inv[Size];

    LL inverInitPrime(LL mod)///����ɸ��Ԫ����ͬʱɸ�����Ļ�����ɸ����Ԫ
    {
        memset(prime,0,sizeof(prime));
        inv[1] = 1 % mod;
        for(LL i=2; i <= Size; ++i)
        {
            if(!prime[i])
            {
                prime[++prime[0]] = i;
                inv[i] = modInverPrime(i, mod);
            }
            for(LL j = 1; j <= prime[0] && prime[j] <= Size / i; ++j)
            {
                prime[i * prime[j]] = 1;
                inv[i * prime[j]] = inv[i] * inv[prime[j]] % mod;
                if(i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    }

    LL inverInit(LL mod)///������������������������Ԫ
    {
        LL cnt = 0;///cnt��ʾ��ǰ��֮ǰ�ж��ٸ�����
        inv[1] = 1;
        for(LL i = 2; i <= Size; ++i)
        {
            if(primePos[i])///����������λ���ж��Ƿ�Ϊ������ͬʱ����cnt
            {
                cnt = primePos[i];
                inv[i] = modInverPrime(i, mod);
            }
            for(LL j = 1; j <= cnt && prime[j] <= Size / i; ++j)
            {
                inv[i * prime[j]] = inv[i] * inv[prime[j]] % mod;
                if(i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    }

    ///��ǿ��ʽ��������ɸ1~mod�����ж�mod����Ԫ��pΪ������
    LL inverInit_ex(LL mod)
    {
        inv[1] = 1;
        for(LL i = 2; i <= mod; ++i)
        {
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
    }


///�����ȡģ��

    ///�����
//    LL facMod[Size + 10][Size];///Size < 1e4
//    LL facInver[Size + 10][Size];
//
//    void facModInit()///�����˽׳˶�С��Size������ȡģ��׳���Ԫ�����Ӷ�O(nlog(n)log(n))
//    {
//        for(LL i = 1; i <= prime[0]; ++i)
//        {
//            facMod[i][0] = facInver[i][0] = 1;
//            for(LL j = 1; j <= prime[i]; ++j)
//            {
//                facMod[i][j] = (facMod[i][j - 1] * j) % prime[i];
//                facInver[i][j] = modInverPrime(facMod[i][j], prime[i]);
//            }
//        }
//    }
    ///ֱ�����
    LL com(LL n, LL m, LL mod)///�����ȡģ��ֱ�Ӽ���汾������n��m ��Сʱ����Ч ���Ӷ�O(m)
    {
        if(m > n)
            return 0;
        LL ans = 1;
        for(LL i = 1; i <= m; ++i)
        {
            LL a = (n + i -m) % mod;
            LL b = i % mod;
            ans = ans * (a * modInverPrime(b, mod) % mod) % mod; ///mod������
    //        ans = ans * (a * modInver(b, mod) % mod) % mod; ///mod��������
        }
        return ans;
    }

//    LL com_init(LL n, LL m, LL mod)///�����Ѿ���õı����汾, n,mҪС��mod, ���Ӷ�O(1)
//    {
//        if(m > n)
//            return 0;
//        LL t = primePos[mod];
//        return facMod[t][n] * (facInver[t][n-m] * facInver[t][m] % mod) % mod;
//    }

    ///lucas����
    LL lucas(LL n, LL m,LL mod)///����lucas����������ȡģ������n��m�ϴ�ʱ��Ч�����Ӷ�O(mod*log(m)), ��mod�ǳ���ʱ��Ч
    {
        if(m == 0)
            return 1;
        return com(n % mod, m % mod, mod) * lucas(n / mod, m / mod, mod) % mod;
    }

//    LL lucas_init(LL n, LL m, LL mod)///�����Ѿ���õı����lucas�����Ӷ�O(log(m))
//    {
//        if(m == 0)
//            return 1;
//        return com_init(n % mod, m % mod, mod) * lucas_init(n / mod, m / mod, mod) % mod;
//    }

    ///�����ֽⷨ��
    LL facFactor(LL n, LL p)///��n�Ľ׳˵�������p�ĸ��������ü�����˼����O(log(n))
    {
        LL ans = 0;
        while(n)
        {
            ans += n / p;///ÿ��ͳ��n�ķ�Χ��p�ı���������p^i��Ϊ���ӵ����ĸ���
            n /= p;///ÿ����Сn�Ĺ�ģ���ȼ���i++��ͳ��p�ĸ��ߴ��ݵı�����
        }
        return ans;
    }

    LL com_nprime(LL n, LL m, LL mod)///����mod��������ʱ���������ģ�ĽⷨO(n),����n<1e8��Ч����ΪҪ��n��Χ��������
    {
        LL ans = 1;
        for(LL i = 1; i <= prime[0] && prime[i] <= n; ++i)
        {
            LL x = facFactor(n, prime[i]);
            LL y = facFactor(n - m, prime[i]);
            LL z = facFactor(m, prime[i]);
            x -= (y + z);
            ans *= quickMod(prime[i], x, mod);
            ans %= mod;
        }
        return ans;
    }

///���������ӣ�
    //ֱ�Ӽ��㣺
    vector<LL> factors;
    void getFactors(LL n)///����sqrt(n)��Χ�ڵ������������n��������
    {
        factors.clear();
        LL tmp = n;
        for(LL i = 1; i <= prime[0] && prime[i] <= n / prime[i]; ++i)
        {
            if(tmp % prime[i] == 0)
            {
                factors.push_back(prime[i]);
            }
            while(tmp % prime[i] == 0)///���ڴ���sqrt(n)�󻹿�����Ψһ�Ľϴ�������ӣ����ǰ���������Ҫ���ɾ�
            {
                tmp /= prime[i];
            }
        }
        if(tmp != 1)///���Ľ������Ϊ1��˵�����������ӣ�Ҫ����
        {
            factors.push_back(tmp);
        }
    }

///�����͹�ʽ��
    /// 1^k + 2^k + 3^k +.....n^k �ĺͶ�mod��ģ��ʽ������
    /// �Ƶ����������cxlove�Ĳ���

    LL sumPow2(LL n, LL mod)///����1^2 + 2^2 + 3^2 +.......n^2 �ĺͶ�mod��ģ
    ///��ʽ��n*(n+1)*(2*n+1)/6;
    {
        LL ans = n;
        ans = ans * (n + 1) % mod;
        ans = ans * (2 * n + 1) % mod;
        return ans * modInverPrime(6, mod) % mod;
    }

    LL sumPow3(LL n, LL mod)///����1^3 + 2^3 + 3^3 +.......n^3 �ĺͶ�mod��ģ
    ///��ʽ��n^2*(n+1)^2/4
    {
        LL ans = 1;
        ans = n * n % mod;
        ans = (ans * (n + 1) % mod) * (n + 1) % mod;
        return ans * modInverPrime(4, mod) % mod;
    }

    LL sumPow4(LL n, LL mod)///����1^4 + 2^4 + 3^4 +.......n^4 �ĺͶ�mod��ģ
    ///��ʽ��(n*(n+1)*(2*n+1)*(3*n^2+3*n-1))/30
    {
        LL ans = 1;
        ans = n * (n + 1) % mod;
        ans = ans * (2 * n + 1) % mod;
        ans = ans * (3 * quickMod(n, 2, mod) + 3 * n % mod - 1) % mod;
        return ans * modInverPrime(30, mod) % mod;
    }

///��Ŀ���룺

LL solve(LL n)
{
    LL ans = 0;
    LL tmp3 = 0;
    for(LL i = 1; i < (1 << factors.size()); ++i)
    {
        LL cnt = 0;
        LL tmp2 = 1;
        for(LL j = 0; j < factors.size(); ++j)
        {
            LL tmp = 1 << j;
            if(tmp & i)
            {
                cnt++;
                tmp2 *= factors[j];///ͳ�Ƶ�ǰ״̬�������ӵĳ˻�
            }
        }
        if(cnt & 1)
        {
            tmp3 = n / tmp2;///��ʾn�ķ�Χ���ж��������˻��ı�������Ҫ�����ݳ����Щ��
            ans += tmp3;
        }
        else
        {
            tmp3 = n / tmp2;
            ans -= tmp3;
        }
    }
    return n - ans;
}

LL solveBetween(LL a, LL b, LL n)///���a,b(�����䣩֮����n���ʵ����ĺ�
{
    LL ans1 = 0, ans2 = 0;
    LL tmp3 = 0;
    for(LL i = 1; i < (1 << factors.size()); ++i)
    {
        LL cnt = 0;
        LL tmp2 = 1;
        LL tmp3 = 0;
        for(LL j = 0; j < factors.size(); ++j)
        {
            LL tmp = 1 << j;
            if(tmp & i)
            {
                cnt++;
                tmp2 *= factors[j];///ͳ�Ƶ�ǰ״̬�������ӵĳ˻�
            }
        }
        if(cnt & 1)
        {
            tmp3 = (a - 1) / tmp2;
            ans1 += tmp3 * (tmp3 + 1) / 2 * tmp2;
            tmp3 = b / tmp2;
            ans2 += tmp3 * (tmp3 + 1) / 2 * tmp2;
        }
        else
        {
            tmp3 = (a - 1) / tmp2;
            ans1 -= tmp3 * (tmp3 + 1) / 2 * tmp2;
            tmp3 = b / tmp2;
            ans2 -= tmp3 * (tmp3 + 1) / 2 * tmp2;
        }
    }
    ans1 = (a - 1) * a / 2 - ans1;
    ans2 = b * (b + 1) / 2 - ans2;
    return ans2 - ans1;
}

LL binarySolve(LL s, LL e, LL n, LL x)///���ִ𰸣����ڿ�����һ�������ڵ�������������ͬ��Ҫ���Ŀ�����䣬�ٴӺ���ǰ�ҵ���n���ʵ�������
{
    LL pre = s;
    LL mid = 0;
    if(solve(e) < x)
    {
        return 0;
    }
    while(s < e)
    {
        mid = (s + e) / 2;
        LL tmp = solve(mid);
        if(tmp < x)
        {
            pre = s;
            s = mid + 1;
        }
        else if(tmp >= x)
        {
            e = mid;
        }
    }
    for(LL i = s; i >= pre; --i)
    {
        if(gcd(i, n) == 1)
        {
            return i;
        }
    }
    return 0;
}

///��Ŀ���룺

struct Rec///�����࣬����
{
    LL x1, x2, y1, y2;
    Rec():x1(0), x2(0), y1(0), y2(0) {}

    LL area()///���
    {
        if(x1 >= x2 || y1 >= y2)
        {
            return 0;
        }
        return (y2 - y1) * (x2 - x1);
    }

    Rec interRec(const Rec& b)const///�������������ཻ����
    {
        Rec ans;
        if(x2 <= b.x1 || y2 <= b.y1 || b.x2 <= x1 || b.y2 <= y1)
        {
            return ans;
        }
        ans.x1 = max(x1, b.x1);
        ans.y1 = max(y1, b.y1);
        ans.x2 = min(x2, b.x2);
        ans.y2 = min(y2, b.y2);
        return ans;
    }
};

LL arr[25];
Rec arr2[25];

LL dfsRec(LL& ans, LL cur, Rec inter, LL flag)
{
    Rec tmp = arr2[arr[cur]].interRec(inter);
    if(tmp.area() == 0)///ע�⣬Ҫ���������ι�����������ĳһ�������Ϊ0������������
        return 0;
    if(flag & 1)
    {
        ans += tmp.area();
    }
    else
    {
        ans -= tmp.area();
    }
    for(LL i = cur + 1; i <= k; ++i)
    {
        dfsRec(ans, i, tmp, flag + 1);
    }
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
//    mathInit();
//    cin>>t;
//    while(t--)
    while(scanf("%I64d%I64d",&n, &m) == 2 && (m + n))
    {
        printf("Case %I64d:\n", ++Case);
        LL ans = 0;
//        scanf("%I64d%I64d",&n, &m);
        Rec s;
        s.x1 = s.y1 = 0;
        s.x2 = s.y2 = 1005;
        for(LL i = 1; i <= 20; ++i)
        {
            arr2[i] = Rec();
        }
        for(LL i = 1; i <= n; ++i)
        {
            scanf("%I64d%I64d%I64d%I64d",&arr2[i].x1, &arr2[i].y1, &arr2[i].x2, &arr2[i].y2);
        }
        for(LL i = 1; i <= m; ++i)///���ھ�����Ŀ���٣����������ݳ⣬�����֦��λ�����޷���֦
        {
            memset(arr,0,sizeof(arr));
            scanf("%I64d",&k);
            for(LL j = 1; j <= k; ++j)
            {
                scanf("%I64d",&arr[j]);
            }
            LL ans = 0;
            for(LL j = 1; j <= k; ++j)
            {
                dfsRec(ans, j, s, 1);
            }
            printf("Query %I64d: %I64d\n", i, ans);
        }
        printf("\n");
//        printf("Case #%I64d: ", ++Case);
//        printf("%I64d\n",ans);

    }
    return 0;
}
