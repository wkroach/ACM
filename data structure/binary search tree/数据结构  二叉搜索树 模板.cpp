#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#define eps 1e-9
#define N 100000
#define M 30
#define ULL unsigned long long int
#define LL long long
#define INF 0x3f3f3f3f
using namespace std;
int n,m;

struct node//节点
{
    int value;//节点的值
    node* rson;//右儿子指针
    node* lson;//左儿子指针
    node* fa;//父节点指针
    node():value(0),rson(NULL),lson(NULL),fa(NULL){}
};

struct tree//树
{
    node* root;//假根
    tree():root(0){}
};

node*& tree_minimum(node* T)//查找以T为根的树的最小节点
{
    if(T->lson==NULL)
        return T;
    tree_minimum(T->lson);
}

node*& tree_maximum(node* T)//查找以T为根的树的最大节点
{
    if(T->rson==NULL)
        return T;
    tree_maximum(T->rson);
}

node* tree_successor(node* T)//查找节点T的后继节点
{
    if(T->rson!=NULL)
    {
        return tree_minimum(T->rson);
    }
    node* y=T->fa;
    while(y!=NULL&&T==y->rson)
    {
        T=y;
        y=y->fa;
    }
    return y;
}

node* tree_predecessor(node* T)//查找节点T的前驱节点
{
    if(T->lson!=NULL)
    {
        return tree_maximum(T->lson);
    }
    node* y=T->fa;
    while(y!=NULL&&T==y->lson)
    {
        T=y;
        y=y->fa;
    }
    return y;
}

void tree_inorder(node* T)//中序遍历以T为根的树
{
    if(T==NULL)
        return ;
    tree_inorder(T->lson);
    cout<<T->value<<" ";
    tree_inorder(T->rson);
}

void tree_insert(tree &T,node* z)//在树T中插入节点
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

void tree_transplant(tree& T,node* z,node* tmp)//在树T中将节点tmp移植到z的位置，用tmp替换z
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

void node_delete(tree &T,node* z)//在树T中删除z节点
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
    }
}

void tree_build(tree& T,const vector<int>& arr)//用数组arr中的元素建一棵树
{
    for(int i=0;i<arr.size();++i)
    {
        node* tmp=new node;
        tmp->value=arr[i];
//        cout<<1<<endl;
        tree_insert(T,tmp);
    }
}

void tree_delete(node* T)//删除树T
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
    #endif // ONLINE_JUDGE
    scanf("%d",&n);
    vector<int> arr;
    for(int i=0;i<n;++i)
    {
        int tmp;
        cin>>tmp;
        arr.push_back(tmp);
    }
    tree T;
    tree_build(T,arr);
    tree_inorder(T.root);
    node_delete(T,tree_minimum(T.root));
    cout<<endl;
    tree_inorder(T.root);
    cout<<endl;
//    cout<<tree_maximum(T.root)->value<<endl;
    node_delete(T,tree_maximum(T.root));
    tree_inorder(T.root);
    tree_delete(T.root);
    return 0;
}

