#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
#define order 3
class node{
    public:
        node *parent;
        int key_size;
        int child_size;
        int key[order+1]; //actually order
        node *child[order+2]; //for oversize easy to handle actually order-1
        node(){
            parent = NULL;
            key_size = 0;
            child_size = 0;
        }
        node(node *Parent,int Key[],int key_start,int key_end,node *Child[],int child_start,int child_end){
            parent = Parent;
            child_size = child_end - child_start;
            memcpy(child,Child+child_start,child_size*sizeof(Child[0]));
            key_size = key_end - key_start;
            memcpy(key,Key+key_start,key_size * sizeof(Key[0]));
            for(int i = 0; i < child_size; i++){
                child[i]->parent = this;
            }
        }

        void printnode();
};
void node::printnode(){
            cout << "[";
            for (int i = 0; i < key_size; i++){
                if (i){cout<<",";}
                cout << key[i];}
            cout << "]";
        }
bool comp_func1 (node *p1, node *p2){return p1->key[0] < p2->key[0];}
bool comp_func2 (int p1, int p2){return p1 < p2;}
node *Root = new node();

void insert(node *leaf,int value);
void split(node *treenode);
node *find_leaf(node *root, int n);

void split(node *treenode){
    node *root = Root;//Debug
    int keysize = treenode->key_size;
    int childsize = treenode->child_size;
    bool isleaf = childsize == 0;
    node **child = treenode->child;
    int *key = treenode->key;
    if(keysize <= order-1){return;}
    if(isleaf && keysize <= order ){return;}
    if(!treenode->parent){
        Root = new node();
        treenode ->parent = Root;
    }
    node *parent = treenode->parent;
    node *left;
    node *right;
    int middle = 2;
    if(isleaf){
        left = new node(parent,key,0, 2, child, 0, 0);
        right = new node(parent,key,2,keysize, child,0,0);
    }
    else{
        middle = 1;
        left = new node(parent, key, 0, 1, child, 0, 2);
        right = new node(parent,key, 2, keysize, child, 2, childsize);
    }
    parent->key[parent->key_size++] = key[middle];
    
    if(parent->child_size > 0){
        for(int i = 0; i < parent->child_size; i++){
            if(parent->child[i] == treenode){
                parent->child[i] = left;
                break;
            }
        }
    }
    else{
        parent->child[parent->child_size++] = left;
    }
    delete treenode;
    parent->child[parent->child_size++] = right;
    sort(parent->key,parent->key+parent->key_size);
    sort(parent->child,parent->child+parent->child_size,comp_func1);
    split(parent);
}

void print_tree ()
{
    node *BlankLine = NULL; // 换行标记，标记一层节点
    queue<node *> que;
    que.push(Root);
    que.push(BlankLine);
    while (!que.empty())
    {
        node *t = que.front();
        que.pop();
        if (t == BlankLine)
        {
            printf("\n");
            if (!que.empty())
                que.push(BlankLine);
            continue;
        }
        t->printnode();
        for (int i = 0; i < t->child_size; ++i)
        {
            que.push(t->child[i]);
        }

    }
}

void insert(node *leaf,int value){
    if(!leaf){leaf = new node();}
    leaf->key[leaf->key_size++] = value;
    sort(leaf->key,leaf->key+leaf->key_size,comp_func2);
    split(leaf);
}

node *find_leaf(node *root, int n)
{
    if (root == NULL){return root;}
    if (root->child_size == 0){return root;}
    for(int i = 0; i < root->key_size; i++){
        if(n < root->key[i]){
            return find_leaf(root->child[i],n);
        }
    }
    return find_leaf(root->child[root->child_size-1],n);
}


int main ()
{
    int N;
    cin >> N;
    while(N--){
        int num;
        cin >> num;
        node *leaf = find_leaf(Root, num);
        int found = 0;
        if(leaf){
            for (int i = 0; i < leaf->key_size; i++){
                if (leaf->key[i] == num){
                    found = 1;
                    break;}
            }
        }

        if (!found){insert(leaf, num);}
        else{printf("Key %d is duplicated\n", num);}
    }
    print_tree();
    return 0;
}
