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
int n,m,k;

int cnt=0;
int arr[110][110];
int dfs(int n,int m)///整数拆分的记忆化算法，分为对当前盘子中有无空盘的2种情况进行搜索
{

    if(n<0) return 0;
    if(arr[n][m]) return arr[n][m];
//    cout<<n<<" "<<m<<" "<<++cnt<<endl;
    if(n==0||m==1) return 1;///当n为0时和m为1时也要算一种
    return arr[n][m] = dfs(n-m,m) + dfs(n,m-1);///要么当前的每个盘子都放苹果，要么选一个不放，即得到两种子结构
}
int main()
{

    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    int x,y,z;
    LL Case=0;
    cin>>t;
    while(t--)
//    cin>>n;
//    while(cin>>n)
    {
        memset(arr,0,sizeof(arr));
        cin>>x>>y;
        cout<<dfs(x,y)<<endl;
    }
    return 0;
}
