
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
#define seed 31
#define ULL unsigned long long int
map <ULL,int> p;
ULL k[100010];
ULL Hash[100005];
char s[100005];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int m,l;
    int t,n;
    k[0]=1;
    for(int i=1;i<=100005;++i)
        k[i]=k[i-1]*seed;
    while(scanf("%d%d",&m,&l)==2)
    {
        p.clear();
        memset(Hash,0,sizeof(Hash));
        getchar();
        gets(s);
        int len=strlen(s);
        Hash[len]=0;
        ///hash
        for(int i=len-1;i>=0;--i)
            Hash[i]=(Hash[i+1]*seed+s[i]-'a'+1);
//        for(int i=len-1;i>=0;--i)
//            printf("%lld ",Hash[i]);
        int sum=0;
        ULL head;
        ///纯暴力枚举复杂度为O((len-m*l)*m*l)
        ///每段每段的枚举，复杂度为O(l*(s-l)/l)==O(s-l)
        for(int i=0;i<l&&i<len-m*l;++i)///开头只枚举到一个L为止，内层循环以L为单位枚举
        {
            head=i;
            p.clear();///每枚举一个开头别忘了将map清零
            for(int j=i;j<m*l+i;j+=l)///先以L为单位枚举完一个m*l
            {
                ULL tmp=Hash[j]-Hash[j+l]*k[l];
                p[tmp]++;
            }
            if(p.size()==m)
                sum++;
            for(int j=m*l+i;j<=len-l;j+=l)///再依次向后移动1长度为L的字符串，并从map删除一个开头L的字符串
            ///且将新移入m*L字符串的长为L的子字符串加入map
            {
                ULL tmp=Hash[head]-Hash[head+l]*k[l];
                p[tmp]--;
                if(p[tmp]==0) p.erase(tmp);
                head+=l;
                tmp=Hash[j]-Hash[j+l]*k[l];
                p[tmp]++;
                if(p.size()==m) sum++;
                //printf("%d\n",sum);
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}

