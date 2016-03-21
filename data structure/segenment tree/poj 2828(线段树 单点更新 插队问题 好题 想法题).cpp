//���
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
    if(pos<=sum[now*2]) update(lson);///�ص㣡������������������������������
    ///���pos֮ǰ��a�ˣ���ôposһ��Ҫ����ƶ�a����λ�ã�
    ///���pos����֮���λ�����ˣ���ôpos��Ҫ������������������
    ///���ԣ��赱ǰpos�������ӣ����ӳ���Ϊn��posΪp
    ///������posǰ��a�ˣ�����b��
    ///��n-p>=a+b����n-a-b>=p���������п�λ����sum[now*2]���ڵ���pʱ
    ///pos�Ż�ͣ���������У���֮��ͣ�����Һ�����
    else
    {
        pos-=sum[now*2];///�ص㣡��������������������������������
        ///��pos�Ѿ����Һ����л������Һ����У�pos��Ϊp+a+b���ݹ��ѯ�Һ���ʱ
        ///pos��λ��Ҫ������Һ��ӵ�����ʼ������pos=p+a+b-n��pos=p-(n-a-b)
        ///��p�������п�λ����sum[now*2]
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
            scanf("%d%d",&arr2[i],&arr3[i]);///����ÿ���˵�λ��ֻ����֮�������˵�λ�õ�Ӱ��
            ///���Կ��Ե������ÿ���ˣ����Ƶ�������֮���˵�λ�ã���Ӧ���ƶ�������
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
