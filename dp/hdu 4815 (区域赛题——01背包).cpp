//���
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define N 100005
int arr[100];
int dp[40005];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t,n;
    double p;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d%lf",&n,&p);
        for(int i=1;i<=n;++i)
            scanf("%d",&arr[i]);
        dp[0]=1;
        ///dp����01��������
        for(int i=1;i<=n;++i)///ö��ÿһ���⣨��Ʒ��
            for(int j=40000;j>=arr[i];--j)///ö�ٷ��������������Ӻ���ǰɨ�����������
                if(dp[j-arr[i]])///��� ��ǰö�ٵķ��� ��ȥ ��ǰö�ٵ���Ŀ���� ���������
                    dp[j]+=dp[j-arr[i]];///����ϴ���Ŀ����Ʒ������jֵ���ڵķ������ټ���j-arr[i]�ķ����������������������米������
        double sum=0,k=(1LL<<n);
        for(int i=0;i<=40000;++i)
        {
            sum+=((double)dp[i]/k);
            if(sum>=p)
            {
                printf("%d\n",i);
                break;
            }
        }
//        for(int i=0;i<=20;++i)
//            printf("%d ",dp[i]);
//        puts("");
    }
    return 0;
}

