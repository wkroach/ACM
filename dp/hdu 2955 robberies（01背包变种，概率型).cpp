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
using namespace std;
int n,m,k;
int ql,qr,pos;
double dp2[20005];
vector<int> arr;
vector<double> arr2;
double p;
void zero_one_pack(int n, int v, int c, int w, double pol)///01�����ı��ΰ汾������Ʒ�ļ�ֵ������������������Ʒ��ֵ���������ӳ��ĸ�������ֵ
{
    for(int i=v;i>=c;--i)///��֤�����ӽṹ���ӳ����������ô�����Ϊ���ʴ���p�ı����������������Ʒ�ļ�ֵ��
    {
        if(dp2[i - c] * pol > dp2[i])
        {
            dp2[i] = dp2[i-c] * pol;
        }
    }
    /* һ�ֵ��͵Ĵ���ⷨ�����ı�ԭʼ��01�����������������ֵ��Ϊ��Ʒԭ���ļ�ֵ������Ϊ��ֵ���������һ���жϸ����Ƿ��������p
        �������ڣ�dp[i-c] + w ��dp[i] ���ʱ����״̬ת�Ʒ���ʧЧ���޷�������Ž⡣��Ϊ����Ȼ�����Ǹ��ʴ���p�ǲ����ģ��ڼ�ֵ��ͬʱҪѡ����ʴ��һ��
    for(int i=v;i>=c;--i)
    {
        if(dp[i - c] + w > dp[i])
        {
            if(dp2[i - c] * pol > p)
            {
                dp2[i] = dp2[i - c] * pol;
                dp[i] = dp[i - c] + w;
            }
        }
    }*/
}

//void complete_pack(int n, int v, int c, int w)///��ȫ����ģ��
//{
//    for(int i = c; i<=v; ++i)
//    {
//        dp[i] = max(dp[i], dp[i-c] + w);
//    }
//}

//void multiy_pack(int n, int v, int c, int w, int k)///���ر���ģ��
//{
//    if(k*c > v)
//    {
//        complete_pack(n,v,c,w);
//    }
//    else
//    {
//        int t = 1;
//        while(t < k)
//        {
//            zero_one_pack(n, v, t*c, t*w);
//            k -= t;
//            t *= 2;
//        }
//        zero_one_pack(n, v, k*c, k*w);
//    }
//}

int solve(int n,int sum)
{
    memset(dp2,0,sizeof(dp2));///���ڸ��ʳ�ʼ��Ϊ0�������൱����ͨ�����ĳ�ʼ��Ϊ-inf��������װ����01����
    dp2[0] = 1;///ʲôҲû��͵ʱ�����ܵĸ�����ȻΪ1
    for(int i=0;i<n;++i)
    {
        zero_one_pack(n,sum,arr[i],arr[i],arr2[i]);
    }
    int ans = 0;
    for(int i=sum;i>=0;--i)///���ڱ�����װ���ģ�����һ��������ģ������ҵ������������ĵ�һ��һ�������Ľ�
    {
        if(dp2[i] >= p)
        {
            return i;
        }
    }
    return ans;
}
//int solve2(int n, int sum)///���ر����ⷨ�����Ӷ�O(v*sum(log(k)))
//{
//    memset(dp,0,sizeof(dp));
//    for(int i = 0; i<n; ++i)
//    {
//        multiy_pack(n, sum, arr2[i], arr2[i], arr3[i]);
//    }
//    return dp[sum];
//}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        cin>>p>>n;
        p = 1-p;
        int sum=0;
        arr.clear();
        arr2.clear();
        for(int i=0;i<n;++i)
        {
            int tmp;
            double tmp2;
            cin>>tmp>>tmp2;
            sum += tmp;
            arr.push_back(tmp);
            arr2.push_back(1-tmp2);
        }
       int ans = solve(n,sum);
        cout<<ans<<endl;
    }
    return 0;
}

