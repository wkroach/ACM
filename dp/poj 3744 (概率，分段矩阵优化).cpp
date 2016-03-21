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
#define N 5
#define M 30
#define ULL unsigned long long int
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
int n,m,k,t;
LL MOD;
struct Matrix
{
//	LL mat[N][N];
    double mat[N][N];//浮点型
	int row;//行
	int col;//列
	Matrix():row(N),col(N){}
	Matrix(int r,int c):row(r),col(c){}//构造函数
};

Matrix Mul(Matrix left,Matrix right)
{
	Matrix res;
	if(left.col != right.row)	return res;

	res.row = left.row;
	res.col = right.col;

	for(int i = 0 ; i < left.row ; i++)
	{
		for(int j = 0 ; j < right.col; j++)
		{
			res.mat[i][j] = 0;
			for(int k = 0 ; k < left.col ; k++)
			{
				res.mat[i][j] += left.mat[i][k] * right.mat[k][j];
			}
		}
	}
	return res;
}

Matrix Pow(Matrix x,int n)
{
	Matrix res ;

	res.row = x.row;
	res.col = x.col;

	for(int i = 0 ; i < res.row ;i++)
	{
		for(int j = 0 ; j < res.col ; j++)
			res.mat[i][j] = 0;
		res.mat[i][i] = 1;
	}

	while(n)
	{
		if(n&1)	res = Mul(res,x);
		x = Mul(x,x);
		n >>= 1;
	}

	return res;
}

int main()
{
//    freopen("input.txt","r",stdin);
    double p;
    int arr[15];
    while(scanf("%d%lf",&n,&p)==2)
    {
        memset(arr,0,sizeof(arr));
        for(int i=0;i<n;++i)
            scanf("%d",&arr[i]);
        sort(arr,arr+n);///以末尾为地雷位分段，利用矩阵快速幂算出这一段通过的概率，总概率等于所有段的概率之积
        Matrix tmp(2,2);///递推式（状态转移方程）写成矩阵连乘式
        tmp.mat[0][0]=p;
        tmp.mat[1][0]=1-p;
        tmp.mat[0][1]=1;
        tmp.mat[1][1]=0;
        int len=arr[0]-1;///默认初始位置概率为1，所以幂要减一，
        Matrix res=Pow(tmp,len);
        double ans=(1-res.mat[0][0]);///当前这一段通过的概率即为1减到达此段最后有地雷的点的概率
        for(int i=1;i<n;++i)
        {
            if(arr[i]==arr[i-1])  continue;
            res=Pow(tmp,arr[i]-arr[i-1]-1);
            ans*=(1-res.mat[0][0]);
        }
        printf("%.7lf\n",ans);
    }
    return 0;
}

