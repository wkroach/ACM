//吴柯
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
#define N 200005
#define MAX 1000000000
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,sum[N*3],arr[N],arr2[N],arr3[N],ql,qr,pos,val;

void push_up(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    sum[now]=sum[now*2]+sum[now*2+1];
}

void build(int now,int l,int r)
{
    if(l==r)
    {
        sum[now]=1;
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
        sum[now]=0;
        arr[l]=val;
        return ;
    }
    if(pos<=sum[now*2]) update(lson);///重点！！！！！！！！！！！！！！！！
    ///如果pos之前有a人，那么pos一定要向后移动a个空位置，
    ///如果pos后移之后的位置有人，那么pos还要跳过它，继续往后移
    ///所以，设当前pos属于左孩子，左孩子长度为n，pos为p
    ///左孩子中pos前有a人，后有b人
    ///则n-p>=a+b，即n-a-b>=p，即左孩子中空位置数sum[now*2]大于等于p时
    ///pos才会停留在左孩子中，反之会停留在右孩子中
    else
    {
        pos-=sum[now*2];///重点！！！！！！！！！！！！！！！！！
        ///若pos已经在右孩子中或移入右孩子中，pos变为p+a+b，递归查询右孩子时
        ///pos的位置要相对于右孩子的起点初始化，即pos=p+a+b-n即pos=p-(n-a-b)
        ///即p减左孩子中空位置数sum[now*2]
        update(rson);
    }
    push_up(now,l,r);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d",&n)==1)
    {
        memset(arr,0,sizeof(arr));
        memset(sum,0,sizeof(sum));
        for(int i=n;i>0;--i)
            scanf("%d%d",&arr2[i],&arr3[i]);///由于每个人的位置只受它之后加入的人的位置的影响
            ///所以可以倒叙遍历每个人，并推导出由于之后人的位置，它应当移动到哪里
       build(1,1,n);
        for(int i=1;i<=n;++i)
        {
            pos=arr2[i]+1;
            val=arr3[i];
            ql=1,qr=pos;
            update(1,1,n);
        }
        for(int i=1;i<=n;++i)
        {
            printf("%d",arr[i]);
            if(i!=n)
                printf(" ");
            else
                puts("");
        }
//        for(int i=1;i<=n;++i)
//            printf("%d ",sum[i]);
    }
    return 0;
}
