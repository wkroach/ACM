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
int n,m;

struct node
{
    int v;
    int num;
};
bool cmd(node a,node b)
{
    return a.v>b.v;
}
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    char str[10];
    node arr[20];
    int maze[15][15];
    int a,b,c;
    cin>>t;
    while(t--)
    {
        memset(maze,0,sizeof(maze));
        scanf("%d",&n);
        node tmp;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&arr[i].v);
            arr[i].num=i;
        }
//        for(int i=0;i<n;++i)
//        {
//            printf("%d ",arr[i].v);
//        }
        int flag=1;
        for(int i=0;i<n;++i)///���ڿ�ͼ�����������ܱ�2��������
                            ///Havel��Hakimi�����Ƚ������дӴ�С���򣬴�ǰ���󣬶��ڵ�ǰ���i
                            ///����֮�����е�Ӵ�С���򣬽���v[i]�����������1��ѭ������
                            ///�����ڵ�ǰ������Ϊ�������޷���ͼ������ǰ���������ں���ڵ�������ʱҲ�޷���ͼ��
        {
            sort(arr+i,arr+n,cmd);
            if(arr[i].v>n-i-1)
            {
                flag=0;
                break;
            }
            if(arr[i].v<0)
            {
                flag=0;
                break;
            }
            for(int j=i+1;j<n;++j)
            {
                if(arr[i].v==0)
                {
                    break;
                }
                arr[j].v-=1;
                arr[i].v-=1;
                maze[arr[i].num][arr[j].num]=1;
                maze[arr[j].num][arr[i].num]=1;
            }
        }
        if(!flag)
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
            for(int i=0; i<n; ++i)
            {
                for(int j=0; j<n; ++j)
                {
                    if(j)
                    {
                        printf(" ");
                    }
                    printf("%d ",maze[i][j]);
                }
                puts("");
            }
        }
        if(t)
        {
            puts("");
        }
    }
    return 0;
}
