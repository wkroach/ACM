
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define eps 1e-9
#define N 1000
#define M 50
#define INF 0x3f3f3f3f
using namespace std;


int n,m,t;
double dp[N+5][N+5];
int main()
{
//    freopen("input.txt","r",stdin);
    scanf("%d",&t);
    int Case=1;
    while(t--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        double ans=1.0;
        if(n&1)///���������£�¹�Ĵ������Ӱ��������Ϊ���ᱻ�ȳԵ�
            ///�����ϻ���ĿΪ����ʱ������������������Ȼʣһ���ϻ�������
        {
            ans=0;
        }
        else if(n)
        {
            while(n)///��ѧ���ʽ��ans=(n-1)/(n+1)*(n-3)/(n-1)......*1/3
            ///(n-1)*n/((n+1)*n)��ÿ������nֻ�ϻ�ʱ�ܹ����ĸ���
            {
                ans*=(n*1.0-1)/(n*1.0+1);
                n-=2;
            }
        }
        else
        {
            ans=1;
        }
        printf("Case %d: ",Case++);
        printf("%.7lf\n",ans);
    }
    return 0;
}
