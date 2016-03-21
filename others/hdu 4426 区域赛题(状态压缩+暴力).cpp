#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<string>
#include<map>
#include<set>
#define N 112345
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
int g[55][55][15];
int vis[55][55];
struct node
{
    int x;
    int y;
    int r;
};
set <int> ans;///用集合存放解，输出最小的解，即第一个元素
int flag;

bool judge()
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
        {
            if(vis[i][j])
                continue;
            if(!g[i][j][0])
                return false;
        }
    return true;
}

void solve()
{
    if(judge())///可能每个点都是稻草人，直接输出0
    {
        ans.insert(0);
        return ;
    }
//    cout<<1;
    vector <int> arr2;
//    cout<<1;
    int tmp=0,cnt=1,cnt2=0,flag1=0;
    for(int i=0;i<=(1<<m)-1;++i)///状态压缩，用二进制模拟选择稻草人，一共2^m种可能
    {
//        cout<<1;
        cnt=1;
        cnt2=0;
        flag1=0;
        arr2.clear();
        for(int j=0;j<m;++j)
        {
            if(i&(1<<j))
            {
                cnt2++;
                arr2.push_back(j+1);
            }
        }
//        cout<<1;
        for(int j=1;j<=n;++j)///大暴力
        {
            for(int k=1;k<=n;++k)
            {
                if(vis[j][k])
                    continue;
//                cout<<1;
                for(int l=0;l<arr2.size();++l)
                {
//                    cout<<1;
                    if(g[j][k][arr2[l]])
                    {
//                        g[j][k][0]=1;
                        flag1=1;
                        break;
                    }
                }
                if(!flag1)
                {
                    goto there;
                }
                flag1=0;
            }
        }
//        cout<<1;
        ans.insert(cnt2);
        there:;
    }
}

int main()
{
//    int i,j,k,kk,t;
//    freopen("input.txt","r",stdin);
//    scanf("%d",&k);
//    kk=0;
//    while(k--)
//    cout<<1;
//    scanf("%d",&t);
    while(scanf("%d",&n)==1&&n)
    {
        flag=0;
        vector<node> arr;
        ans.clear();
        memset(g,0,sizeof(g));
        memset(vis,0,sizeof(vis));
        scanf("%d",&m);
        for(int i=0;i<m;++i)
        {
            node tmp;
            scanf("%d%d",&tmp.x,&tmp.y);
            vis[tmp.x][tmp.y]=1;
            arr.push_back(tmp);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d",&arr[i].r);
        }
        for(int i=1;i<=n;++i)///将每个点的所属稻草人记录下来
        {
            for(int j=1;j<=n;++j)
            {
                if(vis[i][j])
                    continue;
                for(int k=0;k<arr.size();++k)
                {
                    if(abs(arr[k].x-i)+abs(arr[k].y-j)<=arr[k].r)
                        g[i][j][k+1]=1;
                }
            }
        }
//        cout<<1;
        solve();
//        cout<<1;
        if(ans.empty())///如果没有可行解，输出-1
            flag=1;
        if(flag)
        {
            printf("-1\n");
            continue;
        }
        printf("%d\n",*ans.begin());
    }
    return 0;
}
