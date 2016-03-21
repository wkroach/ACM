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
#define N 300005///splay���ڵ��ŵ��ڴ��
#define M 100005
#define MAX 1000000000
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define key_value  ch[ch[root][1]][0]
int n,m;
int pre[N],ch[N][2],val[N],root,total;///pre��ʾ���ڵ㣬ch��ʾ���ӽڵ㣬val��ʾ�ڵ���ֵ��root��ʾ����total��ʾ���Ĺ�ģ
int s[N],rev[N];///s��ʾÿ�������Ĺ�ģ��rev��ʾ������

void splay_new_node(int &r,int father,int value)///�����½ڵ㣬�����нڵ��ʼ��
{
    r=++total;
    pre[r]=father;
    val[r]=value;
    rev[r]=0;
    s[r]=1;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void splay_push_up(int r)///push_up�����������߶������ڸ��½ڵ��size������rΪ�������Ĵ�С���ڵ������
///ע�⣡����push_up����ͨ���ڻ���ʱ�͸��Ľڵ�����
{
    s[r]=s[ch[r][1]]+s[ch[r][0]]+1;
    return ;
}

void splay_push_down(int r)///push_down���������ڸ��������ǣ��ݹ���з�ת����������ѡ����
///ע�⣡����push_down������Ҫ��get_kth��get_min��get_max����ɣ���ʾһֱ�������Ƶ���Ҫ��Ľڵ�
///��·�������нڵ������ת����˿ɽ��к�������
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

void build(int &rt,int l,int r,int father)///�����������������߶�����ÿ���ڵ�ֵΪ��������߶��е�λ��
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

void init()///��ʼ����������ǰ������ڱ��ڵ㣬�ֱ��ø��ڵ�����ڵ��Ҷ��ӣ����Ը��ڵ��Ҷ��ӵ������Ϊ������
{
    root=total=pre[0]=val[0]=0;
    splay_new_node(root,0,-1);
    splay_new_node(ch[root][1],root,-1);
    build(key_value,1,n,ch[root][1]);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_rotate(int r,int flag)///��ת������push_down��push_up
{
    int tmp=pre[r];
    splay_push_down(tmp);///�����ԣ�������push_down�ڱ����в�Ӱ��������ע�͵�����������������
    splay_push_down(r);///�п�������Ϊ��ѯʱ�Ѿ�push_down���ˣ����rotate��push_down�����壿��Ҫ��֮����Ŀ���ؽ�������
    ch[tmp][!flag]=ch[r][flag];
    pre[ch[r][flag]]=tmp;
    if(pre[tmp])
    {
        ch[pre[tmp]][ch[pre[tmp]][1]==tmp]=r;
    }
    pre[r]=pre[tmp];
    ch[r][flag]=tmp;
    pre[tmp]=r;
    splay_push_up(tmp);///����splay��ת�ķ�ʽ�����ӽڵ���splay����¼��ɣ�������ÿ�ζ�Ҫ����
}

void splay_low(int r,int goal)///��Ч���splay������д�������˻�ΪO(n)�������д
///�����е���Ҳ���ԣ�Ч����˫������
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

void splay(int r,int goal)///��Ч���˫��splay������push_down��push_up����
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
    splay_push_up(r);///����rotate��ɺ��ٸ��¶��ӽڵ㣬����Ч�ʡ����ڵ�ĸ�����rotate�����
    if(goal==0)
    {
        root=r;
    }
}

int splay_get_kth(int r,int k)///����rΪ����������������еĵ�k����������push_down����
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

int splay_max(int r)///��ѯ��rΪ���ڵ�����������ڵ㣬��ѯ���̰���push_down
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

int splay_min(int r)///��ѯ��rΪ���ڵ����������С�ڵ㣬��ѯ���̰���push_down
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

void  splay_reverse(int a,int b)///�ص㣡��������a,b�η�ת�����������ǵķ�ʽ����
{
    int x=splay_get_kth(root,a);///ע�⣬��Ӧ��ѯ��a-1��b+1���ڵ㣬�����ڱ��ڵ�Ĵ��ڣ�ʵ�ʲ�ѯa��b+2
    int y=splay_get_kth(root,b+2);
    splay(x,0);///��ʹλ��ǰһ���ڵ���չ���ٸ���ʹ֮��Ϊ��
    splay(y,root);///�յ�λ�ú�һ����չ����������bһ����a���ұߣ�������չ���Ϊ�����Ҷ���
    rev[key_value]^=1;///�����Ǹ����Ҷ��ӵ�����ӣ�����֮��һЩ�в���ʹ���������ת
}

void splay_cut(int a,int b,int c)///�ص㣡���������в�������a,b�μ��е�ɾ��a,b��֮���c����
{
    int x=splay_get_kth(root,a);///ԭ��ͬreverse����
    int y=splay_get_kth(root,b+2);
    splay(x,0);
    splay(y,root);
    int tmp=key_value;///���в�������Ҫ��������ȱ�������ʱ�����У�Ȼ�����
    key_value=0;
    splay_push_up(ch[root][1]);///�Խڵ���в�����Ҫ���½ڵ�
    splay_push_up(root);
    int z=splay_get_kth(root,c+1);///�ҵ�ɾ��������е�c���ڵ㣨ʵΪc+1������չ���ٸ�
    splay(z,0);
    int zz=splay_min(ch[root][1]);///�ҵ�c�ĺ�̽ڵ㣬����c�Ѿ��Ǹ������Ժ�̽ڵ㼴Ϊ����������С�ڵ㣨����������߽ڵ㣩
    splay(zz,root);///��c�ĺ�̽ڵ���չ��������ʹ֮��Ϊc���Ҷ���
    key_value=tmp;///���е��������ӵ�c���Ҷ��ӵ�����ӣ����ӵ�c��c�ĺ��֮�䣬ԭ��ͬreverse
    pre[tmp]=ch[root][1];
    splay_push_up(ch[root][1]);///ͬ���Խӵ���в�����Ҫ���½ڵ�
    splay_push_up(root);
}

int cnt=0;///��������������¼�������
void splay_inorder(int r)
{
    if(r==0) return ;///r==0ʱ��ʾ���ʵ��˿սڵ㣬��ʾ���ʵ�������Ҷ�ӵĿ�ָ�룬����
    splay_push_down(r);
    splay_inorder(ch[r][0]);
    if(cnt>=1&&cnt<=n)///cntΪ0��n-1ʱ���ʵĽڵ�Ϊ�ڱ��ڵ㣬�����
    {
        if(cnt>1)///�������Ҫ�����
        {
            printf(" ");
        }
        printf("%d",val[r]);
    }
    cnt++;///ע�������������λ�ã�Ҫ�ڷ���һ���ǿսڵ����������ʼ���ڶԵ�ǰ�ڵ���в����ĺ��棬����������޹�
    splay_inorder(ch[r][1]);
//    splay_push_up(r); ///����ڵ��������push_up
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
        cnt=0;///������ÿ�α������ʱҪ��0������
        splay_inorder(root);
        puts("");
    }
    return 0;
}
