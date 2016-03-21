
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
#define N 100005
LL arr1[N],arr2[N],arr4[N];
LL r,ans;
int n,m;
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE

    int t;
    scanf("%d",&t);
    while(t--)
    {
       scanf("%d%d",&n,&m);
       for(int i=0;i<n;++i)
            scanf("%lld%lld",&arr1[i],&arr2[i]);
        arr4[n-1]=arr1[n-1]*arr2[n-1];
        for(int i=n-2;i>=0;--i)
            arr4[i]=min(arr1[i]*arr2[i],arr4[i+1]);///预处理，arr4[i]为i之后最小的价格
       vector <LL> arr3(arr1,arr1+n);
       vector <LL> :: iterator it;
       while(m--){
            it=arr3.begin();
            scanf("%lld",&r);
            if(r==0){printf("0\n");continue;}
            it=lower_bound(arr3.begin(),arr3.end(),r);///用lowwer_bound找到第一个大于等于r的位置
            int s=(it-arr3.begin()-1);
            ans=min(r*arr2[s],arr4[s+1]);
            if(r>arr1[n-1]) ans=r*arr2[n-1];
            printf("%lld\n",ans);
       }
    }
    return 0;
}

