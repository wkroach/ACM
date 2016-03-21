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
#define N 50
#define M 50
#define INF 0x3f3f3f3f
using namespace std;
int n,m,k=0;
double dp[N*M+5][M+5][N+5];///��ά����dp,dp[i][j][k]��ʾ������j��k��ʱ����i��ĸ���
int main()
{
//    freopen("input.txt","r",stdin);
    int t;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&m,&n);
        dp[0][0][0]=1;
        dp[1][1][1]=1.0;
        for(int i=1;i<n*m;++i)
            for(int j=1;j<=m;++j)
                for(int k=1;k<=n;++k)
                {
                    if(dp[i][j][k]>0)
                    ///4�������
                    ///1����������ǰ״̬����һ
                    ///2���м�һ���в���
                    ///3���м�һ���в���
                    ///4��״̬Ϊ�ı䣬�����ӵĵ����ѿ��Ƶķ�Χ��
                    {
                        dp[i+1][j+1][k+1]+=dp[i][j][k]*(m-j)*(n-k)/(n*m-i);
                        dp[i+1][j+1][k]+=dp[i][j][k]*(m-j)*k/(n*m-i);
                        dp[i+1][j][k+1]+=dp[i][j][k]*(n-k)*j/(n*m-i);
                        if(j<m||k<n)///��״̬�����жϵ�4���������Ϊһ���ﵽ��״̬��������Ͷ��
                            dp[i+1][j][k]+=dp[i][j][k]*(j*k-i)/(n*m-i);
                    }
                }
        double E=0;
        for(int i=1;i<=n*m;++i)
        {
            E+=i*dp[i][m][n];
//            printf("%lf ",dp[i][m][n]);
        }
        printf("%.12lf\n",E);
    }
    return 0;
}
