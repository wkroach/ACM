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
LL num[35];///��ÿһ��2 �Ĵ��� 2^i������λΪ1������Ϊ0���������������ͳ��С��2^(i+1)��round������Ŀ

void combination() ///�������
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
//    for(int i=0;i<35;++i)///����������Ƿ���ȷ
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
        for(int j = (i + 1)/2 ; j < i ; ++j)///ͳ�ƴ��ڵ���2^i, С��2^(i+1)��round������Ŀ
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

void output_2(LL x)///���x�Ķ�������ʽ
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
    }///��ת����2����λ��������
    LL ans = 0;
    int len = arr.size();
    ans += num[len-1];///�ȶ�����ͳ�Ƴ���С��x��round����Ŀ����num[len - 1]
    int zero = 0;///�����λ�ĺ�һλ����������ͳ��round������Ŀ��zero��ʾ��ǰλ֮ǰ0����Ŀ
    for(int i = 1; i < arr.size(); ++i)
    {
        int cnt = len - i;
        if(arr[i])///ֻ�Ե�ǰλΪ1ʱ���з������ȼ�����Ϊ0����֮���λ�����������ͳ�ƣ���Ϊ�����ó��Ľ��һ������С
        {
            zero++;
            for(int j = max(0 , (len + 1)/2 - zero) ; j < cnt; ++j)
            {
                ans += C[cnt-1][j];
            }
            zero--;///�����˻�ԭ��1
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
        printf("%I64d\n",solve(m+1)-solve(n)) ;/// solve(x)��ѡ���xС��round ���� ������ĿҪ���Ǳ������ڣ���˺��߼�һ
    }
    return 0;
}
