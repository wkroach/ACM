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

void push_up(int now,int l,int r)///�ص㣡������������ϲ�������
{
    if(l==r) return ;
    int mid=l+(r-l)/2;
    if((lsum[now*2]>=mid-l+1)&&arr[mid+1]>arr[mid])///ֱ��ͨ��ԭ��������жϣ������������ϵ�ͺϲ�
        lsum[now]=lsum[now*2]+lsum[now*2+1];
    else
        lsum[now]=lsum[now*2];
    if((rsum[now*2+1]>=r-mid)&&arr[mid+1]>arr[mid])
        rsum[now]=rsum[now*2+1]+rsum[now*2];
    else
        rsum[now]=rsum[now*2+1];
    msum[now]=max(msum[now*2],msum[now*2+1]);
    if(arr[mid]<arr[mid+1])///ͬ�ϣ��ϲ�ʱҪ�������Һ��Ӹ��Ժ����Һ�����ͨ���ֵĳ��ȴ�С
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
    if(ql<=mid&&qr>mid&&l!=r)///��ѯʱҲ��Ҫ�ж��Ƿ�����ϲ������������©��
    {
        if(arr[mid+1]>arr[mid])///�ϲ�������push_up���ƣ���Ҫע�⣬��ѯ������ԭ���䲻һ��һ��
            ///��Ҫ����ȡ��
        {
            int len1,len2;
            if(rsum[now*2]>=mid-ql+1) len1=mid-ql+1;///ԭ���䳤�ȿ��ܴ����������䣬��Ҫ��ȥ����
            else len1=rsum[now*2];
            if(lsum[now*2+1]>=qr-mid) len2=qr-mid;///ͬ��
            else len2=lsum[now*2+1];
            ans3=max(ans3,len1+len2);///����������������ֵ
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
            scanf("%s",ch);///�ص㣡��������������������������������
            ///Ϊ�˷�ֹ������ַ������ַ����������ַ���������������
            if(ch[0]=='Q')
            {
                scanf("%d%d",&ql,&qr);
                printf("%d\n",quire(1,0,n-1));
            }
            else if(ch[0]=='U')
            {
                scanf("%d%d",&pos,&val);
                arr[pos]=val;///��ֱ���޸�ԭ�����ֵ����ʡ�ռ�ʱ��
                update(1,0,n-1);
            }
        }
    }
    return 0;
}
