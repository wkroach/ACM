//Îâ¿Â
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
using namespace std;
#define LL long long int
#define ULL unsigned long long int
#define MOD 1000000007
#define N 10005
#define M 100005
#define MAX 1000000000
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n=0,m=0,ql=0,qr=0,h=0,a=0,b=0,ans=0;
int arr[N*40],lazy[N*40],sum[N*40],l,r;///此题数据有问题，要开10倍给定范围的数组
struct node
{
    int a;
    int b;
    int x;
}arr2[N*10];
int Hash[10000005];///简单的哈希表，因为所给数的范围<=1e7,可用数组直接存放
map <int,int> MAP;///用map容易超时，此题最好还是不用map
vector <int> v;///离散化数据时用vector更方便

void build(int now,int l,int r)
{
    if(l==r)
    {
        sum[now]=0;
        return ;
    }
    build(lson);
    build(rson);
}
///此题只需统计叶子节点的颜色数即可，因此无需push_up
void push_down(int now,int l,int r)
{
    if(l==r) return ;
    if(lazy[now])
    {
        lazy[now*2]=lazy[now*2+1]=lazy[now];
        sum[now*2]=sum[now*2+1]=lazy[now];
        lazy[now]=0;
    }
}
void update(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(ql<=l&&r<=qr)
    {
        lazy[now]=b;
        sum[now]=b;
        return ;
    }
    push_down(now,l,r);
    if(ql<=mid) update(lson);
    if(qr>mid) update(rson);
}

void quire(int now,int l,int r)
{
    int ans=0;
    int mid=l+(r-l)/2;
    push_down(now,l,r);
    if(l==r)
    {
        arr[sum[now]]=1;///查询到一个叶子节点，用一个数组将它的颜色标记
        return ;
    }
    quire(lson);
    quire(rson);
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        //build(1,1,N);
        memset(arr,0,sizeof(arr));
        memset(sum,0,sizeof(sum));
        memset(lazy,0,sizeof(lazy));
        memset(Hash,0,sizeof(Hash));
        v.clear();
        //MAP.clear();
        ///重点——离散化！！！
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&arr2[i].a,&arr2[i].b);///用结构体保存区间位置方便查询
            //arr2[i].x=b=i;
            v.push_back(arr2[i].a);
            v.push_back(arr2[i].b);
        }
        sort(v.begin(),v.end());///现将输入的区间位置放入vector并排序
        int len=v.size();
//        for(int i=0;i<len;++i)
//            printf("%d ",v[i]);
 //       puts("");
        len=unique(v.begin(),v.end())-v.begin();///去重，将重复的元素去掉，减小离散化的范围
        ///注意unique的用法！！并不是去掉原先vector的元素而是将重复的元素置后
        ///并且返回去重后序列的最后一个元素的后一个位置
        int cnt=2;
        Hash[v[0]]=1;
        for(int i=1;i<len;++i)///将位置从小到大对应数字1~n
        {
            if(v[i]>1+v[i-1])///重点，若两个位置不相邻，需要在两者之间再插入一个元素
                ///否则会出现覆盖错误的情况
            {
                Hash[v[i-1]+1]=cnt;
                cnt++;
            }
            Hash[v[i]]=cnt;
            cnt++;
        }
        for(int i=1;i<=n;++i)
        {
            ql=Hash[arr2[i].a],qr=Hash[arr2[i].b];
            b=i;
            update(1,1,N*10);///更新节点，1~n的数字代表1~n种颜色
        }
        quire(1,1,N*10);///查询所有叶子节点并标记
        ans=0;
        for(int i=1;i<=n;++i)
            if(arr[i])
                ans++;///如果此颜色已经被标记，则ans增加
        printf("%d\n",ans);
//        for(int i=1;i<=n;++i)
//            printf("%d ",MAP[arr2[i].a]);
//        for(int i=0;i<len;++i)
//            printf("%d ",v[i]);
 //       puts("");
    }
    return 0;
}
