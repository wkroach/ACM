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
#define N 10005
int arr[N],arr1[N],arr2[N];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int n,flag;
    while(scanf("%d",&n)==1&&n)
    {
        flag=0;
        memset(arr,0,sizeof(arr));///存放原数组
        memset(arr1,0,sizeof(arr1));///存放前i个数的最大连续和
        memset(arr2,0,sizeof(arr2));///存放前i个数连续和，若小于0则重新统计
        for(int i=1;i<=n;++i){
            scanf("%d",&arr[i]);
            if(arr[i]>=0)
                flag=1;
        }
        if(!flag)
        {
            printf("%d %d %d\n",0,arr[1],arr[n]);
            continue;
        }
        ///核心代码如下：
        int s,e,s1;
        arr1[1]=arr[1];
        if(arr[1]<0) ///注意起始数是否小于0
        {
            arr2[1]=0,s=s1=e=arr[2];
        }
        else
        {
            arr2[1]=arr[1],s=s1=e=arr[1];
        }
        for(int i=2; i<=n; ++i)
        {
            arr2[i]=arr2[i-1]+arr[i];
            if(arr2[i]<=arr1[i-1]) ///保存最大值即末位置
            {
                arr1[i]=arr1[i-1];
            }
            else
            {
                arr1[i]=arr2[i],e=arr[i],s=s1;
            }
            if(arr2[i]<0) ///由于前i个数和小于0，加上i+1个数一定小于i+1，不如重新从i+1计数
            {
                arr2[i]=0,s1=(i==n?n:arr[i+1]);///更新其实位置
            }
            //printf("%d %d %d ",m,s,e);
        }
        printf("%d %d %d\n",arr1[n],s,e);
    }
    return 0;
}

