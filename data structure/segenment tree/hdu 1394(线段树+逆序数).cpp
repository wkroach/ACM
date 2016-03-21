
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
            ///����arr[0]~arr[n-1]����0~n-1��
            ///��arr[i]ǰ���ұ������������Ϊ��ĿǰΪֹ��arr[i]��n-1�������������һ����arr[i]��
            ///��Ϊarr[i]����arr[i]֮ǰ��������
            ///��ѯarr[i]��n-1֮������ĸ���
            sum+=quire(1,0,n-1);
            ///���½ڵ㣬���������arr[i]�����߶���
            push_up(arr[i],1,0,n-1);
        }
        int ans=sum;
        for(int i=0;i<n;++i)
        {
            ///��arr[i]���������ײ�ʱ����arr[i]�������������Լ�Ϊarr[i]��ֵ
            ///��Ϊ��arr[i]С�����ĸ���Ϊarr[i]���Ҷ�����֮��
            ///�ұ���������ĸ���Ϊn-1-arr[i]
            ///��arr[i]������βʱ��������ȥ���������������ԣ����ϱ���������ĸ���
            ///��Ϊ�µ����е�������
            sum+=n-2*arr[i]-1;
            ans=min(ans,sum);
        }
        printf("%d\n",ans);
    }
    return 0;
}

