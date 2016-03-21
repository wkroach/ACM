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
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now<<1,l,l+(r-l)/2
#define rson now<<1|1,l+(r-l)/2+1,r
const int N=50005;
int n,m,val,pos,ql,qr,num;
int arr1[N<<2],arr2[N<<2],msum[N<<2],lsum[N<<2],rsum[N<<2],lazy[N<<2];

struct node
{
    int l;
    int r;
    bool friend operator <(node a,node b)
    {
        return a.l<b.l;
    }
};

void push_up(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(lsum[now<<1]==(mid-l+1))
        lsum[now]=lsum[now<<1]+lsum[now<<1|1];
    else
        lsum[now]=lsum[now<<1];
    if(rsum[now<<1|1]==r-mid)
        rsum[now]=rsum[now<<1|1]+rsum[now<<1];
    else
        rsum[now]=rsum[now<<1|1];
    msum[now]=max(msum[now<<1],msum[now<<1|1]);
    msum[now]=max(msum[now],rsum[now<<1]+lsum[now<<1|1]);
}

void push_down(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(lazy[now]!=-1&&l!=r)
    {
        lazy[now<<1]=lazy[now<<1|1]=lazy[now];
        msum[now<<1]=lsum[now<<1]=rsum[now<<1]=lazy[now]*(mid-l+1);
        msum[now<<1|1]=lsum[now<<1|1]=rsum[now<<1|1]=lazy[now]*(r-mid);
        lazy[now]=-1;
    }
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        msum[now]=lsum[now]=rsum[now]=1;
        return ;
    }
    int mid=l+(r-l)/2;
    build(lson);
    build(rson);
    msum[now]=lsum[now]=rsum[now]=msum[now<<1]+msum[now<<1|1];
}

bool quire(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    push_down(now,l,r);
    if(msum[now]<num)
    {
        return false;
    }
    if(l==r)
    {
        ql=l;
        qr=l+num-1;
        pos=ql;
        return true;
    }
    else if(msum[now<<1]>=num)
      return  quire(lson);
    else if(rsum[now<<1]+lsum[now<<1|1]>=num)
    {
        ql=mid-rsum[now<<1]+1;
        qr=ql+num-1;
        pos=ql;
        return true;
    }
      return  quire(rson);
}

void update(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(ql<=l&&r<=qr)
    {
        lazy[now]=val;
        msum[now]=lsum[now]=rsum[now]=(r-l+1)*lazy[now];
        return ;
    }
    push_down(now,l,r);
    if(ql<=mid) update(lson);
    if(qr>mid) update(rson);
    push_up(now,l,r);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d%d",&n,&m)==2)
    {
        vector<node>s;
        memset(lazy,-1,sizeof(lazy));
        build(1,1,n);
        char  q[10];
        for(int i=1;i<=m;++i)
        {
            scanf("%s",q);///�ַ�����char��string�ٶȿ���2��������������������
            if(q[0]=='R')
            {
                val=1;///��ǣ��������ַ��ú���գ�����ͬ��
                ql=1;
                qr=n;
                update(1,1,n);///Reset��update����buildҪ�죬ԭ��ͬpush_down,O(n)->O(logn)
                s.clear();
                puts("Reset Now");
            }
            else if(q[0]=='N')
            {
                val=0;
                scanf("%d",&num);
                if(quire(1,1,n))
                {
                    printf("New at %d\n",pos);
                    node tmp;
                    tmp.l=ql;
                    tmp.r=qr;
                    vector<node>::iterator it;
                    it=upper_bound(s.begin(),s.end(),tmp);///���ҵ���λ��(ql)���Ӵ�С���뵽vector�У������ҵ������λ��
                    s.insert(it,tmp);
                    update(1,1,n);
                }
                else puts("Reject New");
            }
            else if(q[0]=='F')
            {
                val=1;
                scanf("%d",&pos);
                node tmp;
                tmp.l=tmp.r=pos;
                vector<node>::iterator it;
                it=upper_bound(s.begin(),s.end(),tmp);///������������pos�ĵ�һ��ֵ
                int tmp2=it-s.begin()-1;///�ҵ�ǰһ��ֵ����posҪô�������ֵ�ı�ע��Χ��Ҫô����vector��
                if(tmp2==-1||s[tmp2].r<pos)///���ǰһ��ֵ��-1��pos���������Χ�ڣ���δ�ҵ�pos
                    puts("Reject Free");
                else
                {
                    cout<<"Free from "<<s[tmp2].l<<" to "<<s[tmp2].r<<endl;
                    ql=s[tmp2].l;qr=s[tmp2].r;
                    update(1,1,n);
                    s.erase(s.begin()+tmp2);
                }
            }
            else if(q[0]=='G')
            {
                scanf("%d",&num);
                if(s.size()<num)
                {
                    puts("Reject Get");
                }
                else
                {
                    printf("Get at %d\n",s[num-1].l);
                }
            }
        }
        puts("");
    }
   return 0;
}
