
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
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    LL r,y,b,sum;
    while(scanf("%lld%lld%lld",&r,&y,&b)==3)
    {
        int flag=0,flag2=0,flag3=0;
        if(r==0) flag++;
        if(y==0) flag++;
        if(b==0) flag++;
        if(r>2) flag2++;
        if(y>2) flag2++;
        if(b>2) flag2++;
        if(r==2) flag3++;
        if(y==2) flag3++;
        if(b==2) flag3++;
        sum=r+y+b;
        if(r>=2&&y>=2&&b>=2)
            printf("%lld\n",15+(sum-6)*6);
        else if(flag==1)
        {
            if(r==0&&y&&b)
                r=y,y=b;
            else if(y==0&&r&&b)
                y=b;
            if(r>=2&&y>=2)
                printf("%lld\n",6+(r+y-4)*4);
            else if(r==1&&y==1)
                printf("1\n");
            else
                printf("%lld\n",3+(r+y-3)*3);
        }
        else if(flag==2)
        {
            if(sum==1)
                printf("0\n");
            else if(sum>=2)
                printf("%lld\n",1+(sum-2)*2);
        }
        else if(flag==0)
        {
            if(sum==3&&flag2==0)
                printf("3\n");
            else if(sum==4&&flag2==0)
                printf("6\n");
            else if(sum==5&&flag2==0)
                printf("10\n");
            else if(flag2==1&&flag3!=1)
                printf("%lld\n",6+(sum-4)*4);
            else if(flag2==2)
                printf("%lld\n",10+(sum-5)*5);
            else if(flag2==1&&flag3==1)
                printf("%lld\n",10+(sum-5)*5);
        }
        else if(flag==3)
            printf("0\n");
    }
    return 0;
}

