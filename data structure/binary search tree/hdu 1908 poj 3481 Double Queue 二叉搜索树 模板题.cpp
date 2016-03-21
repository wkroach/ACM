#include<cstdio>
#include<cstdlib>
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
using namespace std;
#define LL long long int
#define ULL unsigned long long int
#define MOD 1000000007
#define N 100005
#define M 100005
#define MAX 1000000000
//#define lson now*2,l,l+(r-l)/2
//#define rson now*2+1,l+(r-l)/2+1,r

int n,m;

struct node
{
    int num;
    int value;
    node* rson;
    node* lson;
    node* fa;
    node():num(0),value(0),rson(NULL),lson(NULL),fa(NULL){}
};

struct tree
{
    node* root;
    tree():root(NULL){}
};

node* tree_minimum(node* T)
{
    if(T->lson==NULL)
        return T;
    tree_minimum(T->lson);
}

node* tree_maximum(node* T)
{
    if(T->rson==NULL)
        return T;
    tree_maximum(T->rson);
}


void tree_insert(tree &T,node* z)
{
    node* y=NULL;
    node* x=T.root;
    while(x!=NULL)
    {
        y=x;
        if(x->value>z->value)
            x=x->lson;
        else if(x->value<z->value)
            x=x->rson;
        else if(x->value==z->value)
            return ;
    }
    z->fa=y;
    if(y==NULL)
        T.root=z;
    else if(y->value>z->value)
        y->lson=z;
    else if(y->value<z->value)
        y->rson=z;
}

void tree_transplant(tree& T,node* z,node* tmp)
{
    if(z->fa==NULL)
        T.root=tmp;
    else if(z==z->fa->lson)
        z->fa->lson=tmp;
    else if(z==z->fa->rson)
        z->fa->rson=tmp;
    if(tmp!=NULL)
        tmp->fa=z->fa;
}

void node_delete(tree &T,node* z)
{
    if(z->lson==NULL)
    {
        tree_transplant(T,z,z->rson);
        delete z;
        z=NULL;
    }
    else if(z->rson==NULL)
    {
        tree_transplant(T,z,z->lson);
        delete z;
        z=NULL;
    }
    else
    {
        node* tmp=tree_minimum(z->rson);
        if(tmp->fa!=z)
        {
            tree_transplant(T,tmp,tmp->rson);
            tmp->rson=z->rson;
        }
        tree_transplant(T,z,tmp);
        tmp->lson=z->lson;
        tmp->lson->fa=tmp;
        delete z;
        z=NULL;
    }
}

void tree_build(tree& T,const vector<int>& arr)
{
    for(int i=0;i<arr.size();++i)
    {
        node* tmp=new node;
        tmp->value=arr[i];
//        cout<<1<<endl;
        tree_insert(T,tmp);
    }
}

void tree_delete(node* T)
{
    if(T==NULL)
        return ;
    tree_delete(T->lson);
    tree_delete(T->rson);
    delete T;
    T=NULL;
}

int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    tree T;
    node* tmp=NULL;
    node* tmp2=NULL;
    while(scanf("%d",&n)==1&&n)
    {
        tmp=new node;
        tmp2=NULL;
        if(n==1)
        {
            scanf("%d%d",&(tmp->num),&(tmp->value));
            tree_insert(T,tmp);
        }
        else if(n==2||n==3)
        {
            if(T.root==NULL)
            {
                delete tmp;
                tmp=NULL;
                printf("0\n");
                continue;
            }
            if(n==2)
            {
                tmp2=tree_maximum(T.root);
            }
            else if(n==3)
            {
                tmp2=tree_minimum(T.root);
            }
            printf("%d\n",tmp2->num);
            node_delete(T,tmp2);
        }
    }
    return 0;
}

