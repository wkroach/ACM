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
#define N 300005///splay树节点存放的内存池
#define M 100005
#define MAX 1000000000
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define key_value  ch[ch[root][1]][0]
int n,m;
int pre[N],ch[N][2],val[N],root,total;///pre表示父节点，ch表示儿子节点，val表示节点存的值，root表示根，total表示树的规模
int s[N],rev[N];///s表示每个子树的规模，rev表示懒惰标记

void splay_new_node(int &r,int father,int value)///建立新节点，并进行节点初始化
{
    r=++total;
    pre[r]=father;
    val[r]=value;
    rev[r]=0;
    s[r]=1;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void splay_push_up(int r)///push_up函数，类似线段树用于更新节点的size，即以r为根的树的大小（节点个数）
///注意！！！push_up操作通常在回溯时和更改节点后进行
{
    s[r]=s[ch[r][1]]+s[ch[r][0]]+1;
    return ;
}

void splay_push_down(int r)///push_down函数，用于更新懒惰标记，递归进行翻转子树，类似选段树
///注意！！！push_down操作主要在get_kth和get_min和get_max中完成，表示一直将操作推到所要求的节点
///则路径上所有节点均被翻转，因此可进行后续操作
{
    if(rev[r])
    {
        swap(ch[r][0],ch[r][1]);
        rev[ch[r][0]]^=1;
        rev[ch[r][1]]^=1;
        rev[r]^=1;
    }
    return ;
}

void build(int &rt,int l,int r,int father)///建树，方法类似于线段树，每个节点值为它在这个线段中的位置
{
    if(l>r)
    {
        return ;
    }
    int mid=(l+r)/2;
    splay_new_node(rt,father,mid);
    build(ch[rt][0],l,mid-1,rt);
    build(ch[rt][1],mid+1,r,rt);
    splay_push_up(rt);
}

void init()///初始化，在序列前后加入哨兵节点，分别用根节点与根节点右儿子，并以根节点右儿子的左儿子为根建树
{
    root=total=pre[0]=val[0]=0;
    splay_new_node(root,0,-1);
    splay_new_node(ch[root][1],root,-1);
    build(key_value,1,n,ch[root][1]);
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
///此题中单旋也可以，效率与双旋相差不大
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

int splay_get_kth(int r,int k)///查找r为根的子树所存的序列的第k个数，包含push_down操作
{
    splay_push_down(r);
    int t=s[ch[r][0]];
    if(k==t+1)
    {
        return r;
    }
    else if(k<=t)
    {
        return splay_get_kth(ch[r][0],k);
    }
    else
    {
        return splay_get_kth(ch[r][1],k-t-1);
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

void  splay_reverse(int a,int b)///重点！！！！将a,b段翻转，采用懒惰标记的方式进行
{
    int x=splay_get_kth(root,a);///注意，本应查询第a-1和b+1个节点，由于哨兵节点的存在，实际查询a和b+2
    int y=splay_get_kth(root,b+2);
    splay(x,0);///起使位置前一个节点伸展到假根，使之成为根
    splay(y,root);///终点位置后一个伸展到根，由于b一定在a的右边，所以伸展后成为根的右儿子
    rev[key_value]^=1;///懒惰标记根的右儿子的左儿子，利用之后一些列操作使这颗子树翻转
}

void splay_cut(int a,int b,int c)///重点！！！！剪切操作，将a,b段剪切到删除a,b段之后的c后面
{
    int x=splay_get_kth(root,a);///原理同reverse操作
    int y=splay_get_kth(root,b+2);
    splay(x,0);
    splay(y,root);
    int tmp=key_value;///剪切操作，需要将这棵树先保留在临时变量中，然后清除
    key_value=0;
    splay_push_up(ch[root][1]);///对节点进行操作后要更新节点
    splay_push_up(root);
    int z=splay_get_kth(root,c+1);///找到删除后的序列第c个节点（实为c+1）并伸展到假根
    splay(z,0);
    int zz=splay_min(ch[root][1]);///找到c的后继节点，由于c已经是根，所以后继节点即为右子树的最小节点（右子树最左边节点）
    splay(zz,root);///将c的后继节点伸展到根，即使之成为c的右儿子
    key_value=tmp;///将切掉的子树接到c的右儿子的左儿子，即接到c和c的后继之间，原理同reverse
    pre[tmp]=ch[root][1];
    splay_push_up(ch[root][1]);///同理，对接点进行操作后要更新节点
    splay_push_up(root);
}

int cnt=0;///计数器，用来记录输出次数
void splay_inorder(int r)
{
    if(r==0) return ;///r==0时表示访问到了空节点，表示访问到了树的叶子的空指针，返回
    splay_push_down(r);
    splay_inorder(ch[r][0]);
    if(cnt>=1&&cnt<=n)///cnt为0和n-1时访问的节点为哨兵节点，不输出
    {
        if(cnt>1)///按照输出要求输出
        {
            printf(" ");
        }
        printf("%d",val[r]);
    }
    cnt++;///注意计数器自增的位置，要在访问一个非空节点后再自增，始终在对当前节点进行操作的后面，与遍历规则无关
    splay_inorder(ch[r][1]);
//    splay_push_up(r); ///输出节点无需进行push_up
}
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    char str[10];
    int a,b,c;
    while(scanf("%d%d",&n,&t)==2)
    {
        if(n==-1&&t==-1)
        {
            break;
        }
        init();
        while(t--)
        {
            scanf("%s",str);
            if(str[0]=='C')
            {
                scanf("%d%d%d",&a,&b,&c);
                splay_cut(a,b,c);
            }
            else
            {
                scanf("%d%d",&a,&b);
                splay_reverse(a,b);
            }
        }
        cnt=0;///别忘了每次遍历输出时要清0计数器
        splay_inorder(root);
        puts("");
    }
    return 0;
}
