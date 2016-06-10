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

//#include<bits/c++std.h>

#define Size 100005
#define inf 2e9
#define INF 2e18
#define LL long long int
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r

using namespace std;
LL n,m,k;
LL ql,qr,pos;

LL arr[10005];
LL rsum1[20005];///��¼�ӵ�ǰ�������ߵ����Ϊ�����ĵ�ʱ�������С��������10000Ϊ��ֵ��ÿ�ζ���10000�������������ֲ���10000����
LL rsum2[20005];///��¼���������Ϊż������
LL ans[10005];

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
//    cin>>t;
//    while(t--)
    while(scanf("%I64d",&n) == 1)
    {
        for(LL i = 0; i < n; ++i)
        {
            scanf("%I64d",&arr[i]);
        }
        for(LL i = 0; i < n;++i)///O(n^2)��ÿ�������б���
        {
            memset(rsum1,0,sizeof(rsum1));
            memset(rsum2,0,sizeof(rsum2));
            ans[i] = 0;
            LL rtmp = 0;//�����ұߴ���arr[i]��������Ŀ��С��arr[i]��������Ŀ�Ĳ�ֵ
            for(LL j = i;j<n;j++)///�ӵ�ǰλ������ɨ��ֻ�洢��¼��������
            {
                if(arr[j] > arr[i])
                {
                    rtmp++;
                }
                else if(arr[j]<arr[i])
                {
                    rtmp--;
                }
                if((j-i)&1)///ע�⣡��������żҪ�ֿ��㣬��Ϊż�����ȵ���λ��һ��������Ҫ��
                    rsum1[rtmp+10000]++;///ÿ�ζ���10000�����ɽ��������ֿ�
                else
                    rsum2[rtmp+10000]++;///ÿ�μ���������С�����ж��ٸ�
            }
            LL ltmp = 0;///�ӵ�ǰλ������ɨʱ�ļ�¼
            for(LL j = i;j>=0;--j)///ɨ���ֱ�Ӽ��㲻��Ҫ�洢������arr[i]�Ѱ�����rsum2[10000]�У������ظ�����
            {
                if(arr[j] > arr[i])
                {
                    ltmp++;
                }
                else if(arr[j]<arr[i])
                {
                    ltmp--;
                }
                LL flag = (i-j)&1;
                if(flag)///ֻ������������ż����ͬ������������֤������ĿΪ����
                {
                    ans[i] += rsum1[10000 - ltmp];///���������ߵļ�¼֮��Ϊ0ʱ������������У���arr[i]�������С������Ŀһ��
                }
                else///��ôֻ��Ҫ�ҵ��ұ߶�Ӧ������߼�¼�෴�������ɣ�
                {
                    ans[i] += rsum2[10000 - ltmp];
                }
            }
        }
        for(LL i = 0;i<n;++i)
        {
            if(i<n-1)
                printf("%I64d ",ans[i]);
            else
            {
                printf("%I64d\n",ans[i]);
            }
        }
    }
    return 0;
}
