///splay ��������ά�������ģ��  by wkroach

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
#define inf 2e9
#define INF 2e18
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define key_value  ch[ch[root][1]][0]
int n;
int arr[N];
int pre[N],ch[N][2],val[N],m[N],root,total;///pre��ʾ���ڵ㣬ch��ʾ���ӽڵ㣬val��ʾ�ڵ���ֵ��root��ʾ����total��ʾ���Ĺ�ģ,m��ʾ��������Сֵ
int s[N],rev[N],add[N];///s��ʾÿ�������Ĺ�ģ��rev��ʾ��ת������,add��ʾ��������������
int s2[N],total2;///�ֶ��ڴ�أ����������ڴ�Ҫ��ǳ��ߵ����ʹ��
///m[N]Ҳ�ɱ�ʾ������Ϣ�����ֵ���͵ȣ�ͬ�߶���
///ͨ������ά�����ⲻ�������ͬ�ڵ���������Ϊÿ������λ�ö���ȷ���Ҳ������������λ����ͬ��

void Treaval(int x) {
    if(x) {
        Treaval(ch[x][0]);
        printf("���%2d:����� %2d �Ҷ��� %2d ����� %2d size = %2d ,val = %2d \n",x,ch[x][0],ch[x][1],pre[x],s[x],val[x]);
        Treaval(ch[x][1]);
    }
}
void debug() {printf("%d\n",root);Treaval(root);}///debug����

void splay_new_node(int &r,int father,int value)///�����½ڵ㣬�����нڵ��ʼ������ʼ��һ��Ҫȫ������������������
{
    if(total2)
    {
        r=s2[total2--];
    }
    else
    {
        r=++total;
    }
    pre[r]=father;///��ʼ��Ҫȫ��������
    val[r]=value;
    m[r]=value;
    rev[r]=0;
    add[r]=0;
    s[r]=1;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void update_add(int r,int value)///���²������ɸ�����ĿҪ����и���
{
    if(!r) return;
    val[r]+=value;
    m[r]+=value;
    add[r]+=value;
}

void update_rev(int r)///���²��������ڷ�ת���ɸ�����ĿҪ����и���
{
    if(!r) return ;
    swap(ch[r][0],ch[r][1]);
    rev[r]^=1;
}

void splay_push_up(int rt)///push_up�����������߶���
///ע�⣡����push_up����ͨ���ڻ���ʱ�͸��Ľڵ�����
{
    int l=ch[rt][0],r=ch[rt][1];
    s[rt]=s[r]+s[l]+1;
    m[rt]=min(min(m[l],m[r]),val[rt]);
    return ;
}

void splay_push_down(int rt)///push_down���������ڸ��������ǣ�����ѡ����
///ע�⣡����push_down������Ҫ��get_kth��get_min��get_max����ɣ���ʾһֱ�������Ƶ���Ҫ��Ľڵ�
///��·�������нڵ�����ɸ��ģ���˿ɽ��к�������
///���º�push_down���Էֿ���ɣ�ʹ����ṹ����
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

void build(int &rt,int l,int r,int father)///�ݹ齨���������������߶�����ÿ���ڵ�ֵΪ���������ж�Ӧλ�õ�ֵ
///ÿ���ڵ������ж�Ӧ��λ��������������Ϣ����ʵ���ǰ��սڵ��ʾ��λ��˳���С��������
///�ڵ�ı����ֵ���뽨����ʽ�޹�
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

void init()///��ʼ����������ǰ������ڱ��ڵ㣬�ֱ��ø��ڵ�����ڵ��Ҷ��ӣ����Ը��ڵ��Ҷ��ӵ������Ϊ������
///�����ڱ��ڵ���Ϊ�˴�����������ߺ����ұߵ����
{
    root=total=total2=pre[0]=val[0]=ch[0][0]=ch[0][1]=add[0]=0;///��ʼ��Ҫȫ����������������1
    s[0]=0;
    m[root]=inf;
    splay_new_node(root,0,inf);///�ڱ��ڵ��ֵ������ĿҪ��ͬ����ͬ
    splay_new_node(ch[root][1],root,inf);
    build(key_value,1,n,ch[root][1]);///����
    splay_push_up(ch[root][1]);///���½ڵ���Ϣ
    splay_push_up(root);
}

void splay_rotate(int r,int flag)///��ת������push_down��push_up
{
    int tmp=pre[r];
//    splay_push_down(tmp);///�����ԣ�������push_down�ڱ����в�Ӱ��������ע�͵�����������������
//    splay_push_down(r);///�п�������Ϊ��ѯʱ�Ѿ�push_down���ˣ����rotate��push_down�����壿��Ҫ��֮����Ŀ���ؽ�������
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

int splay_max(int r)///��ѯ��rΪ���ڵ�����������ڵ㣬���������ұߵ�������ѯ���̰���push_down
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

int splay_min(int r)///��ѯ��rΪ���ڵ����������С�ڵ㣬����������ߵ�������ѯ���̰���push_down
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
    update_rev(key_value);///�����Ǹ����Ҷ��ӵ�����ӣ�����֮��һЩ�в���ʹ���������ת
}

void splay_add(int a,int b,int c)///ͬ��ת����
{
    int x=splay_get_kth(root,a);
    int y=splay_get_kth(root,b+2);
    splay(x,0);
    splay(y,root);
    update_add(key_value,c);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_insert(int a,int b)///�����������a֮�����һ����������һ����ԭ����ͬ
{
    int x=splay_get_kth(root,a+1);
    int y=splay_get_kth(root,a+2);
    splay(x,0);
    splay(y,root);
    splay_new_node(key_value,ch[root][1],b);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_erase(int r)///ɾ������������ͬʱ��ɾȥ���ڴ汣������
{
    if(!r) return;
    s2[++total2]=r;
    splay_erase(ch[r][0]);
    splay_erase(ch[r][1]);
}

void splay_delete(int a,int b)///ɾ��a��b֮������У�ԭ��ͬ�������
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

int splay_Min(int a,int b)///��ѯa��b���е���Сֵ�����Ը�����ĿҪ������������ݣ�ԭ��ͬ��
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
            else if(str2=="REVOLVE")///����Ĺؼ�����ת���������Խ���ת����c���߶γ�ȡģ��Ȼ��ת��Ϊ���в���
            {
                scanf("%d%d%d",&a,&b,&c);
                int len=b-a+1;
                c=(c%len+len)%len;
                if(c==0)
                {
                    continue;
                }
                splay_cut(b-c+1,b,a-1);///ת����ļ��в���
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
