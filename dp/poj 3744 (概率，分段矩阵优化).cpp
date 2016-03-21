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
    double mat[N][N];//������
	int row;//��
	int col;//��
	Matrix():row(N),col(N){}
	Matrix(int r,int c):row(r),col(c){}//���캯��
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
        sort(arr,arr+n);///��ĩβΪ����λ�ֶΣ����þ�������������һ��ͨ���ĸ��ʣ��ܸ��ʵ������жεĸ���֮��
        Matrix tmp(2,2);///����ʽ��״̬ת�Ʒ��̣�д�ɾ�������ʽ
        tmp.mat[0][0]=p;
        tmp.mat[1][0]=1-p;
        tmp.mat[0][1]=1;
        tmp.mat[1][1]=0;
        int len=arr[0]-1;///Ĭ�ϳ�ʼλ�ø���Ϊ1��������Ҫ��һ��
        Matrix res=Pow(tmp,len);
        double ans=(1-res.mat[0][0]);///��ǰ��һ��ͨ���ĸ��ʼ�Ϊ1������˶�����е��׵ĵ�ĸ���
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

