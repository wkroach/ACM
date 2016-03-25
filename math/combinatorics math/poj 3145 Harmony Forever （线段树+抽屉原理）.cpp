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
#define Mod 1000000007///题目数据有误，要开两倍数据
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
using namespace std;
int n,m,k;
int ql,qr,pos;
int minm[Size*4],vis[Size];///vis记录插入的次序
int arr[Size];

void push_up(int now,int l,int r)
{
    int mid = l+(r-l)/2;
    minm[now] = min(minm[now<<1] , minm[now<<1|1]);
}

void build(int now,int l,int r)
{
    minm[now] = inf;
    if(l==r)
    {
        return ;
    }
    build(lson);
    build(rson);
}

int update(int now,int l,int r)
{
    int mid = l+(r-l)/2;
    if(l == r) return minm[now] = pos;
    if(pos <= mid) update(lson);
    if(pos > mid)  update(rson);
    push_up(now,l,r);
}

int quire(int now,int l,int r)
{
    int mid = l+(r-l)/2;
    if(ql <= l && r <= qr)
    {
        return minm[now];
    }
    int ans1 = inf,ans2 = inf;
    if(ql <= mid) ans1 = quire(lson);
    if(qr > mid) ans2 = quire(rson);
    return min(ans1,ans2);
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
//    cin>>t;
//    while(t--)
    while(scanf("%d",&t)&&t)
    {
        if(Case)
        {
            printf("\n");
        }
        printf("Case %d:\n",++Case);
        char s[2];
        int tmp;
        int cnt = 1;
        memset(vis,0,sizeof(vis));
        memset(arr,0,sizeof(arr));
        build(1,0,Size);
//        cout<<1<<endl;
        for(int i = 1 ; i <= t ; ++i)
        {
            scanf("%s%d",s,&tmp);
            if(s[0] == 'A')
            {
                if(tmp > 5000)///由于当y较小时线段树效率较低，不如直接暴力来的快
                {///线段树，复杂度O(log(Size)*Size/tmp)
                    int ans = -1;
                    int tmp_ans = inf;
                    int time = Size/tmp;
                    for(int i=0 ; i < time ; ++i)///将线段分为长为y的若干段，分段求出最小值，则一定是当前段中的模y最小值
                    {
                        ql = i * tmp;
                        qr = (i+1) * tmp-1;
                        int tmpos = quire(1,0,Size);
//                        cout<<tmpos<<endl;
                        if(tmpos == inf)
                        {
                            continue;
                        }
                        else
                        {
                            if(tmp_ans > tmpos%tmp)///找出所有线段中模数最小的值选其插入时间，如果有相等的情况，则还要去插入时间靠后的那个
                            {
//                                cout<<tmpos<<endl;
                                ans = vis[tmpos];
                                tmp_ans = tmpos%tmp;
                            }
                            else if(tmp_ans == tmpos%tmp)
                            {
                                ans = max(ans, vis[tmpos]);
                            }
                        }
                    }///总长度可能除不尽y，要将剩余部分也做一次查询
                    ql = qr + 1;
                    qr = Size;
                    int tmpos = quire(1, 0, Size);
                    if(tmpos != inf && tmp_ans > tmpos % tmp)
                    {
                        ans = vis[tmpos];
                        tmp_ans = tmpos % tmp;
                    }
                    else if(tmpos != inf && tmp_ans == tmpos%tmp)
                    {
                        ans = max(ans, vis[tmpos]);
                    }
                    printf("%d\n",ans);
                }
                else
                {///暴力，复杂度O(T)
                    int ans = -1;
                    int tmp_ans = inf;
                    for(int i=cnt-1 ; i > 0 ; --i)///从后往前找更快
                    {

                        if(vis[arr[i]])
                        {
                            if(arr[i] % tmp == 0)
                            {
                                ans = i;
                                break;
                            }
                            if(tmp_ans > arr[i]%tmp)
                            {
                                ans = i;
                                tmp_ans = arr[i]%tmp;
                            }
                        }
                    }
                    printf("%d\n",ans);
                }
            }
            else if(s[0] == 'B')
            {
                pos = tmp;
                arr[cnt] = pos;
                vis[pos] = cnt++;
                update(1,0,Size);
            }
        }
    }
    return 0;
}

