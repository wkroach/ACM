#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define eps 1e-9
#define N 100000
#define M 30
#define ULL unsigned long long int
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
///数组表示二叉树，数组的下标表示节点的编号
int n,pre[N+5],ch[N+5][2],val[N+5],root,total;
///pre存放父节点的下标，val存放值，ch存放孩子下标，0左孩子1右孩子
///root表示根节点下标，假根下标为0，只作为父节点使用，total表示节点数
void splay_new_node(int &r,int father,int value)///新建节点，节点标号标号加1，总数加1
{
    r=++total;
    pre[r]=father;
    val[r]=value;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void splay_rotate(int r,int flag)///splay旋转操作，与普通平衡树的旋转操作无异，r表示被旋转的节点下标
///flag表示旋转的方向，0表示左旋，1表示右旋
{
    int tmp=pre[r];
    ch[tmp][!flag]=ch[r][flag];
    pre[ch[r][flag]]=tmp;
    if(pre[tmp])
        ch[pre[tmp]][ch[pre[tmp]][1]==tmp]=r;///碉堡的代码！！！！一行就可以判断当前节点的方向并且进行调整
    pre[r]=pre[tmp];
    ch[r][flag]=tmp;
    pre[tmp]=r;
    return;
}

void splay(int r,int goal)///splay调整，分为3种情况
{
    while(pre[r]!=goal)///循环调整，直到所调整的节点的跟节点为目标记节点
    {
//        cout<<pre[r]<<" "<<pre[pre[r]]<<endl;
        if(pre[pre[r]]==goal)///情况1：父节点的父节点为目标节点，1次旋转即可
        {
            splay_rotate(r,ch[pre[r]][0]==r);///直接通过当前节点的方向判断旋转方向
        }
        else
        {
            int y=pre[r];
            int flag=ch[pre[y]][0]==y;///预设旋转方向
            if(ch[y][flag]==r)///情况2：父节点的方向与当前节点方向不同，2次相反方向旋转即可
            {
                splay_rotate(r,!flag);
                splay_rotate(r,flag);
            }
            else///情况3：父子节点方向相同，先转父节点，后转子节点，旋转方向相同
            {
                splay_rotate(y,flag);
                splay_rotate(r,flag);
            }
        }
    }
    if(goal==0)///根据所选目标节点调整根节点
        root=r;
}

bool splay_insert(int value)///splay 插入节点，value为所插入节点的值
{
    int r=root;
    while(ch[r][val[r]<value])///循环查找值所在位置
    {
        if(val[r]==value)///重复的不插入
        {
            splay(r,0);
            return false;
        }
        r=ch[r][val[r]<value];
//        cout<<"debug"<<endl;
    }
    splay_new_node(ch[r][val[r]<value],r,value);///创建新节点
//    cout<<"debug"<<endl;
    splay(ch[r][value>val[r]],0);///splay调整
//    cout<<"debug"<<endl;
    return true;
}

int get_pre(int x)///查找前继
{
    int r=x;
    if(ch[r][0]==0) return INF;
    r=ch[r][0];
    while(ch[r][1])
        r=ch[r][1];
    return val[x]-val[r];///根据题目要求返回差值
}

int get_aft(int x)///查找后继，其余同上
{
    int r=x;
    if(ch[r][1]==0) return INF;
    r=ch[r][1];
    while(ch[r][0])
        r=ch[r][0];
    return val[r]-val[x];
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d",&n)==1)
    {
        int ans=0;
        root=total=0;
        memset(pre,0,sizeof(pre));
        memset(val,0,sizeof(val));
        memset(ch,0,sizeof(ch));
        for(int i=0;i<n;++i)
        {
            int tmp;
            if(scanf("%d",&tmp)==EOF)
                tmp=0;
            if(i==0)
            {
                ans+=tmp;
                splay_new_node(root,0,tmp);
                continue;
            }
            if(!splay_insert(tmp)) continue;
            int pre_value=get_pre(root);
            int aft_value=get_aft(root);
            ans+=min(pre_value,aft_value);
//            cout<<tmp<<" "<<ans<<endl;
        }
        printf("%d\n",ans);
    }
    return 0;
}
