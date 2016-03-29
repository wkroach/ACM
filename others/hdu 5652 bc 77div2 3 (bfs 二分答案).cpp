#include<cstdio>
#include<cstdlib>
#include<time.h>
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

//#include<bits/c++std.h>

#define Size 1000005
#define inf 2e9
#define INF 2e18
#define LL long long int
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
using namespace std;
int n,m,k;
int ql,qr,pos;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};

struct node
{
    int x,y;
    int val;
    int num;
    node():x(0),y(0),val(0),num(0){}
};

int maze[505][505];
node maze2[505][505];
int vis[505][505];

void maze_input(int r,int c)///�ص㣬���ڴ��⣬�������������һ�ſյ㣬��������һ���㣬���ɱ�֤ԭ��һ�ž����������������˶�ԭ��һ��ÿ��λ������ʼ������
{
    char s[506];
    for(int i=1;i<=r;++i)
    {
        scanf("%s",s);
        for(int j=0;j<c;++j)
        {
            maze[i][j] = s[j]-'0';
        }
    }
}

void maze_output()
{
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<m;++j)
        {
            cout<<maze[i][j];
        }
        cout<<endl;
    }
}


bool good(node tmp, int t)
{
    int x = tmp.x;
    int y = tmp.y;
    if(vis[x][y])
        return false;
    if(x<0||x>n)
        return false;
    if(y<0||y>=m)
        return false;
    if(maze[x][y])
        return false;
    if(maze2[x][y].val == 1 && maze2[x][y].num <= t)
        return false;
    return true;
}

bool bfs(int t)///bfs��ע��ÿ������ǰҪ��ʼ��vis����
{
    memset(vis,0,sizeof(vis));///�ǵó�ʼ������������������������������
    node s;
    queue<node> q;
    while(!q.empty())
        q.pop();
    q.push(s);
    while(!q.empty())
    {
        node tmp = q.front();
//        cout<<tmp.x<<" "<<tmp.y<<endl;
        if(tmp.x == n)
            return true;
        node tmp2;
        for(int i=0;i<4;++i)
        {
            tmp2.x = tmp.x + dir[i][0];
            tmp2.y = tmp.y + dir[i][1];
            if(good(tmp2,t))
            {
                vis[tmp2.x][tmp2.y] = 1;
                q.push(tmp2);
            }
        }
        q.pop();
    }
    return false;
}

int bis(int s, int e)
{
    int l = s, r = e;///���ֺ���˼�룬��Ҫ�ҵĽ������[l,r] �У���С��Χֱ���������1������ѡȡ�����ұ߽��Ƿ�Ϊǰһ��mid�����Ƿ���ʹ�����ѡ��ȡ����ʽ
  /*  if(!bfs(s))
        return 0;
    while(l < r)
    {
        int mid = (l + r + 1) / 2;///���ڵ�r = l + 1ʱ���ܻ�����ѭ����Ҫ����ȡ��
        bool judge = bfs(mid);

        if(judge)
        {
            l = mid;///ÿ�����䣬�ڳ�ʼֵ�����е�����£�l��Ϊǰһ����mid�Ѿ��жϹ�
        }
        else
        {
            r = mid - 1;
        }
    }
    if(l == e) return -1;
    return l + 1;
    */ ///����д��1���ҳ�����ͨ�е�����һ�� �ټ�һ(����ڿ��н����upper_bound)��Ҫ�ж϶�����ͨ�е��������ʼ����Ƿ���ͨ��

    if(bfs(e))
        return -1;
    while(l<r)
    {
        int mid = (l + r)/2;
        bool judge = bfs(mid);
        if(judge)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;///ÿ�����䣬��ĩβֵ�����е�����£�r��Ϊǰһ����mid�Ѿ��жϹ�
        }
    }
    return l;///����д��2���ҵ������еĵ�һ�꣨����ڲ����н����lower_bound), Ҫ�ж϶���ͨ�м����һ������
}
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&t)&&t)
    {
        cin>>n>>m;
        memset(maze,0,sizeof(maze));
        memset(maze2,0,sizeof(maze2));
        maze_input(n,m);
//        maze_output();
        cin>>k;
        for(int i=1;i<=k;++i)
        {
            cin>>x>>y;
            maze2[x+1][y].val = 1;
            maze2[x+1][y].num = i;
        }
        cout<<bis(0,k)<<endl;///��������������ӣ�ɽԽ�࣬��ͨ�Ŀ�����Խ�ͣ����������ģ����Զ��ִ�
    }
    return 0;
}

