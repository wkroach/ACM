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
#define pi 4*atan(1)
#define Mod 1000000007
#define eps 1e-8
using namespace std;
LL n,m,k;
LL arr[10005];
LL arr2[10006];
LL arr3[10006];

bool cmp(LL a, LL b)
{
    int x = (int)a;
    int y = (int)b;
    return arr2[x] < arr2[y];
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
//    LL Case=0;
//    cin>>t;
//    while(t--)
    while(scanf("%I64d",&n)==1)
    {
//        cout<<n<<endl;
        LL tmp = 0;
        for(int i = 0; i < (int)n ;++i)
        {
//            cout<<i<<endl;
            scanf("%I64d",&arr[i]);
            tmp += arr[i];
            arr2[i] = tmp % n;
            arr3[i] = (LL)i;
        }
        sort(arr3,arr3+n,cmp);
//        for(int i=0;i<n;++i)
//        {
//            cout<<arr2[i]<<endl;
//        }
        for(int i=0 ; i < (int)n ;++i)
        {
            if(arr2[i]==0)
            {
                cout<<i+1<<endl;
                for(int j=0;j<=i;++j)
                {
                    cout<<arr[j]<<endl;
                }
                goto there;
            }
        }
        for(int i=0 ; i < n-1 ;++i)
        {
            if(arr2[arr3[i]] == arr2[arr3[i+1]])
            {
                LL s = min(arr3[i], arr3[i+1]);
                LL e = max(arr3[i], arr3[i+1]);
                cout<<e-s<<endl;
                for(LL j = s+1; j <= e; ++j)
                {
                    cout<<arr[(int)j]<<endl;
                }
                break;
            }
        }
        there:
            ;
    }
    return 0;
}

