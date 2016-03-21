

///splay写法1：区间操作，push_down



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
#define N 100005///splay树节点存放的内存池
#define M 100005
#define inf 1e9
#define INF 1LLe18
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define key_value ch[ch[root][1]][0]

int n,m;
int pre[N],ch[N][2],val[N],root,total;///pre表示父节点，ch表示儿子节点，val表示节点存的值，root表示根，total表示树的规模
int s[N],rev[N];///s表示每个子树的规模（节点个数），rev表示懒惰标记
int num[N],s2[N];///由于可能有值重复的节点，num用来存放此节点重复的个数，若没有重复节点则为1,s2表示树的实际规模（实际表示的r的个数）
int sum=0;///总共离开的员工数

void Treaval(int x) {
    if(x) {
        Treaval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,val = %2d \n",x,ch[x][0],ch[x][1],pre[x],s[x],val[x]);
        Treaval(ch[x][1]);
    }
}
void debug() {printf("%d\n",root);Treaval(root);}///debug函数

void splay_new_node(int &r,int father,int value)///建立新节点，并进行节点初始化
{
    r=++total;
    pre[r]=father;
    val[r]=value;
    rev[r]=0;
    s[r]=s2[r]=1;
    num[r]=1;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void splay_push_up(int r)///push_up函数，类似线段树用于更新节点的size，即以r为根的树的大小（节点个数）
///注意！！！push_up操作通常在回溯时和更改节点后进行
{
    s[r]=s[ch[r][1]]+s[ch[r][0]]+1;
    s2[r]=s2[ch[r][1]]+s2[ch[r][0]]+num[r];
    return ;
}

void splay_push_down(int r)///push_down函数，原理同线段树
{
    if(rev[r])
    {
        val[r]+=rev[r];
        rev[ch[r][0]]+=rev[r];
        rev[ch[r][1]]+=rev[r];
        rev[r]=0;
    }
    return ;
}



void init()///初始化，在序列前后加入哨兵节点，分别用根节点与根节点右儿子，并以根节点右儿子的左儿子为根建树
{
    root=total=pre[0]=val[0]=s2[0]=s[0]=num[0]=0;
    ch[0][0]=ch[0][1]=0;
    splay_new_node(root,0,-inf);
    splay_new_node(ch[root][1],root,inf);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_rotate(int r,int flag)///旋转，包含push_down和push_up
{
    int tmp=pre[r];
    splay_push_down(tmp);///经测试，这两条push_down在本题中不影响结果，可注释掉。。。。。。。。
    splay_push_down(r);///有可能是因为查询时已经push_down过了，因此rotate中push_down无意义？需要在之后题目中载进行试验
    ch[tmp][!flag]=ch[r][flag];
    pre[ch[r][flag]]=tmp;
    if(pre[tmp])
    {
        ch[pre[tmp]][ch[pre[tmp]][1]==tmp]=r;
    }
    pre[r]=pre[tmp];
    ch[r][flag]=tmp;
    pre[tmp]=r;
    splay_push_up(tmp);///由于splay旋转的方式，儿子节点在splay后更新即可，父亲则每次都要更新
}

void splay_low(int r,int goal)///低效版的splay，单旋写法，易退化为O(n)，代码好写
///此题中单旋效率为双旋一半
{
    splay_push_down(r);
    while(pre[r]!=goal)
    {
        splay_rotate(r,ch[pre[r]][0]==r);
    }
    splay_push_up(r);
    if(!goal)
    {
        root=r;
    }
}

void splay(int r,int goal)///高效版的双旋splay，包含push_down和push_up操作
{
    splay_push_down(r);
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
    splay_push_up(r);///所有rotate完成后再更新儿子节点，提升效率。父节点的更新在rotate后进行
    if(goal==0)
    {
        root=r;
    }
}

void splay_insert(int r,int value)///splay 插入节点，value为所插入节点的值
{
    splay_push_down(r);
    while(ch[r][val[r]<value])///循环查找值所在位置
    {
        if(val[r]==value)///重复的点需要增加num的值，并伸展到根
        {
            num[r]++;
            splay(r,0);
            return ;
        }
        r=ch[r][val[r]<value];
        splay_push_down(r);
//        cout<<"debug"<<endl;
    }
    splay_new_node(ch[r][val[r]<value],r,value);///创建新节点
    splay_push_up(r);
    splay_push_up(ch[r][val[r]<value]);
//    cout<<"debug"<<endl;
    splay(ch[r][value>val[r]],0);///splay调整
//    cout<<"debug"<<endl;
}

int splay_get_val_kth(int r,int k)///查找r为根的子树所存的序列的第k个数，包含push_down操作
///由于有重复节点的存在，所以与普通版有区别
{
//    cout<<k<<endl;
    splay_push_down(r);
    int t=s2[ch[r][0]];
    if(k<=t+num[r]&&k>t)///考虑重复节点
    {
        return r;
    }
    else if(k<=t)
    {
        return splay_get_val_kth(ch[r][0],k);
    }
    else
    {
        return splay_get_val_kth(ch[r][1],k-t-num[r]);///同上
    }
}
int splay_max(int r)///查询以r为根节点的子树的最大节点，查询过程包含push_down
{
    splay_push_down(r);
    int tmp=r;
    while(ch[tmp][1])
    {
        tmp=ch[tmp][1];
        splay_push_down(tmp);
    }
    return tmp;
}

int splay_min(int r)///查询以r为根节点的子树的最小节点，查询过程包含push_down
{
    splay_push_down(r);
    int tmp=r;
    while(ch[tmp][0])
    {
        tmp=ch[tmp][0];
        splay_push_down(tmp);
    }
    return tmp;
}

void  splay_add(int k)///采用懒惰标记的方式对区间进行操作，此题范围同一为起始到终止
{
    int x=splay_min(root);///此题同大部分伸展树操作中的一样，将两个哨兵节点伸展到根和根的右儿子
    int y=splay_max(root);
    splay(x,0);
    splay(y,root);
    rev[key_value]+=k;///懒惰标记根的右儿子的左儿子，利用之后一些列操作增加这段区间的值
}

int splay_search_acc(int r,int k)///重点！！！查找值大于等于k的第一个节点，即值k的后继及值为k的节点
{
    splay_push_down(r);
    int tmp=r;
    while(ch[r][val[r]<k])///先找到节点的位置或应该接入的位置
    {
        if(val[r]==k)
        {
            return r;
        }
        r=ch[r][val[r]<k];
        splay_push_down(r);
    }
    if(val[r]>k)///若父节点满足要求，直接返回结果
    {
        return r;
    }
    while(r!=tmp&&k>val[r])///否则同二叉树查询后继节点，需要向前查找
    {
        r=pre[r];
    }
    return r;
}

void splay_delete()///重点！！！！删除子树
{
    int x=splay_min(root);///伸展哨兵节点
    int y=splay_max(root);
    splay(x,0);
    splay(y,root);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
    int tmp=splay_max(key_value);///如果子树中最大的值依然小于工资下限，则直接全部删除即可
      if(val[tmp]<m)
    {
        sum+=s2[key_value];
        key_value=0;
        splay_push_up(ch[root][1]);
        splay_push_up(root);
        return ;
    }
    int r=splay_search_acc(key_value,m);///查找后继节点，并伸展到子树的根
    splay(r,ch[root][1]);
//    cout<<"debug"<<endl;
    tmp=ch[key_value][0];///删除左子树即可将小于工资下限的节点全部删除
    ch[key_value][0]=0;
    sum+=s2[tmp];
    tmp=0;
    splay_push_up(key_value);///维护树
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    char str[10];
    int a,b,c;
    int k;
    while(scanf("%d%d",&n,&m)==2)
    {
        sum=0;
        init();///初始化很重要！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            scanf("%d",&k);
//            cout<<str<<endl;
            if(str[0]=='I')
            {
                if(k<m)
                {
                    continue;
                }
                splay_insert(root,k);
            }
            if(str[0]=='A')
            {
                  splay_add(k);
            }
            if(str[0]=='S')
            {
                splay_add(-k);
                splay_delete();
//                debug();
            }
            if(str[0]=='F')
            {
//                debug();
                if(s2[root]<k+2)///注意，题目要求第k大的值，与树从小到大查找相反，因此要反着找
                {
                    printf("-1\n");
                    continue;
                }
//                debug();
                int ans=splay_get_val_kth(root,s2[root]-k);
                printf("%d\n",val[ans]);
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}
