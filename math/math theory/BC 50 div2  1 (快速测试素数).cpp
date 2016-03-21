//���
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
#define N 200005
#define MAX 1000000000
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int m,ql,qr,pos,val;
LL nn;

int arr[100005];
int prime[100005];
void init()///���ٲ������ķ�����1.�ȴ�һ��sqrt(N)��������
{
    int p=1;
    for(int i=2;i<=100000;++i)
    {
        if(!arr[i])
        {
            prime[p++]=i;
            for(int j=i*2;j<=100000;j+=i)
                arr[j]=1;
        }
    }
}

bool isgood(LL n)///2.������������ӵ�1ö�ٵ���sqrt(n)�������������һ��zhengc
///��ô�Ͳ�����������֮�������������ô��������
{
    for(int i=1;prime[i]<=sqrt(n);i++)
    {
        if(!(n%prime[i]))
            return false;
    }
    return true;
}
bool isprime(LL n)
{
    for(int i=3;i<=sqrt(n);i+=2)
    {
        if(!(n%i))
            return false;
    }
    return true;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    LL n;
//    for(LL i=2;i<=100;++i)
//        nn=i,
//        printf("%I64d ",fac(i-1));
    init();
    scanf("%d",&t);
    while(t--)
    {
       scanf("%I64d",&n);
//        if(!(n&1))
//            printf("0\n");
        if(n==3)
        {
            printf("2\n");
            continue;
        }
        if(n==4)
        {
            printf("2\n");
            continue;
        }
        if(n==2)
        {
            printf("1\n");
            continue;
        }
        if(isgood(n))
        {
            printf("%I64d\n",n-1);
        }
        else
            printf("0\n");
    }
    return 0;
}
