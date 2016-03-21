    #include<iostream>
    #include<cstdio>
    #include<cstring>
    #include<cmath>
    #include<stack>
    #include<vector>
    #include<map>
    #include<set>
    #include<queue>
    #include<algorithm>
    using namespace std;
    typedef long long ll;
    //ll arr[1000000];
    struct node
    {
        ll x;
        ll y;
    };
    node arr[1000000];

    bool cmp(node a,node b)
    {
        if(a.x!=b.x) return a.x<b.x;
        return a.y<b.y;
    }

    ll quick(ll a,ll b,ll mod)
    {
        ll c=1;
        if(b==0) return 1;
        else
        {
            while(b)
            {
                if(b&1) {c*=a;c%=mod;}
                a*=a;a%=mod;
                b>>=1;
            }
        }
        return c%mod;
    }

    ll ex_gcd(ll a,ll b,ll &g,ll &x,ll &y)
    {
        if(b==0){g=a;x=1;y=0;}
        else{ex_gcd(b,a%b,g,y,x);y-=x*(a/b);}
    }

    ll serch(node arr[],ll s,ll e,ll aim)
    {
        while(e>=s)
        {
            ll m=(e+s)/2;
            if(arr[m].x==aim) return arr[m].y;
            else if(arr[m].x>aim) e=m-1;
            else s=m+1;
        }
        return -1;
    }

    ll gcd(ll x,ll y)
    {
        return y==0?x:gcd(y,x%y);
    }
    ll e_phi(ll n)
    {
        ll m=sqrt(n+0.5);
        ll ans=n;
        for(int i=2;i<=m;++i)
            if(n%i==0)
            {
                ans=ans/i*(i-1);
                while(n%i==0) n/=i;
            }
            if(n>1) ans=ans/n*(n-1);
            return ans;
    }
    ll ex_bsbg(ll a,ll &b,ll &k,ll &d)
    {
        ll g;
        ll cnt=0;
        while(g=gcd(a,b),g!=1)
        {
            cnt++;
            if(k%g!=0) return -1;
            k/=g,b/=g,d*=(a/g),d%=b;
        }
        return cnt;
    }

    int main()
    {
       // Orz,I can't find D!
       //No Solution
        //freopen("input.txt","r",stdin);
        ll p,b,n,phi;
        while(scanf("%I64d%I64d%I64d",&b,&p,&n)==3)
        {
    //        memset(arr,0,sizeof(arr));
            if(b==0&&p==0&&n==0) break;
            //if(p==0){printf("No Solution\n");continue;}
            if(n>=p) n%=p;
            if(b==p&&n==0){printf("1\n");continue;}
             //else if(b==p&&n!=0) {printf("No Solution\n");continue;}
            if(p==1&&b==0){printf("1\n");continue;}
                else if(p==1&&b!=0) {printf("No Solution\n");continue;}
            ll cnt1,d=1;
            cnt1=ex_bsbg(b,p,n,d);
            ll ans=0,p1;
            int flag=0;
            if(cnt1==-1){printf("No Solution\n");continue;}
            else if(cnt1==0) p1=p-1;
            else p1=e_phi(p);
            //ll gcda=gcd(b,p);
            ll m=(int)ceil(sqrt((double)p1));
            arr[0].x=d;arr[0].y=0;
            for(int i=1;i<m;++i)
                arr[i].x=arr[i-1].x*b,arr[i].x%=p,arr[i].y=i;
            sort(arr,arr+m,cmp);
            int cnt=1;
            for(int i=1;i<m;++i)
                if(arr[i].x!=arr[cnt-1].x)
                    arr[cnt++].x=arr[i].x;
            ll g=0,x=0,y=0;
            ex_gcd(b,p,g,x,y);
    //        printf("x=%I64d y=%I64d ",x,y);
            x=(x%p+p)%p;
            ll b2=quick(x,m,p);
            ll cur=1;
    //        printf("b2=%I64d m=%I64d x=%I64d",b2,m,x);
            for(int i=0;i<m;++i)
            {
                cur=cur*(i==0?n:b2);
                cur%=p;
                ans=serch(arr,0,cnt-1,cur);
    //            printf("ans=%I64d ",ans);
                if(ans>=0){printf("%I64d\n",(ans+i*m+cnt1)%p1); break;}
            }
            if(ans<0) printf("No Solution\n");
        }
        return 0;
    }

