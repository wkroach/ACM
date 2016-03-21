#include<cstdio>
#include<cstdlib>
#include<time.h>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<stack>
#include<vector>
#include<algorithm>
#define Size 105
#define inf 2e9
#define INF 2e18
#define LL long long
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
int n,m,k;
int com[30][30];

void init()///杨辉三角矩阵(组合数表)1-26
{
    for(int i=1;i<=26;++i)
    {
        com[i][0]=1;
    }
    com[1][1]=1;
    for(int i=2;i<=26;++i)
    {
        for(int j=1;j<=i;++j)
        {
            com[i][j]=com[i-1][j]+com[i-1][j-1];
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
//    int Case=0;
//    cin>>t;
    init();
    char str[13];
    while(scanf("%s",str)==1)
//    cin>>n;
//    while(scanf("%d",&n)==1)
    {
        int len=strlen(str);
        int sum=0;
        for(int i=0;i<len-1;++i)///如果输入的字符串不满足要求，输出0
        {
            if(str[i+1]<=str[i])
            {
                cout<<sum<<endl;
                return 0;
            }
        }
        for(int i=1; i<len; ++i)///在总长度为n的字符串中选满足题目要求的长度为k的字符串数目为C(n,k)，证明见下面
        {
            sum += com[26][i];
        }
        for(int i=0;i<len;++i)///先统计长度小于当前字符串长度的字符串数目，再按每一位字符进行统计可能的数目
        {
            char ch = i==0 ? 'a' : str[i-1]+1;///可行的字符必定是比前一位大，比当前位小,如果是首位，从a开始
            while(ch<str[i])
            {
                int tmp=ch-'a';
                sum += com['z'-ch][len-1-i];///利用之前的结论计算出当前满足条件的字符串数目
                ch++;
            }
        }
        there:
        cout<<sum+1<<endl;///统计结果时要把这一个字符串本身考虑进来
    }
    return 0;
}

/*定理证明：
            公式：C(n,m) = sum(C(i,m-1),1<=i<=n-1)
            在已有序的长度为n字符串中选k个字符组成字符串的情况：
            k = 1时，结果为n
            k = 2时，从前往后枚举，然后相加，以n=26为例:
                    以a开头：ab,ac,......az 共有C(25,1) = 25个，即C(26-1,k-1)个
                    以b开头：bc,bd,......bz 共有C(24,1) = 24个，即C(26-2,k-1)个
                    ........
                    以x开头：xy,xz,共有C(2,1) = 2个，即C(26-24,k-1)个
                    以y开头：yz,共有C(1,1) = 1个，即C(26-25,k-1)个
            所以：
                ans = sum(C(i,k-1),1<=i<=26-1) = C(26,k)个
            当n不为26时同理可得
*/



