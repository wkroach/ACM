
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
#define N 50
#define M 50
#define INF 0x3f3f3f3f
using namespace std;


///高斯消元，kuang bin 的模板
///以0位起始位置！！！！！！！
//const double eps=1e-9;
const int MAXN=220;
const double eps=1e-9;

double a[MAXN][MAXN],x[MAXN];///方程的左边的矩阵和等式右边的值，求解之后x存的就是结果
///kuang bin的模板没有使用增广阵，而是直接用x[]存放矩阵右边的值并在求解之后存放解
int equ,var;///方程数和未知数个数
/*
*返回0表示无解，1表示有解
*/
int Gauss()
{
    int i,j,k,col,max_r;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
    for(i=k+1;i<equ;i++)
        if(fabs(a[i][col])>fabs(a[max_r][col]))
            max_r=i;
    if(fabs(a[max_r][col])<eps)return 0;
    if(k!=max_r)
    {
        for(j=col;j<var;j++)
            swap(a[k][j],a[max_r][j]);
        swap(x[k],x[max_r]);
    }
    x[k]/=a[k][col];
    for(j=col+1;j<var;j++)a[k][j]/=a[k][col];
    a[k][col]=1;
    for(i=0;i<equ;i++)
        if(i!=k)
        {
            x[i]-=x[k]*a[i][k];
            for(j=col+1;j<var;j++)a[i][j]-=a[k][j]*a[i][col];
            a[i][col]=0;
        }
    }
    return 1;
}

int n,m,t;

int main()
{
    freopen("input.txt","r",stdin);
    int go[205];///用于表示状态的转移（蛇和梯子），本质是改变了一个方程
    equ=var=100;
    scanf("%d",&t);
    int Case=1;
    while(t--)
    {
        memset(a,0,sizeof(a));
        memset(x,0,sizeof(x));
        scanf("%d",&n);
        for(int i = 0;i < 105;++i)
        {
            go[i]=i;
        }
        for(int i = 0;i < n;++i)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            go[a]=b;
        }
        for(int i = 1;i <= equ;++i)
        {
            if(go[i]!=i)
            ///将项的转移写成一个恒等方程
            {
                a[i-1][i-1]=1.0;///所需求解的项，系数为1
                a[i-1][go[i]-1]=-1.0;///与之相关的项
                x[i-1]=0.0;
            }
            else if(i+6<=equ)///1*dp[i]=-(1/6)*(dp[i+1]+dp[i+2]+...dp[i+6])+1
            {
                a[i-1][i-1]=1.0;
                for(int j=1;j<=6;++j)
                {
                    a[i-1][i + j-1] = - (1.0/6.0);
                }
                x[i-1] = 1.0;
            }
            else///1*dp[i]=-(1/6)*(dp[i+1]+dp[i+2]+...dp[100]+(i+6-100)*dp[i])+1
                ///超出100的点视为没有走，所以是dp[i]，但是依旧视为投过了点，所以系数还是-(1.0/6.0)
            {
                a[i-1][i-1] = (100.0-i)/6.0;///化简后的dp[i]的系数
                for(int j=1;j<=equ-i;++j)
                {
                    a[i-1][i-1 + j]= -(1.0/6.0);
                }
                x[i-1]=1.0;
            }
        }
        a[equ-1][equ-1]=1.0;///dp[100]=0,等价于1.0*dp[100]=0
        x[var-1]=0.0;
       int ans= Gauss();
//       for(int i=0;i<=equ;++i)
//        cout<<x[i]<<endl;
        printf("Case %d: ",Case++);
        printf("%lf\n",x[0]);///要求的结果是dp[1]，即是x[0]
    }
    return 0;
}
