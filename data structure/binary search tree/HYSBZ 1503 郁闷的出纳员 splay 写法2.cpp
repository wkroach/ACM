

///splay�ⷨ2��������Ŀ��Ҫ��������ȫ���ڵ��ֵ�����Կ�����һ��cnt������ʾ�ı���ܵ�ֵ
///Ҫע���¼ӽ����Ľڵ�Ӧ�����ܵ�ǰcntӰ�죬Ϊ��cnt��Ӱ�죬Ҫ�ȼ�����ǰcnt��ֵ

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
#define N 100005///splay���ڵ��ŵ��ڴ��
#define M 100005
#define inf 1e9
#define INF 1LLe18
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
#define key_value ch[ch[root][1]][0]
int n,m;
int pre[N],ch[N][2],val[N],root,total;///pre��ʾ���ڵ㣬ch��ʾ���ӽڵ㣬val��ʾ�ڵ���ֵ��root��ʾ����total��ʾ���Ĺ�ģ
int s[N],rev[N];///s��ʾÿ�������Ĺ�ģ��rev��ʾ������
int num[N],s2[N];///���ڿ�����ֵ�ظ��Ľڵ㣬num������Ŵ˽ڵ��ظ��ĸ�������û���ظ��ڵ���Ϊ1,s2��ʾ����ʵ�ʹ�ģ��ʵ�ʱ�ʾ��r�ĸ�����
int sum=0,cnt;///�ܹ��뿪��Ա����

void Treaval(int x) {
    if(x) {
        Treaval(ch[x][0]);
        printf("���%2d:����� %2d �Ҷ��� %2d ����� %2d size = %2d ,val = %2d \n",x,ch[x][0],ch[x][1],pre[x],s[x],val[x]);
        Treaval(ch[x][1]);
    }
}
void debug() {printf("%d\n",root);Treaval(root);}
void splay_new_node(int &r,int father,int value)///�����½ڵ㣬�����нڵ��ʼ��
{
    r=++total;
    pre[r]=father;
    val[r]=value;
    s[r]=s2[r]=1;
    num[r]=1;
    ch[r][0]=ch[r][1]=0;
    return ;
}

void splay_push_up(int r)///push_up�����������߶������ڸ��½ڵ��size������rΪ�������Ĵ�С���ڵ������
///ע�⣡����push_up����ͨ���ڻ���ʱ�͸��Ľڵ�����
{
    s[r]=s[ch[r][1]]+s[ch[r][0]]+1;
    s2[r]=s2[ch[r][1]]+s2[ch[r][0]]+num[r];
    return ;
}

void init()///��ʼ����������ǰ������ڱ��ڵ㣬�ֱ��ø��ڵ�����ڵ��Ҷ��ӣ����Ը��ڵ��Ҷ��ӵ������Ϊ������
{
    root=total=pre[0]=val[0]=s2[0]=s[0]=num[0]=0;
    ch[0][0]=ch[0][1]=0;
    splay_new_node(root,0,-inf);
    splay_new_node(ch[root][1],root,inf);
    splay_push_up(ch[root][1]);
    splay_push_up(root);
}

void splay_rotate(int r,int flag)///��ת������push_up
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
    splay_push_up(tmp);///����splay��ת�ķ�ʽ�����ӽڵ���splay����¼��ɣ�������ÿ�ζ�Ҫ����
}

void splay_low(int r,int goal)///��Ч���splay������д�������˻�ΪO(n)�������д
///�����е���Ҳ���ԣ�Ч����˫������
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

void splay(int r,int goal)///��Ч���˫��splay������push_up����
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
    splay_push_up(r);///����rotate��ɺ��ٸ��¶��ӽڵ㣬����Ч�ʡ����ڵ�ĸ�����rotate�����
    if(goal==0)
    {
        root=r;
    }
}

void splay_insert(int r,int value)///splay ����ڵ㣬valueΪ������ڵ��ֵ
{
    while(ch[r][val[r]<value])///ѭ������ֵ����λ��
    {
        if(val[r]==value)///�ظ��Ĳ�����
        {
            num[r]++;
            splay(r,0);
            return ;
        }
        r=ch[r][val[r]<value];
//        cout<<"debug"<<endl;
    }
    splay_new_node(ch[r][val[r]<value],r,value);///�����½ڵ�
    splay_push_up(r);
    splay_push_up(ch[r][val[r]<value]);
//    cout<<"debug"<<endl;
    splay(ch[r][value>val[r]],0);///splay����
//    cout<<"debug"<<endl;
}

int splay_get_val_kth(int r,int k)///����rΪ����������������еĵ�k����������push_down����
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

int splay_max(int r)///��ѯ��rΪ���ڵ�����������ڵ�
{
    int tmp=r;
    while(ch[tmp][1])
    {
        tmp=ch[tmp][1];
    }
    return tmp;
}

int splay_min(int r)///��ѯ��rΪ���ڵ����������С�ڵ�
{
    int tmp=r;
    while(ch[tmp][0])
    {
        tmp=ch[tmp][0];
    }
    return tmp;
}

int splay_search_acc(int r,int k)///�ص㣡��������ֵ���ڵ���k�ĵ�һ���ڵ㣬��ֵk�ĺ�̼�ֵΪk�Ľڵ�
{
    int tmp=r;
    while(ch[r][val[r]<k])///���ҵ��ڵ��λ�û�Ӧ�ý����λ��
    {
        if(val[r]==k)
        {
            return r;
        }
        r=ch[r][val[r]<k];
    }
    if(val[r]>k)///�����ڵ�����Ҫ��ֱ�ӷ��ؽ��
    {
        return r;
    }
    while(r!=tmp&&k>val[r])///����ͬ��������ѯ��̽ڵ㣬��Ҫ��ǰ����
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
    splay(1,0);///���������ڱ��ڵ�ı���Ѿ�ȷ�����Ҳ����ٸ��ģ�����ֱ����չ������Ҫ�ٲ���
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
        init();///��ʼ������Ҫ��������������������������������������������������������������������
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
                splay_insert(root,k-cnt);///�������нڵ�ֵ�ĸı���cnt�����棬����²���ڵ�Ҫ�ȼ�ȥcnt
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
                if(s2[root]<k+2)///ע�⣬��ĿҪ���k���ֵ��������С��������෴�����Ҫ������
                {
                    printf("-1\n");
                    continue;
                }
//                debug();
                int ans=splay_get_val_kth(root,s2[root]-k);
                printf("%d\n",val[ans]+cnt);///������Ҫ���ϸñ���cnt
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}
