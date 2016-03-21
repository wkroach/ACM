 Graph and Queries#include<cstdio>
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
//#include<bits/stdc++.h>
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
    int x;
    int y;
    bool friend operator <(const node& a,const node& b)
    {
//        return a.x==b.x?a.y<b.y:a.x<b.x;
          return a.x<b.x||(a.x==b.x&&a.y<b.y);
    }
};
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t;
    char str[10];
    int a,b,c;
    cin>>t;
    multiset<node> s;
    int Case=0;
    while(t--)
    {
        if(Case)
        {
            printf("\n");
        }
        printf("Case #%d:\n",++Case);
        s.clear();
        multiset<node>:: iterator it=s.begin();
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            node tmp;
            scanf("%d%d",&tmp.x,&tmp.y);
            it=s.lower_bound(tmp);
            if(it==s.begin()||(--it)->y>tmp.y)
            {
                s.insert(tmp);
                it=s.upper_bound(tmp);
                for(;it!=s.end()&&it->y>=tmp.y;)
                {
                        s.erase(it++);///不能用s.erase(it); it++ ！！！！！！！！否则指针有可能变成野指针
                }
            }
            printf("%d\n",s.size());
        }
    }
    return 0;
}
