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
#define ULL unsigned long long int
#define MOD 1000000007
#define N 50005
#define Max 1000000000
#define seed 31
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int BIT[N],n,pos,val,arr[N],sum1,sum2,ql,qr;
string ch;
int lowbit(int x)
{
    return x&(-x);
}

void update(int pos,int val)///更新节点
{
    while(pos<=n)
    {
        BIT[pos]+=val;
        pos+=lowbit(pos);
    }
}

void getsum1(int qr)///求和
{
    while(qr>0)
    {
        sum1+=BIT[qr];
        qr-=lowbit(qr);
    }
}

void getsum2(int qr)///同上
{
    while(qr>0)
    {
        sum2+=BIT[qr];
        qr-=lowbit(qr);
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(BIT,0,sizeof(BIT));
        memset(arr,0,sizeof(arr));
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&arr[i]);
            update(i,arr[i]);///初始化
        }
        printf("Case %d:\n",T-t);
        while(cin >> ch,ch!="End")
        {
//            cout << ch,'\n';
            if(ch=="Query")
            {
                scanf("%d%d",&ql,&qr);
                sum1=sum2=0;
                if(ql==1) getsum1(qr);
                else
                {
                    getsum1(qr);
                    getsum2(ql-1);
                    sum1-=sum2;
                }
                printf("%d\n",sum1);
            }
            else if(ch=="Add")
            {
                scanf("%d%d",&pos,&val);
                update(pos,val);
            }
            else if(ch=="Sub")
            {
                scanf("%d%d",&pos,&val);
                update(pos,-val);
            }
        }
    }
    return 0;
}
