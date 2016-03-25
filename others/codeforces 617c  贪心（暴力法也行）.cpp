#include<cstdio>
#include<cstdlib>
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
#define Size 105
#define LL long long
#define ULL unsigned long long
#define Mod 1000000007

using namespace std;
int n,m,k;
struct node
{
    long long length;
    long long length1;
    long long length2;
    node():length(0),length1(0),length2(0){}
};

bool cmp(node a,node b)
{
    return a.length1>b.length1;
}
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t ;
//    scanf("%d",&t);
//    scanf("%d",&n);
    vector<node> arr;
    while(scanf("%d",&n)==1)
    {
        long long x1,x2,y1,y2;
        long long a,b;
        arr.clear();
        scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
        for(int i=0;i<n;++i)
        {
            node tmp2;
            scanf("%I64d%I64d",&a,&b);
            long long l1=(x1-a)*(x1-a)+(y1-b)*(y1-b);
            long long l2=(x2-a)*(x2-a)+(y2-b)*(y2-b);
            long long tmp=min(l1,l2);
//            cout<<tmp<<" "<<l1<<" "<<l2<<endl;
            tmp2.length=tmp;
            tmp2.length1=l1;
            tmp2.length2=l2;
            arr.push_back(tmp2);
        }
        arr.push_back(node());///末尾要多加一个空点，用来判断点全部在2号喷头范围内的情况
        sort(arr.begin(),arr.end(),cmp);
        long long ans1=0,ans2=0;
        LL ans=arr[0].length1;
        LL t=-1;
        for(int i=0;i<n;++i)
        {
            t=max(t,arr[i].length2);
            ans=min(ans,arr[i+1].length1+t);
        }
//        LL ans=1e18;
//        for(int j=0; j<=n; ++j)///暴力法
//        {
//            ans1=arr[j].length1;
//            ans2=0;
//            for(int i=0; i<n; ++i)
//            {
//                    if(ans1<arr[i].length1)
//                    {
//                        ans2=max(arr[i].length2,ans2);
//                    }
//            }
//            ans=min(ans,ans1+ans2);
//        }
//        if(n==1)
//        {
//            ans=min(arr[0].length1,arr[0].length2);
//        }
        printf("%I64d\n",ans);
    }
    return 0;
}
