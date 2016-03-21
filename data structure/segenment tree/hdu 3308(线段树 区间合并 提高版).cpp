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
#define MAX 1000000000
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,ql,qr,pos,val;
int arr[N],msum[N*4],lsum[N*4],rsum[N*4];

void push_up(int now,int l,int r)///重点！！！！！区间合并！！！
{
    if(l==r) return ;
    int mid=l+(r-l)/2;
    if((lsum[now*2]>=mid-l+1)&&arr[mid+1]>arr[mid])///直接通过原数组进行判断，如满足递增关系就合并
        lsum[now]=lsum[now*2]+lsum[now*2+1];
    else
        lsum[now]=lsum[now*2];
    if((rsum[now*2+1]>=r-mid)&&arr[mid+1]>arr[mid])
        rsum[now]=rsum[now*2+1]+rsum[now*2];
    else
        rsum[now]=rsum[now*2+1];
    msum[now]=max(msum[now*2],msum[now*2+1]);
    if(arr[mid]<arr[mid+1])///同上，合并时要考虑左，右孩子各自和左右孩子连通部分的长度大小
        msum[now]=max(msum[now],rsum[now*2]+lsum[now*2+1]);
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        msum[now]=lsum[now]=rsum[now]=1;
        return ;
    }
    build(lson);
    build(rson);
    push_up(now,l,r);
}
void update(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(l==r)
    {
        return ;
    }
    if(pos<=mid) update(lson);
    if(pos>mid) update(rson);
    push_up(now,l,r);
}

int quire(int now,int l,int r)
{
    int ans1=1,ans2=1,ans3=0;
    int mid=l+(r-l)/2;
    if(ql<=l&&r<=qr)
    {
        return msum[now];
    }
    if(ql<=mid) ans1=quire(lson);
    if(qr>mid) ans2=quire(rson);
    ans3 = max(ans1,ans2);
    if(ql<=mid&&qr>mid&&l!=r)///查询时也需要判断是否满足合并条件，否则会漏解
    {
        if(arr[mid+1]>arr[mid])///合并过程与push_up类似，但要注意，查询区间与原区间不一定一致
            ///需要进行取舍
        {
            int len1,len2;
            if(rsum[now*2]>=mid-ql+1) len1=mid-ql+1;///原区间长度可能大于所查区间，需要舍去部分
            else len1=rsum[now*2];
            if(lsum[now*2+1]>=qr-mid) len2=qr-mid;///同上
            else len2=lsum[now*2+1];
            ans3=max(ans3,len1+len2);///返回三种情况的最大值
        }
    }
    return ans3;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    int a,b;
    char ch[2];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(arr,0,sizeof(arr));
        memset(msum,0,sizeof(msum));
        memset(lsum,0,sizeof(lsum));
        memset(rsum,0,sizeof(rsum));
        for(int i=0;i<n;++i)
            scanf("%d",&arr[i]);
        build(1,0,n-1);
        for(int i=0;i<m;++i)
        {
            scanf("%s",ch);///重点！！！！！！！！！！！！！！！！！
            ///为了防止读入空字符，用字符串来读入字符！！！！！！！
            if(ch[0]=='Q')
            {
                scanf("%d%d",&ql,&qr);
                printf("%d\n",quire(1,0,n-1));
            }
            else if(ch[0]=='U')
            {
                scanf("%d%d",&pos,&val);
                arr[pos]=val;///可直接修改原数组的值，节省空间时间
                update(1,0,n-1);
            }
        }
    }
    return 0;
}
