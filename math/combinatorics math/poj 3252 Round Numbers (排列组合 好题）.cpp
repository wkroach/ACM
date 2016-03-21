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
#define LL long long
#define i64 __LL64
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
LL n,m,k;
LL C[35][35];
LL num[35];///对每一个2 的次幂 2^i（即首位为1，其余为0），利用排列组合统计小于2^(i+1)的round数的数目

void combination() ///组合数表
{
    for(int i=0;i<35;++i)
    {
        C[i][0] = 1;
    }
    for(int i=1;i<35;++i)
    {
        for(int j=1;j<=i;++j)
        {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
//    for(int i=0;i<35;++i)///测试组合数是否正确
//    {
//        for(int j=0;j<=i;++j)
//        {
//            cout<<C[i][j]<<" ";
//        }
//        cout<<endl;
//    }
}

void init()///
{
    for(int i=1; i<= 32; ++i)
    {
        for(int j = (i + 1)/2 ; j < i ; ++j)///统计大于等于2^i, 小于2^(i+1)的round数的数目
        {
            num[i] += C[i-1][j];
        }
        num[i] += num[i-1];
    }
//    for(int i=0;i<=35;++i)
//    {
//        cout<<num[i]<<endl;
//    }
}

void output_2(LL x)///输出x的二进制形式
{
    LL tmp = x;
    stack<LL> s;
    while(tmp)
    {
        s.push(tmp&1);
        tmp>>=1;
    }
    while(!s.empty())
    {
        cout<<s.top();
        s.pop();
    }
    cout<<endl;
}

LL solve(LL x)
{
    LL tmp = x;
    stack<LL> s;
    while(tmp)
    {
        s.push(tmp&1);
        tmp>>=1;
    }
    vector<LL> arr;
    while(!s.empty())
    {
        arr.push_back(s.top());
        s.pop();
    }///先转换成2进制位并存起来
    LL ans = 0;
    int len = arr.size();
    ans += num[len-1];///先二进制统计长度小于x的round数数目，即num[len - 1]
    int zero = 0;///从最高位的后一位，依次往后统计round数的数目，zero表示当前位之前0的数目
    for(int i = 1; i < arr.size(); ++i)
    {
        int cnt = len - i;
        if(arr[i])///只对当前位为1时进行分析，先假设它为0，对之后的位进行排列组合统计，因为这样得出的结果一定比它小
        {
            zero++;
            for(int j = max(0 , (len + 1)/2 - zero) ; j < cnt; ++j)
            {
                ans += C[cnt-1][j];
            }
            zero--;///别忘了还原回1
        }
        else
        {
            zero++;
        }
    }
    return ans;
}


int main()
{

    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    combination();
    init();
    LL t;
    LL x,y,z;
    LL Case=0;
//    cin>>t;
//    while(t--)
//    cin>>n;
//    for(LL i=1;i<13;++i)
//    {
//       output_2(i);
//       cout<<solve(i)<<endl;
//    }
    while(scanf("%I64d%I64d",&n,&m)==2)
    {
        printf("%I64d\n",solve(m+1)-solve(n)) ;/// solve(x)是选择比x小的round 数， 由于题目要求是闭区间内，因此后者加一
    }
    return 0;
}
