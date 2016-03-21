
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
        ///������ö�ٸ��Ӷ�ΪO((len-m*l)*m*l)
        ///ÿ��ÿ�ε�ö�٣����Ӷ�ΪO(l*(s-l)/l)==O(s-l)
        for(int i=0;i<l&&i<len-m*l;++i)///��ͷֻö�ٵ�һ��LΪֹ���ڲ�ѭ����LΪ��λö��
        {
            head=i;
            p.clear();///ÿö��һ����ͷ�����˽�map����
            for(int j=i;j<m*l+i;j+=l)///����LΪ��λö����һ��m*l
            {
                ULL tmp=Hash[j]-Hash[j+l]*k[l];
                p[tmp]++;
            }
            if(p.size()==m)
                sum++;
            for(int j=m*l+i;j<=len-l;j+=l)///����������ƶ�1����ΪL���ַ���������mapɾ��һ����ͷL���ַ���
            ///�ҽ�������m*L�ַ����ĳ�ΪL�����ַ�������map
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

