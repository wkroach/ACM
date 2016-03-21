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
#define Size 105
#define inf 2e9
#define INF 2e18
#define LL long long
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
///���鼯������
int n,m,k;
int fa[50005],relate[50005];///faͬ��ͨ���鼯��relate[i]��ʾi�ĸ��ڵ㵽i��ƫ����
///������i��jƫ����Ϊ0��ʾ����ͬ�࣬Ϊ1��ʾi��j��Ϊ2��ʾj��i

void init()///��ʼ��
{
    for(int i=1;i<=n;++i)
    {
        fa[i]=i;
    }
    memset(relate,0,sizeof(relate));///��ʼʱ��ÿ���ڵ���ڵ㶼���Լ���ƫ����Ϊ0
}

int find_fa(int a)///�ص㣡������·��ѹ���Ĳ�ѯ
{
    if(fa[a]==a)
    {
        return fa[a];
    }
    int tmp=fa[a];///�ȱ���ڵ�ĵ�ǰ���ڵ㣬��Ϊ����ݹ�ѹ���п���ʹ���������ڵ㲻Ϊ��ǰ�ĸ��ڵ�
    fa[a] = find_fa(fa[a]);
    relate[a]=(relate[a]+relate[tmp])%3;///�ص㣬����ƫ�Ƶ��������ʽ
    ///grandfa->son = grandfa->fa + fa->son
    ///���ݸ��¸��ڵ���������нڵ��ƫ����
    ///����ƫ�����ķ�Χ��3�����Ҫ��3ȡģ
    return fa[a];
}

void unio(int a,int b,int x,int y,int d)///�ص㣡��������Ȩ���ȣ��ϲ��ĺϲ�
{
    fa[b]=a;
    relate[b]=(relate[x]+d-1+3-relate[y])%3;///����ƫ��
    ///b->a = b->x + x->y +y->a
    ///x->y��������������ʱ��D�Ƴ�����Ӧ����d-1
    ///�ص㣡��fa->son = (3 - son->fa)%3 �ɶԳ��Կɵã�
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int d,x,y;
    scanf("%d%d",&n,&m);///ע�⣬����ֻ��һ����������
    init();
    int ans=0;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&d,&x,&y);
        if(x>n||y>n)
        {
            ans++;
        }
        else if(d==2&&x==y)
        {
            ans++;
        }
        else
        {
            int a,b;
            a=find_fa(x);
            b=find_fa(y);
            if(a!=b)///���a,b������ͬһ���У��Ⱥϲ�����Ĭ�Ϻϲ����ƫ����Ϊ��
            {
                unio(a,b,x,y,d);
            }
            else
            {
                int tmp=(3-relate[x]+relate[y])%3;///����Ѿ���ͬһ���У��ж�����ʵ�ʵ�����ƫ�����Ƿ�����������ͬ
                if(d-1!=tmp)
                {
                    ans++;
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}








