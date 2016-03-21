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

struct node//�ڵ�
{
    int value;//�ڵ��ֵ
    node* rson;//�Ҷ���ָ��
    node* lson;//�����ָ��
    node* fa;//���ڵ�ָ��
    node():value(0),rson(NULL),lson(NULL),fa(NULL){}
};

struct tree//��
{
    node* root;//�ٸ�
    tree():root(0){}
};

node*& tree_minimum(node* T)//������TΪ����������С�ڵ�
{
    if(T->lson==NULL)
        return T;
    tree_minimum(T->lson);
}

node*& tree_maximum(node* T)//������TΪ�����������ڵ�
{
    if(T->rson==NULL)
        return T;
    tree_maximum(T->rson);
}

node* tree_successor(node* T)//���ҽڵ�T�ĺ�̽ڵ�
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

node* tree_predecessor(node* T)//���ҽڵ�T��ǰ���ڵ�
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

void tree_inorder(node* T)//���������TΪ������
{
    if(T==NULL)
        return ;
    tree_inorder(T->lson);
    cout<<T->value<<" ";
    tree_inorder(T->rson);
}

void tree_insert(tree &T,node* z)//����T�в���ڵ�
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

void tree_transplant(tree& T,node* z,node* tmp)//����T�н��ڵ�tmp��ֲ��z��λ�ã���tmp�滻z
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

void node_delete(tree &T,node* z)//����T��ɾ��z�ڵ�
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

void tree_build(tree& T,const vector<int>& arr)//������arr�е�Ԫ�ؽ�һ����
{
    for(int i=0;i<arr.size();++i)
    {
        node* tmp=new node;
        tmp->value=arr[i];
//        cout<<1<<endl;
        tree_insert(T,tmp);
    }
}

void tree_delete(node* T)//ɾ����T
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

