#include <malloc.h>
#include <stdio.h>

#define MAX(a,b) a>b?a:b
#define RED 0
#define BLACK 1
#define TRUE 1
#define FALSE 0

#ifndef __GNUC__
#define MSVC
#endif

/*red-black tree*/
typedef struct RBTree
{
    struct RBTree *left, *right;
    int color;
    void *value;
} *rb_tree;


static rb_tree newNode(void* value){
    rb_tree node = (rb_tree)malloc(sizeof(struct RBTree));
    node->left = 0;
    node->right = 0;
    node->color = RED;
    node->value = value;
    return node;
}

//右旋转
inline void right_rotate(rb_tree *n){
    rb_tree node = *n;
    rb_tree B = node->left;
    rb_tree E = B->right;
    node->left = E;
    B->right = node;
    B->color = node->color;
    node->color = RED;
    *n = B;
}

//左旋转
inline void left_rotate(rb_tree *r){
    rb_tree root = *r;
    rb_tree B = root->right;
    rb_tree D = B->left;
    root->right = D;
    B->left = root;
    B->color = root->color;	//继承父节点的颜色
    root->color = RED;	//此时变为红色
    *r = B;       //错的
}


inline int isRed(rb_tree node){
    if(node == 0)
        return FALSE;
    return node->color == RED?TRUE:FALSE;
}

static void flipColor(rb_tree *n){
    rb_tree node = *n;
    node->left->color = BLACK;
    node->right->color = BLACK;
    node->color = RED;
}
/*插入节点，保持红黑树性质
  1.左节点为红色
  2.不能存在红色父子节点
  3.黑色平衡
*/
static void _insert(rb_tree* tree,void *value, int (*cmp)(void*, void*)){
    if(*tree==0){
        *tree = newNode(value);
        return;
    }
    rb_tree node = *tree;
    int flag = cmp(node->value, value);
    if(flag<0){//插入节点值大于当前节点的值
        _insert(&(node->right),value,cmp);
    }else if(flag >0){
        _insert(&(node->left),value,cmp);
    }else{
        node->value = value;
    }
    if(isRed((*tree)->left)==FALSE&& isRed((*tree)->right)==TRUE)
        left_rotate(tree);
    if(isRed((*tree)->left) ==TRUE&& isRed((*tree)->left->left)==TRUE)
        right_rotate(tree);
    if(isRed((*tree)->left)==TRUE&&isRed((*tree)->right)==TRUE)
        flipColor(tree);
}

void insert(rb_tree *node, void *value,int (*cmp)(void*, void*)){
    _insert(node,value,cmp);
    (*node)->color = BLACK;
}

void search(rb_tree root, void *value){
    if(root == 0){
        printf("no value found");
        return;
    }
    int res = cmp(value,root->value);
    if(res==0){
        printf("find value:%d\n", value);
        return;
    }
    else if(res>0){
        search(root->right,value);
    }else{
        search(root->left,value);
    }
}

#ifdef MSVC
int main(int argc, char const *argv[])
{
    printf("%s\n", "nihao");
    return 0;
}
#else
inline int cmp(int i, int j){
    if(i>j) return 1;
    else if(i<j) return -1;
    else return 0;
}
int main(){
    rb_tree tree = newNode(0);
    int i;
    for(i =1;i<1000;i++)
        insert(&tree,i,cmp);
    search(tree, 2000);
    printf("end\n");
    return 0;
}
#endif
