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
#define N 3
#define M 30
#define ULL unsigned long long int
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
///hdu 4565   ��ѧ���⣬������
///֤���Ƚϲ���д�������ɲ���ϸ֤�����㷨����

LL n,m,k,t;
LL MOD;
struct Matrix
{
	LL mat[N][N];
    ///double mat[N][N];������
	int row;//��
	int col;//��
	Matrix():row(N),col(N){}
	Matrix(int r,int c):row(r),col(c){}//���캯��
};

Matrix MulMod(Matrix left,Matrix right)
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
			for( k = 0 ; k < left.col ; k++)
				res.mat[i][j] += (left.mat[i][k] * right.mat[k][j]) % MOD,
				res.mat[i][j]%=MOD;
            res.mat[i][j] %= MOD;
		}
	}
	return res;
}


Matrix PowMod(Matrix x,LL n)
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
		if(n&1)	res = MulMod(res,x);
		x = MulMod(x,x);
		n >>= 1;
	}

	return res;
}

int main()
{
//    freopen("input.txt","r",stdin);
    LL a,b;
    while(scanf("%I64d%I64d%I64d%I64d",&a,&b,&n,&m)==4)
    {
        MOD=m;
        double c=a+sqrt((double)b);
//        printf("%lf\n",c);
        Matrix ret(2,1);
//        ret.row=2;
//        ret.col=1;
        Matrix tmp(2,2);///ϵ���������þ�������ݣ�
//        tmp.row=2;
//        tmp.col=2;
        tmp.mat[0][0]=2*a;
        tmp.mat[0][1]=-1*(a*a-b);
        tmp.mat[1][0]=1;
        tmp.mat[1][1]=0;
        ret.mat[1][0]=((LL)ceil(c))%m;
        ret.mat[0][0]=((LL)ceil(c*c))%m;
        if(n<=2)
        {
            if(n==1)
            {
                printf("%I64d\n",ret.mat[1][0]%m);
                continue;
            }
            else if(n==2)
            {
                printf("%I64d\n",ret.mat[0][0]%m);
                continue;
            }
        }
        tmp=PowMod(tmp,n-2);
        Matrix ans=MulMod(tmp,ret);
        printf("%I64d\n",(ans.mat[0][0]%MOD+MOD)%MOD);///ע���������Ǹ�������Ҫת��������ȡģ������ֱ��abs������������
    }
    return 0;
}
