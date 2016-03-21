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
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
int n,m,k;
ULL q;
int arr[Size];
priority_queue<int>qu;

bool solve(int length)
{
        int cnt=1;
        ULL tmp=0;
        for(int j=0;j<n;++j)
        {
            if(qu.size()==length)
            {
                tmp+=(ULL)(cnt++)*(ULL)qu.top();
                qu.pop();
            }
            qu.push(arr[j]);
        }
        if(!qu.empty())
        {
            for(; cnt <= n;)
            {
                tmp += (ULL)(cnt++) * (ULL)qu.top();
                qu.pop();
            }
        }
        if(tmp<=q)
            return true;
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
//    int Case=0;
//    cin>>t;
//    while(t--)
//    cin>>n;
//    while(scanf("%d%d",&n,&m)==2)
//    {
//
//    }
    cin>>n>>q;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    while(!qu.empty())
        qu.pop();
//    ULL ans=INF;
    int length =n;
    int tmp=0;
    int a=1,b=n;
    int ans=-1;
    while(b-a>0)///因为队列越长，答案越小，所以二分查找下界（lower_bound)
    {
//        cout<<length<<" "<<a<<" "<<b<<endl;

        int mid = (a + b)>>1;
        length = mid;
        bool judge = solve(length);
        if(judge)
        {
            ans = length;
            b = mid;
        }
        else
        {
            a = mid + 1;
        }
    }
    if(a>n) cout<<-1<<endl;
    else
        cout<<a<<endl;
    return 0;
}
