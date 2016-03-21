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
#define N 500500
#define M 100005
#define MAX 1000000000
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,k,pos,val,ql,qr,sum[N*4],arr[N];
char name[N][20];
int rprime[37][2]=
{1,1,2,2,4,3,6,4,12,6,24,8,36,9,48,10,60,12,120,16,180,18,240,20,360,24,720,30,840,32,1260,36,1680,40,2520,48,5040,
60,7560,64,10080,72,15120,80,20160,84,25200,90,27720,96,45360,100,50400,
108,55440,120,83160,128,110880,144,166320,160,221760,168,277200,180,332640,192,498960,200,500001,1314521};
///重点！！！！！！500000以内反素数表
///反素数定义：设，f(x)为x的约数个数，如果存在x，使1~x内所有f(i)<f(x),那么x为反素数
///此题中，只需找出最大的比n小的反素数即可，它的f(x)即为答案
void push_up(int now)
{
    sum[now]=sum[now*2]+sum[now*2+1];
}

void build(int now,int l,int r)///建树，节点包含着此节点范围内空位置的个数（即未出队人的个数）
{
    if(l==r)
    {
        sum[now]=1;
        return ;
    }
    build(lson);
    build(rson);
    push_up(now);
}

void update(int now,int l,int r)
{
    if(l==r)
    {
        sum[now]=0;
        pos=l;
        return ;
    }
    if(pos<=sum[now*2]) update(lson);///重点！！！！！！！！！！！
    ///扩展的约瑟夫环，与poj2828 插队问题有类似解法
    ///关键：1.通过模运算找出下一个出队的人在剩余人中的顺序位
    ///（即它在剩余人中是第几位，而不是它的原序号）
    ///2.通过找出的序号，利用线段树找到它的原序号，即输入数组中它的序号
    ///方法：同插队问题，pos表示它在剩余人中（即剩余空位中）是第几位
    ///如果pos大于当前节点左儿子的空位数，那么它一定在
    ///右儿子，然后相对于右儿子，pos需要减去pos多于sum[now*2]的数，然后递归更新
    ///右儿子，否则更新左儿子
    else
    {
        pos-=sum[now*2];
        update(rson);
    }
    push_up(now);
}


int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d%d",&n,&k)==2)
    {
        memset(sum,0,sizeof(sum));
        memset(arr,0,sizeof(arr));
        memset(name,0,sizeof(name));
        for(int i=1;i<=n;++i)
            scanf("%s%d",name[i],&arr[i]);
        build(1,1,n);
//        printf("%s %d ",name[1],arr[1]);
        int p=0,ans=0;
        for(int i=0;i<37;++i)///找出最大的比n小的反素数
            if(rprime[i][0]>n)
            {
                p=rprime[i-1][0];
                ans=rprime[i-1][1];
                break;
            }
//        printf("%d ",p);
        for(int i=1;i<=p;++i)///只需遍历到反素数即可得出结果
        {
            pos=k;
            update(1,1,n);
//            printf("%d ",pos);
            if(i==p)
                break;
            if(arr[pos]>0)///模运算,从当前位置k，走arr[pos]步，
                ///由于模运算，整除时不能直接得0，所以再模之前要-1
                ///再模之后+1
                ///所以向前走要在初始位置-1，还要在走的步数上-1
                ///向后走不需要在步数上-1
                k=(k-2+arr[pos])%sum[1]+1;
            else
                k=((k-1+arr[pos])%sum[1]+sum[1])%sum[1]+1;
        }
        printf("%s %d\n",name[pos],ans);
    }
    return 0;
}
