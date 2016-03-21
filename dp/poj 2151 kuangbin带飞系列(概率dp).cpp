
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
#define M 30
#define ULL unsinged long long
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
///������Ҫ�����ʵĻ���֪ʶ(��ûع�һ�¿α�):
///����֪ʶ1,��p(ab)=p(a)-P(a(~b))
///����֪ʶ2��p(a)=p(a1)+p(a2)+p(a3)+......p(an),a1,a2,a3..an������a���໥����
///�������Ķ�����������n��==������һ��������������n�⣨�������������ȣ����Եȼۣ�
int n,m,k,t;
double dp[N+5][M+5][M+5];///��ǰ��i�����飬����j����ʱ���Ѿ�����k����ĸ���
double arr[N+5][M+5];///��i������������j����ĸ���
double s[N+5][M+5];///��i����������������j����ĸ���
int main()
{
//    freopen("input.txt","r",stdin);
//    scanf("%d",&t);
    int Case=1;
//    while(t--)
//    {
    while(scanf("%d%d%d",&m,&t,&n)==3)
    {
        if(!m&&!n&&!t) break;
        memset(dp,0,sizeof(dp));
        memset(arr,0,sizeof(arr));
        memset(s,0,sizeof(s));
        double ans=1.0;
        for(int i=1;i<=t;++i)
        {
            for(int j=1;j<=m;++j)
            {
                scanf("%lf",&arr[i][j]);
            }
        }
        for(int i=1;i<=t;++i)
        {
            double tmp=1.0;
            dp[i][0][0]=1.0;///�ڵ�0����ʱ����0����ĸ�����ȻΪ0
            for(int j=1;j<=m;++j)
            {
                tmp*=(1-arr[i][j]);
                dp[i][j][0]=tmp;
                for(int k=1;k<=j;++k)///��Ϊ1����j-1��ʱ�Ѿ�������k�⣬��j��δ������
                    ///2����j-1��ʱ�Ѿ�����k-1�⣬��j��������
                {
                    dp[i][j][k]=dp[i][j-1][k]*(1-arr[i][j])+dp[i][j-1][k-1]*arr[i][j];
                }
            }
            ans*=(1-dp[i][m][0]);///ÿ��������������һ��ĸ���,��p(a)
        }
        double tmp=1.0;
        for(int i=1;i<=t;++i)
        {
            s[i][0]=dp[i][m][0];
            for(int j=0;j<=n-1;++j)///����֪ʶ2
            {
                s[i][n-1]+=dp[i][m][j];
            }
            tmp*=(s[i][n-1]-s[i][0]);///tmo��ʾ���ж����Ϊ����n�����Ҿ���������1��
            ///����֪ʶ1��tmp��p(a(~b))
        }
        printf("%.3lf\n",ans-tmp);///��p(ab),ÿ�����鶼��������1�⣬�Ҵ���һ֧������������n��
    }
//    }
    return 0;
}
