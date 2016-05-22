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


LL vis[10010];
vector<LL> arr;
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    LL x,y,z;
    LL Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&n)==1)
    {
        memset(vis,0,sizeof(vis));
        arr.clear();
        scanf("%I64d%I64d%I64d%I64d",&x,&m,&k,&y);
        printf("Case #%I64d:\n", ++Case);
        LL ans = 0;
        LL len1, len2;
        len1 = len2 = 0;
        LL tmp = x%k;
        for(LL i = 0;i<100010;++i)///�ص㣬��������m����С��n�ķ�Χ�ڣ��ض����ҵ�m���ݵ�ģnѭ���ڣ������ѭ�������޹��ɵ�,������󲻳���n������ԭ��n�����ϵ�����nȡģһ�����ظ���ģ����
                                    ///�ص㣬Ҫ��ģnѭ��Ⱥ��������m��n���ʣ���ôm���ݶ���ģn����ѭ���ڣ�����Щģ�����ض�������ģn ��ѭ��Ⱥ�У�������ŷ������
        {
            if(vis[tmp])//�ҳ���ʼ����ѭ���ڵĲ����Լ�ѭ���ڵ���ʼ����ֹλ�ã���������������
            {
                len2 = i + 1 - vis[tmp];
                len1 = vis[tmp]-1;
                break;
            }
            else
            {
                vis[tmp] = i+1;
            }
            arr.push_back(tmp);///��¼ÿ��ģֵ
            tmp *= 10;
            tmp %= k;
        }
//        cout<<len1<<" "<<len2<<endl;
        if(m < len1 + len2)///ע�⣡����������m�ķ�Χ�ڿ���û��ѭ���ڣ���mС����Сѭ���ڳ��Ⱥ�δѭ�����ֺ�ֻ�ܱ������
        {
            for(LL i=0;i<m;++i)
            {
                ans += arr[i];
                ans %= k;
            }
//            cout<<ans<<endl;
        }
        else
        {
            for(LL i=0;i<len1;++i)///��֮���ȶ�δѭ�����
            {
                ans += arr[i];
                ans %= k;
            }
            LL tmp = 0;
            for(LL i = len1;i < len1 + len2;++i)///�ٵ�����ѭ�������
            {
                tmp += arr[i];
                tmp %= k;
            }
            LL num = (m-len1)/len2;//�ж��м���ѭ���ڣ������
            LL len3 = (m-len1)%len2;
            tmp = tmp * num % k;
            ans += tmp;
            ans %= k;
            for(LL i = len1;i<len1 + len3;++i)//����֮��ʣ��Ĳ�������ͼ��ǽ��
            {
                ans += arr[i];
                ans %= k;
            }
        }
        if(ans != y)
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
        }
    }
    return 0;
}
