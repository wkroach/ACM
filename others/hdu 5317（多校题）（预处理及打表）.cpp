//Îâ¿Â
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
#define LL long long
#define MOD 1000000007
int arr[1000001],arr2[1000001][8],arr3[8];
int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
void init()
{
    for(int i=2;i<=1000000;++i)
        if(arr[i]==0)
            for(int j=i;j<=1000000;j+=i)
            {
                arr[j]++;
            }
}
bool bs(int arr[],int l,int r,int p)
{
    int s=l,e=r,m;
    while(s<=e)
    {
        m=(s+e)/2;
        if(arr[m]<p) s=m+1;
        else if(arr[m]>p) e=m-1;
        else if(arr[m]==p) return true;
    }
    return false;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif
    init();
    arr2[2][1]=1;
    for(int i=3;i<=1000000;++i)
    {
        for(int j=1;j<=7;++j)
            arr2[i][j]=arr2[i-1][j];
        arr2[i][arr[i]]++;
    }
//    for(int i=2;i<=10000;++i)
//        printf("%d ",arr[i]);
//    puts("");
//    for(int i=2;i<=1000;++i)
//    {
//        printf("%d: ",i);
//        for(int j=1;j<=7;++j)
//            printf("%d ",arr2[i][j]);
//        puts("");
//    }
//    for(int i=2;i<=1000001;++i)
//        if(arr[i]==7) printf("%d ",i);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int l,r;
        int a=0,b=0,c=0,d=0,e=0,f=0;
        memset(arr3,0,sizeof(arr3));
        scanf("%d%d",&l,&r);
        for(int i=1;i<=7;++i)
        {
            int m=arr2[r][i]-arr2[l][i];
            if(arr[l]==i)
                arr3[i]=m+1;
            else arr3[i]=m;
            //printf("%d ",arr3[i]);
        }
        if(arr3[7]>1) printf("7\n");
        else if(arr3[6]>1) printf("6\n");
        else if(arr3[5]>1) printf("5\n");
        else if(arr3[4]>1) printf("4\n");
        else if(arr3[3]&&arr3[6]) printf("3\n");
        else if(arr3[3]>1) printf("3\n");
        else if(arr3[2]&&arr3[4]) printf("2\n");
        else if(arr3[2]&&arr3[6]) printf("2\n");
        else if(arr3[4]&&arr3[6]) printf("2\n");
        else if(arr3[2]>1) printf("2\n");
        else printf("1\n");

    }
    return 0;
}
