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
struct node
{
    int s;
    int x;
    int y;
    int h;
    bool friend operator <(node a, node b)
    {
        return a.s>b.s;
    }
};
int dp[Size];
vector<node> arr;
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int Case=0;
//    cin>>t;
//    while(t--)
    while(scanf("%d",&n)==1&&n)
    {
        arr.clear();
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d",&x,&y,&z);///����ÿ�����ο���������ת��ת��������ʵ�����ֵ׸߲�ͬ�ľ���
            node tmp = {x*y,x,y,z};
            arr.push_back(tmp);
            tmp = {x*z,x,z,y};
            arr.push_back(tmp);
            tmp = {z*y,z,y,x};
            arr.push_back(tmp);
        }
        sort(arr.begin(),arr.end());///��lis��ͬ��lis˳��������������������ѡ������Ϊ��֤����ľ��ξ�����������ǰ�����棬Ҫ�Ե����������
        dp[0] = arr[0].h;
        for(int i=1;i<arr.size();++i)///�����������lis���Σ�����Ϊÿ�����εĸߣ������ж�Ϊ�ױ��Ƿ��ܱ�ǰһ�����ΰ���
        {
            for(int j=0;j<i;++j)
            {
                if((arr[i].x<arr[j].x&&arr[i].y<arr[j].y)||(arr[i].x<arr[j].y&&arr[i].y<arr[j].x))
                {
                    dp[i] = max(dp[i], dp[j]);
                }
            }
            dp[i] += arr[i].h;///���Ȳ��Ǽ�һ���Ǽӵ�ǰ���εĸ�
        }
        int ans = -1;
        for(int i=0;i<arr.size();++i)
        {
            ans = max(ans, dp[i]);
        }
        printf("Case %d: maximum height = ",++Case);
        cout<<ans<<endl;
    }
    return 0;
}

