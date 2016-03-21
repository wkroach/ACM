

///splay解法2：由于题目中要增减的是全部节点的值，所以可以用一个cnt变量表示改变的总的值
///要注意新加进来的节点应当不受当前cnt影响，为了cnt的影响，要先减掉当前cnt的值

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
int s[N],rev[N];///s表示每个子树的规模，rev表示懒惰标记
int num[N],s2[N];///由于可能有值重复的节点，num用来存放此节点重复的个数，若没有重复节点则为1,s2表示树的实际规模（实际表示的r的个数）
int sum=0,cnt;///总共离开的员工数

void Treaval(int x) {
    if(x) {
        Treaval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,val = %2d \n",x,ch[x][0],ch[x][1],pre[x],s[x],val[x]);
        Treaval(ch[x][1]);
    }
}
void debug() {printf("%d\n",root);Treaval(root);}
void splay_new_node(int &r,int father,int value)///建立新节点，并进行节点初始化
{
    r=++total;
    pre[r]=father;
    val[r]=value;
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

void init()///初始化，在序列前后加入哨兵节点，分别用根节点与根节点右儿子，并以根节点右儿子的左儿子为根建树
{
    root=total=pre[0]=val[0]=s2[0]=s[0]=num[0]=0;
    ch[0][0]=ch[0][1]=0;
    splay_new_node(root,0,-inf);
    splay_new_node(ch[root][1],root,inf);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_rotate(int r,int flag)///旋转，包含push_up
{
    int tmp=pre[r];
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

void splay(int r,int goal)///高效版的双旋splay，包含push_up操作
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
    splay_push_up(r);///所有rotate完成后再更新儿子节点，提升效率。父节点的更新在rotate后进行
    if(goal==0)
    {
        root=r;
    }
}

void splay_insert(int r,int value)///splay 插入节点，value为所插入节点的值
{
    while(ch[r][val[r]<value])///循环查找值所在位置
    {
        if(val[r]==value)///重复的不插入
        {
            num[r]++;
            splay(r,0);
            return ;
        }
        r=ch[r][val[r]<value];
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
{
    int t=s2[ch[r][0]];
    if(k<=t+num[r]&&k>t)
    {
        return r;
    }
    else if(k<=t)
    {
        return splay_get_val_kth(ch[r][0],k);
    }
    else
    {
        return splay_get_val_kth(ch[r][1],k-t-num[r]);
    }
}

int splay_max(int r)///查询以r为根节点的子树的最大节点
{
    int tmp=r;
    while(ch[tmp][1])
    {
        tmp=ch[tmp][1];
    }
    return tmp;
}

int splay_min(int r)///查询以r为根节点的子树的最小节点
{
    int tmp=r;
    while(ch[tmp][0])
    {
        tmp=ch[tmp][0];
    }
    return tmp;
}

int splay_search_acc(int r,int k)///重点！！！查找值大于等于k的第一个节点，即值k的后继及值为k的节点
{
    int tmp=r;
    while(ch[r][val[r]<k])///先找到节点的位置或应该接入的位置
    {
        if(val[r]==k)
        {
            return r;
        }
        r=ch[r][val[r]<k];
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

void splay_delete()
{
//    int x=splay_min(root);
//    int y=splay_max(root);
//    splay(x,0);
//    splay(y,root);
    splay(1,0);///由于两个哨兵节点的编号已经确定好且不会再更改，可以直接伸展二不需要再查找
    splay(2,root);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
    int tmp=splay_max(key_value);
    if(val[tmp]<m-cnt)
    {
        sum+=s2[key_value];
        key_value=0;
        splay_push_up(ch[root][1]);
        splay_push_up(root);
        return ;
    }
    int r=splay_search_acc(key_value,m-cnt);
    splay(r,ch[root][1]);
//    cout<<"debug"<<endl;
    tmp=ch[key_value][0];
    ch[key_value][0]=0;
    sum+=s2[tmp];
    tmp=0;
    splay_push_up(key_value);
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
        cnt=0;
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
                splay_insert(root,k-cnt);///由于树中节点值的改变用cnt来代替，因此新插入节点要先减去cnt
            }
            if(str[0]=='A')
            {
                cnt+=k;
            }
            if(str[0]=='S')
            {
                cnt-=k;
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
                printf("%d\n",val[ans]+cnt);///输出结果要加上该变量cnt
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}
