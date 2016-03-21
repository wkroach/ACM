
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
int arr1[50005],arr2[50005],arr3[50005],arr5[50005],arr6[50005];
bool cmp(LL a,LL b)
{
    return a>b;
}
void maxsum(int arr[],int n)
{
    int m;
    arr[0]=arr3[0]=0;
    arr[1]=arr1[1];
    arr3[1]=arr1[1]>0?arr1[1]:0;
    for(int i=2;i<=n;++i)
    {
        arr3[i]=arr3[i-1]+arr1[i];
        arr[i]=max(arr3[i],arr[i-1]);
        if(arr3[i]<0) arr3[i]=0;
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t,n,flag;
    scanf("%d",&t);
    while(t--)
    {
        flag=0;
        memset(arr1,0,sizeof(arr1));
        memset(arr2,0,sizeof(arr2));
        memset(arr5,0,sizeof(arr5));
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&arr1[i]);
            if(arr1[i]>0) flag=1;
        }
        if(!flag){
            sort(arr1+1,arr1+n+1,cmp);
            printf("%d\n",arr1[1]+arr1[2]);
            continue;
        }
        maxsum(arr2,n);
        reverse(arr1+1,arr1+1+n);
        memset(arr3,0,sizeof(arr3));
        maxsum(arr5,n);
        for(int i=1;i<n;++i)
            arr6[i]=arr2[i]+arr5[n-i];
        //arr6[n]=arr2[n];
        int m=arr6[1];
        for(int i=2;i<n;++i)
            if(m<arr6[i]) m=arr6[i];
        printf("%d\n",m);
    }
    return 0;
}
