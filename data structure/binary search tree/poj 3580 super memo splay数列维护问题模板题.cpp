///splay 对于数列维护问题的模板  by wkroach

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
#define inf 2e9
#define INF 2e18
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define key_value  ch[ch[root][1]][0]
int n;
int arr[N];
int pre[N],ch[N][2],val[N],m[N],root,total;///pre表示父节点，ch表示儿子节点，val表示节点存的值，root表示根，total表示树的规模,m表示子树的最小值
int s[N],rev[N],add[N];///s表示每个子树的规模，rev表示翻转懒惰标记,add表示区间增加懒惰标记
int s2[N],total2;///手动内存池，如遇到对内存要求非常高的题可使用
///m[N]也可表示其他信息如最大值，和等，同线段树
///通常数列维护问题不会出现相同节点的情况（因为每个数的位置都是确定且不会出现两个数位置相同）

void Treaval(int x) {
    if(x) {
        Treaval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,val = %2d \n",x,ch[x][0],ch[x][1],pre[x],s[x],val[x]);
        Treaval(ch[x][1]);
    }
}
void debug() {printf("%d\n",root);Treaval(root);}///debug函数

void splay_new_node(int &r,int father,int value)///建立新节点，并进行节点初始化，初始化一定要全！！！！！！！！！
{
    if(total2)
    {
        r=s2[total2--];
    }
    else
    {
        r=++total;
    }
    pre[r]=father;///初始化要全！！！！
    val[r]=value;
    m[r]=value;
    rev[r]=0;
    add[r]=0;
    s[r]=1;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void update_add(int r,int value)///更新操作，可根据题目要求进行更改
{
    if(!r) return;
    val[r]+=value;
    m[r]+=value;
    add[r]+=value;
}

void update_rev(int r)///更新操作，用于翻转，可根据题目要求进行更改
{
    if(!r) return ;
    swap(ch[r][0],ch[r][1]);
    rev[r]^=1;
}

void splay_push_up(int rt)///push_up函数，类似线段树
///注意！！！push_up操作通常在回溯时和更改节点后进行
{
    int l=ch[rt][0],r=ch[rt][1];
    s[rt]=s[r]+s[l]+1;
    m[rt]=min(min(m[l],m[r]),val[rt]);
    return ;
}

void splay_push_down(int rt)///push_down函数，用于更新懒惰标记，类似选段树
///注意！！！push_down操作主要在get_kth和get_min和get_max中完成，表示一直将操作推到所要求的节点
///则路径上所有节点已完成更改，因此可进行后续操作
///更新和push_down可以分开完成，使代码结构更好
{
    int l=ch[rt][0],r=ch[rt][1];
    if(rev[rt])
    {
        update_rev(l);
        update_rev(r);
        rev[rt]^=1;
    }
    if(add[rt])
    {
        update_add(l,add[rt]);
        update_add(r,add[rt]);
        add[rt]=0;
    }
    return ;
}

void build(int &rt,int l,int r,int father)///递归建树，方法类似于线段树，每个节点值为它在序列中对应位置的值
///每个节点在树中对应的位置是其隐含的信息，树实际是按照节点表示的位置顺序从小到大建立的
///节点的标号与值均与建树方式无关
{
    if(l>r)
    {
        return ;
    }
    int mid=(l+r)/2;
    splay_new_node(rt,father,arr[mid]);
    build(ch[rt][0],l,mid-1,rt);
    build(ch[rt][1],mid+1,r,rt);
    splay_push_up(rt);
}

void init()///初始化，在序列前后加入哨兵节点，分别用根节点与根节点右儿子，并以根节点右儿子的左儿子为根建树
///插入哨兵节点是为了处理数列最左边和最右边的情况
{
    root=total=total2=pre[0]=val[0]=ch[0][0]=ch[0][1]=add[0]=0;///初始化要全！！！！！！！！1
    s[0]=0;
    m[root]=inf;
    splay_new_node(root,0,inf);///哨兵节点的值根据题目要求不同而不同
    splay_new_node(ch[root][1],root,inf);
    build(key_value,1,n,ch[root][1]);///建树
    splay_push_up(ch[root][1]);///更新节点信息
    splay_push_up(root);
}

void splay_rotate(int r,int flag)///旋转，包含push_down和push_up
{
    int tmp=pre[r];
//    splay_push_down(tmp);///经测试，这两条push_down在本题中不影响结果，可注释掉。。。。。。。。
//    splay_push_down(r);///有可能是因为查询时已经push_down过了，因此rotate中push_down无意义？需要在之后题目中载进行试验
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

int splay_max(int r)///查询以r为根节点的子树的最大节点，即序列最右边的数，查询过程包含push_down
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

int splay_min(int r)///查询以r为根节点的子树的最小节点，即序列最左边的数，查询过程包含push_down
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
    update_rev(key_value);///懒惰标记根的右儿子的左儿子，利用之后一些列操作使这颗子树翻转
}

void splay_add(int a,int b,int c)///同翻转操作
{
    int x=splay_get_kth(root,a);
    int y=splay_get_kth(root,b+2);
    splay(x,0);
    splay(y,root);
    update_add(key_value,c);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_insert(int a,int b)///插入操作，在a之后插入一个数，插入一段数原理相同
{
    int x=splay_get_kth(root,a+1);
    int y=splay_get_kth(root,a+2);
    splay(x,0);
    splay(y,root);
    splay_new_node(key_value,ch[root][1],b);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_erase(int r)///删除子树操作，同时将删去的内存保留下来
{
    if(!r) return;
    s2[++total2]=r;
    splay_erase(ch[r][0]);
    splay_erase(ch[r][1]);
}

void splay_delete(int a,int b)///删除a，b之间的数列，原理同插入操作
{
    int x=splay_get_kth(root,a+1);
    int y=splay_get_kth(root,b+1);
    splay(x,0);
    splay(y,root);
    splay_erase(key_value);
    pre[key_value]=0;
    key_value=0;
    splay_push_up(ch[root][1]);
    splay_push_up(root);
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

int splay_Min(int a,int b)///查询a，b段中的最小值，可以根据题目要求更改所求内容，原理同上
{
    int x=splay_get_kth(root,a);
    int y=splay_get_kth(root,b+2);
    splay(x,0);
    splay(y,root);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
    return m[key_value];
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    char str[10];
    string str2;
    int a,b,c;
    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&arr[i]);
        }
        init();
//        debug();
        scanf("%d",&t);
        while(t--)
        {
            cin>>str2;
//            cout<<str2<<endl;
            if(str2=="ADD")
            {
                scanf("%d%d%d",&a,&b,&c);
                splay_add(a,b,c);
//                debug();
            }
            else if(str2=="REVERSE")
            {
                scanf("%d%d",&a,&b);
                splay_reverse(a,b);
//                debug();
            }
            else if(str2=="REVOLVE")///此题的关键，旋转操作，可以将旋转的量c对线段长取模，然后转换为剪切操作
            {
                scanf("%d%d%d",&a,&b,&c);
                int len=b-a+1;
                c=(c%len+len)%len;
                if(c==0)
                {
                    continue;
                }
                splay_cut(b-c+1,b,a-1);///转换后的剪切操作
//                debug();
            }
            else if(str2=="INSERT")
            {
                scanf("%d%d",&a,&b);
                splay_insert(a,b);
//                debug();
            }
            else if(str2=="DELETE")
            {
                scanf("%d",&a);
                splay_delete(a-1,a+1);
//                debug();
            }
            else
            {

                scanf("%d%d",&a,&b);
                printf("%d\n",splay_Min(a,b));
//                debug();
            }
        }
    }
    return 0;
}
