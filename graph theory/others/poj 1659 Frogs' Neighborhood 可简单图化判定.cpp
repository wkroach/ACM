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
        for(int i=0;i<n;++i)///对于可图化，度数和能被2整除即可
                            ///Havel—Hakimi定理：先将度数列从大到小排序，从前往后，对于当前结点i
                            ///对它之后所有点从大到小排序，将后v[i]个点度数均减1，循环进行
                            ///若存在当前结点度数为负，则无法简单图化，当前结点度数大于后面节点数个数时也无法简单图化
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
