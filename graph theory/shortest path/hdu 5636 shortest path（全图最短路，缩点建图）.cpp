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
#define LL long long
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
int n, m, k, q;
int arr[10];
int graph[10][10];

void init()///���㽨ͼ���������������ӵ�6�����㽨��һ��6*6��ͼ
{
    for(int i = 1; i <= 6; ++i)
    {
        for(int j = 1; j <= 6; ++j)
        {
            graph[i][j] = graph[j][i] = abs(arr[i] - arr[j]);
        }
    }

    for(int i = 1; i <= 3; ++i)
    {
        graph[i][i + 3] = graph[i + 3][i] = 1;
    }
}

void floyd()///�����ͼ����ȫͼ���·
{
    for(int k = 1; k <= 6; ++k)
    {
        for(int i = 1; i <= 6; ++i)
        {
            for(int j = 1; j <= 6; ++j)
            {
                if(graph[i][j] > graph[i][k] + graph[k][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
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
    int x, y, z;
    int a, b;
//    int Case=0;
    cin >> t;

    while(t--)
//    cin>>n;
//    while(scanf("%d%d",&n,&m)==2)
    {
        scanf("%d%d", &n, &m);

        for(int i = 1; i <= 3; ++i)
        {
            cin >> arr[i] >> arr[i + 3];
        }

        init();
        floyd();

        LL ans = 0;

        for(int k = 0; k < m; ++k)///������������㣬Ҫô������6����֮���·��Ҫô����6������ѡһ�����һ�����ڣ������ǵ����·
        {
            scanf("%d%d", &a, &b);
            int tmp = abs(a - b);

            for(int i = 1; i <= 6; ++i)
            {
                for(int j = 1; j <= 6; ++j)
                {
                    tmp = min(tmp, abs(a - arr[i]) + graph[i][j] + abs(b - arr[j]));
                }
            }

            ans += (((k + 1) % Mod) * ((LL)tmp % Mod)) % Mod;
            ans %= Mod;
        }

        cout << ans << endl;
    }

    return 0;
}







