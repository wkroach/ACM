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
#define MOD 1000000007
#define N 15
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int a,b;
    while(scanf("%d%d",&a,&b)==2)
    {
        int tmp;
        if(b>a)///特判，b>a,a%b==0时可以直接得出结论
        {
            printf("-1\n");
            continue;
        }
        else if(a%b==0)
        {
            tmp=a/b;
            if(tmp&1)
            {
                printf("%.9lf\n",(double)b);
                continue;
            }
        }
        ///公式：x=(a+b)/(2*n)  n=1,2,3,4,5,....  x>=b;
        ///二分查找大于x的第一个值（类似lower_bound)
        double cnt=(double)a+(double)b;
        if((int)cnt&1) tmp=(int)cnt-1;///定二分上界
        else tmp=(int)cnt;
//        printf("%d ",tmp);
        int mid=2+(tmp)/2;
        double x;
        x=cnt/mid;
        int s=2;
        int e=tmp;
        while(s<=e)///二分查找，因为是找lower_bound，所以s可以等于e
        {
            mid=(s+e)/2;
            if(mid&1) mid--;
            x=cnt/mid;
            if(x<b)
            {
                e=mid-2;
            }
            else
            {
                s=mid+2;
            }
        }
//        printf("%d %d ",s,e);
        if(x<b) x=cnt/e;///由于找出的x可能小于b，要判断
        printf("%.9lf\n",x);
    }
    return 0;
}
