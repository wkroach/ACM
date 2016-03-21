
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
int arr2[2*N];
int ql,qr;
int build(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(l==r)
        return arr2[now]=0;
    build(now*2,l,mid);
    build(now*2+1,mid+1,r);
    arr2[now]=arr2[now*2]+arr2[now*2+1];
}

void push_up(int a,int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(l==r)
        arr2[now]++;
    else
    {
        if(a<=mid) push_up(a,now*2,l,mid);
        else push_up(a,now*2+1,mid+1,r);
        arr2[now]=arr2[now*2]+arr2[now*2+1];
    }
}

int quire(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    int ans=0;
    if(ql<=l&&r<=qr) return ans+=arr2[now];
    if(ql<mid) ans+=quire(now*2,l,mid);
    if(qr>mid) ans+=quire(now*2+1,mid+1,r);
    return ans;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int arr[N];
    int n;
    int sum;
    while(scanf("%d",&n)==1)
    {
        sum=0;
        memset(arr,0,sizeof(arr));
        memset(arr2,0,sizeof(arr2));
        build(1,0,n-1);
        for(int i=0;i<n;++i)
        {
            scanf("%d",&arr[i]);
            ql=arr[i],qr=n-1;
            ///由于arr[0]~arr[n-1]属于0~n-1，
            ///在arr[i]前面且比它大的数，即为到目前为止，arr[i]到n-1中已输入的数（一定比arr[i]大）
            ///即为arr[i]的在arr[i]之前逆序数对
            ///查询arr[i]到n-1之间的数的个数
            sum+=quire(1,0,n-1);
            ///更新节点，将新输入的arr[i]放入线段树
            push_up(arr[i],1,0,n-1);
        }
        int ans=sum;
        for(int i=0;i<n;++i)
        {
            ///当arr[i]放在数组首部时，由arr[i]产生的逆序数对即为arr[i]的值
            ///因为比arr[i]小的数的个数为arr[i]，且都在它之后
            ///且比它大的数的个数为n-1-arr[i]
            ///当arr[i]移至队尾时，总数减去它产生的逆序数对，加上比它大的数的个数
            ///即为新的序列的逆序数
            sum+=n-2*arr[i]-1;
            ans=min(ans,sum);
        }
        printf("%d\n",ans);
    }
    return 0;
}

