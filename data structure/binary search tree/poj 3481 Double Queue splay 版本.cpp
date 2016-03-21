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
#define N 100005
#define M 100005
#define MAX 1000000000
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r

int n,m;
int pre[N],ch[N][2],val[N],nam[N],root,total;///nam��ʾ�����ͻ�����

void splay_new_node(int &r,int father,int value,int name)///��ԭ���splay_new_node����Ϊname���ƵĹ���
{
    r=++total;
    pre[r]=father;
    nam[r]=name;
    val[r]=value;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void splay_rotate(int r,int flag)
{
    int tmp=pre[r];
    ch[tmp][!flag]=ch[r][flag];
    pre[ch[r][flag]]=tmp;
//    pre[r]=pre[tmp];
    if(pre[tmp])
    {
        ch[pre[tmp]][ch[pre[tmp]][1]==tmp]=r;
    }
    pre[r]=pre[tmp];
    ch[r][flag]=tmp;
    pre[tmp]=r;
    return ;
}

void splay_low(int r,int goal)///��Ч���splay������д�������˻�ΪO(n)�������д
{
    while(pre[r]!=goal)
    {
        splay_rotate(r,ch[pre[r]][0]==r);
    }
    if(!goal)
    {
        root=r;
    }
}

void splay(int r,int goal)///��Ч���˫��splay
{
    while(pre[r]!=goal)
    {
        if(pre[pre[r]]==goal)
        {
            splay_rotate(r,ch[pre[r]][0]==r);
        }
        else
        {
            int y=pre[r];
            int flag=ch[pre[y]][0]==y;
            if(ch[y][flag]==r)
            {
                splay_rotate(r,!flag);
                splay_rotate(r,flag);
            }
            else
            {
                splay_rotate(y,flag);
                splay_rotate(r,flag);
            }
        }
    }
    if(goal==0)
    {
        root=r;
    }
}

bool splay_insert(int value,int name)///ͬԭ��
{
    int r=root;
    while(ch[r][val[r]<value])
    {
        if(val[r]==value)
        {
            splay(r,0);
            return false;
        }
        if(nam[r]==name)
        {
            splay(r,0);
            return false;
        }
        r=ch[r][val[r]<value];
    }
    splay_new_node(ch[r][val[r]<value],r,value,name);
    splay(ch[r][val[r]<value],0);
    return true;
}

int splay_max(int r)///��ѯ��rΪ�����ֵ
{
    int tmp=r;
    while(ch[tmp][1])
    {
        tmp=ch[tmp][1];
    }
    splay(tmp,0);
    return tmp;
}

int splay_min(int r)///ͬ�ϣ���ѯ��rΪ������Сֵ
{
    int tmp=r;
    while(ch[tmp][0])
    {
        tmp=ch[tmp][0];
    }
    splay(tmp,0);
    return tmp;
}

///������get_pre������get_aft����
///������splay_delete����
void splay_delete(int r)///delet���������޴��⣬ֻ��ɾ��������Сֵ
{
    if(r==root)
    {
        if(!ch[r][0]&&!ch[r][1])
        {
            root=total=0;
            ch[root][0]=0;
            ch[root][1]=0;
        }
        else
        {
            int t=ch[r][0] ? 0 : 1;
            pre[ch[r][t]]=0;
            root=ch[r][t];
        }
    }
    else
    {
        int y=pre[r];
        int t= (r == ch[r][1]);
        ch[y][t]=ch[r][!t];
        pre[ch[r][!t]]=y;
        splay(y,0);
    }
//    total--;
}

int main()
{
//    #ifndef ONLINE_JUDGE
////        freopen("input.txt","r",stdin);
//    #endif // ONLINE_JUDGE
    total=0;
    root=0;
    memset(pre,0,sizeof(pre));
    memset(ch,0,sizeof(ch));
    memset(val,0,sizeof(val));
    memset(nam,0,sizeof(nam));
    while(scanf("%d",&n),n)
    {
        if(n==1)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            splay_insert(b,a);
        }
        else
        {
            if(root==0)
            {
                printf("0\n");
                continue;
            }
            if(n==2)
            {
                int tmp=splay_max(root);
                splay_delete(tmp);
                printf("%d\n",nam[tmp]);
            }
            else if(n==3)
            {
                int tmp=splay_min(root);
                splay_delete(tmp);
                printf("%d\n",nam[tmp]);
            }
        }
    }
    return 0;
}
