/**
 * C语言实现的红黑树(Red Black Tree)
 *
 * @author skywang
 * @date 2013/11/18
 */


#include "tools_rbtree.h"
#define RED        0    // 红色节点
#define BLACK    1    // 黑色节点

static void default_free(void *p)
{

    free(p);
}
/*
 * 创建红黑树，返回"红黑树的根"！
 */
void RB_Node_init(RB_Node*node)
{
    node->color=RED;
    node->parent=NULL;
    node->left=NULL;
    node->right=NULL;

    node->data=NULL;
    node->prop=NULL;
}
void RB_Tree_init(RB_Tree* tree)
{
    tree->root=NULL;
    tree->cmp=NULL;
    tree->copy=NULL;
    tree->del=default_free;
    tree->size=0;
    tree->find=RB_find;
    tree->insert=RB_insert;
    tree->erase=RB_erase;
    tree->begin=RB_begin;
    tree->rbegin=RB_rbegin;
    tree->iterator_init=NULL;
    tree->prop=NULL;
}
void RB_Trav_init(RB_Trav* it)
{
    it->tree=NULL;
    it->next=RB_next;
    it->prev=RB_prev;
    it->it=NULL;
    it->prop=NULL;
}
static void RB_Tree_Node_free(RB_Tree*tree,RB_Node* node)
{
    if(node==NULL)
    {
        return; 
    }
    if(node->left!=NULL)
    {
        RB_Tree_Node_free(tree,node->left);
    }
    if(node->right!=NULL)
    {
        RB_Tree_Node_free(tree,node->right);
    }
    if(node->data!=NULL)
    {
        tree->del(node->data);
    }
    free(node);
}
void RB_Tree_free(RB_Tree *tree)
{
    if(tree==NULL)
    {
        return ;
    }
    RB_Node* node=tree->root;
    if (node != NULL)
    {
        RB_Tree_Node_free(tree,node);
    }
    tree->size=0;
    free(tree);
}

/* 
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x                  
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y  
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 * 
 */
static void rbtree_right_rotate(RB_Tree *tree, RB_Node *y)
{
    // 设置x是当前节点的左孩子。
    RB_Node *x = y->left;

    // 将 “x的右孩子” 设为 “y的左孩子”；
    // 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
    y->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = y;
    }

    // 将 “y的父亲” 设为 “x的父亲”
    x->parent = y->parent;

    if (y->parent == NULL) 
    {
        //tree = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
        tree->root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
    }
    else
    {
        if (y == y->parent->right)
        {
            y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
        }
        else
        {
            y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
        }
    }

    // 将 “y” 设为 “x的右孩子”
    x->right = y;

    // 将 “y的父节点” 设为 “x”
    y->parent = x;
}

/* 
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y                
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry     
 *     /   \                       /  \
 *    ly   ry                     lx  ly  
 *
 *
 */
static void rbtree_left_rotate(RB_Tree *tree, RB_Node *x)
{
    // 设置x的右孩子为y
    RB_Node *y = x->right;

    // 将 “y的左孩子” 设为 “x的右孩子”；
    // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }

    // 将 “x的父亲” 设为 “y的父亲”
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        //tree = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
        tree->root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
    }
    else
    {
        if (x->parent->left == x)
        {
            x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        }
        else
        {
            x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        }
    }
    
    // 将 “x” 设为 “y的左孩子”
    y->left = x;
    // 将 “x的父节点” 设为 “y”
    x->parent = y;
}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     RB_Node 插入的结点        // 对应《算法导论》中的z
 */
static void rbtree_insert_fixup(RB_Tree *tree, RB_Node *node)
{
    RB_Node *parent, *gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while ((parent = node->parent )&&parent->color==RED) 
    {
        gparent = parent->parent;

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            {
                RB_Node *uncle = gparent->right;
                if (uncle && uncle==RED)
                {
                    uncle->color=BLACK;
                    parent->color=BLACK;
                    gparent->color=RED;
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                RB_Node *tmp;
                rbtree_left_rotate(tree, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            parent->color=BLACK;
            gparent->color=RED;
            rbtree_right_rotate(tree, gparent);
        } 
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
            {
                RB_Node *uncle = gparent->left;
                if (uncle && uncle==RED)
                {
                    uncle->color=BLACK;
                    parent->color=BLACK;
                    gparent->color=RED;
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                RB_Node *tmp;
                rbtree_right_rotate(tree, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            parent->color=BLACK;
            gparent->color=RED;
            rbtree_left_rotate(tree, gparent);
        }
    }

    // 将根节点设为黑色
    tree->root->color=BLACK;
}

/*
 * 添加节点：将节点(RB_Node)插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根
 *     RB_Node 插入的结点        // 对应《算法导论》中的z
 */
void* RB_insert(RB_Tree *tree ,void* data)
{
    RB_Node *y = NULL;
    RB_Node *x = tree->root;
    RB_Node*node=(RB_Node*)malloc(sizeof(RB_Node));
    RB_Node_init(node);
    node->data=tree->copy(data); 
    int re=0;
    RB_Node* node1=node;
    tree->size++;
    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        re=tree->cmp(x->data,data);
        if (re>0)
        {

            x = x->left;
            if(x==NULL)
            {
                node->parent=y;
                y->left=node;
                break;
            }
        }
        else if(re<0)
        {
            x = x->right;
            if(x==NULL)
            {
                node->parent=y;
                y->right=node;
                break;
            }
        }
        else
        {
            tree->del(x->data); 

            x->data=node->data;
            free(node);
            tree->size--;
            return x->data;
        }
    }
    if(y==NULL)
    {
        tree->root = node;                // 情况1：若y是空节点，则将RB_Node设为根
    }
    node1->color = RED;

    // 3. 将它重新修正为一颗二叉查找树
    rbtree_insert_fixup(tree, node1);
    return node1->data;
}
RB_Trav* RB_begin(RB_Tree*tree)
{
   RB_Trav*re=(RB_Trav*)malloc(sizeof(RB_Trav));
   RB_Trav_init(re);
   if(tree->iterator_init!=NULL)
   {
        tree->iterator_init(re);
   }
   re->it=rbtree_minimum(tree);
   return re; 
}
RB_Trav* RB_rbegin(RB_Tree*tree)
{
    RB_Trav*re=(RB_Trav*)malloc(sizeof(RB_Trav));
    RB_Trav_init(re);
    if(tree->iterator_init!=NULL)
    {
        tree->iterator_init(re);
    }
    re->it=rbtree_maximum(tree);
    return re; 
}
void* RB_next(RB_Trav*it)
{
    if(it->it==NULL)
    {
        return NULL;
    }
    RB_Node* node=rbtree_successor(it->it);
    if(node==NULL)
    {
        it->it=NULL;
        return NULL;
    }
    else
    {
        it->it=node;
        return node->data;
    }
}
void* RB_prev(RB_Trav*it)
{
    if(it->it==NULL)
    {
        return NULL;
    }
   RB_Node* node=rbtree_predecessor(it->it);
   if(node==NULL)
   {
        it->it=NULL;
        return NULL;
   }
   else
   {    it->it=node;
       return node->data; 
   } 

}
RB_Node* rbtree_minimum(RB_Tree *tree)
{
    RB_Node *node=NULL;

    if (tree!=NULL)
    {
        if(tree->root==NULL)
        {
            return NULL;
        }
        node=tree->root;
        while(node->left!=NULL)
        {
            node=node->left;
        }
        return node;
        
    }

    if (node == NULL)
    {
        return NULL;
    }

    return NULL;
}

RB_Node* rbtree_maximum(RB_Tree *tree)
{
    RB_Node *node=NULL;

    if (tree!=NULL)
    {
        if(tree->root==NULL)
        {
            return NULL;
        }
        node=tree->root;
        while(node->right!=NULL)
        {
            node=node->right;
        }
        return node;
        
    }

    if (node == NULL)
    {
        return NULL;
    }
    return NULL;
}

/* 
 * 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
 */

RB_Node* rbtree_successor(RB_Node *x)
{
    RB_Node* node=NULL;
    // 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
    if (x->right != NULL)
    {
        node=x->right;
        while(node->left!=NULL)
        {
            node=node->left;
        }
        return node;
    }

    // 如果x没有右孩子。则x有以下两种可能：
    // (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
    // (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
    else
    {
        node = x->parent;
        while ((node!=NULL) && (x==node->right))
        {
            x = node;
            node = node->parent;
        }
    }
    return node;
}
 
/* 
 * 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
 */

RB_Node* rbtree_predecessor(RB_Node *x)
{
    RB_Node* node=NULL;
    // 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
    if (x->left != NULL)
    {
        node=x->left;
        while(node->right!=NULL)
        {
            node=node->right;
        }
        return node;
    }
    else
    {
    // 如果x没有左孩子。则x有以下两种可能：
    // (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
    // (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
        node = x->parent;
        while ((node!=NULL) && (x==node->left))
        {
            x = node;
            node = node->parent;
        }
    }
    return node;
}
RB_Node* RB_find1(RB_Tree* tree,void*data)
{
     RB_Node* node=tree->root;
    int re=0;
    while(node!=NULL)
    {
        re=tree->cmp(data,node->data);
        if(re>0)
        {
            node=node->right;
        }
        else if(re<0)
        {
            node=node->left;
        }
        else
        {
            return node;
        }
    }
    return NULL;
}
void* RB_find(RB_Tree *tree, void*data)
{
    RB_Node* node=RB_find1(tree,data);
    if(node!=NULL)
    {
        return node->data;
    }
    return NULL;

}
/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     RB_Node 待修正的节点
 */

static void rbtree_delete_fixup(RB_Tree *tree, RB_Node *node, RB_Node *parent)
{
    RB_Node *other=NULL;

    while ((!node ||node->color==BLACK) && node != tree->root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color==RED)
            {
                // Case 1: x的兄弟w是红色的 
                other->color=BLACK; 
                parent->color=RED;
                rbtree_left_rotate(tree, parent);
                other = parent->right;
            }
            if ((!other->left || other->left->color==BLACK) &&
                (!other->right || other->right->color==BLACK))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                other->color=RED;  
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || other->right->color==BLACK)
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    other->left->color=BLACK;
                    other->color=RED;
                    rbtree_right_rotate(tree, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                other->color=parent->color;
                parent->color=BLACK;
                other->right->color=BLACK;
                rbtree_left_rotate(tree, parent);
                node = tree->root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (other->color==RED)
            {
                // Case 1: x的兄弟w是红色的 
                other->color=BLACK; 
                
                parent->color=RED;
                rbtree_right_rotate(tree, parent);
                other = parent->left;
            }
            if ((!other->left || other->left->color==BLACK) &&
                (!other->right || other->right->color==BLACK))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                other->color=RED;  
                
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color  ==BLACK)
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    other->right->color=BLACK;
                    other->color=RED;
                    rbtree_left_rotate(tree, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                other->color=parent->color;
                parent->color=BLACK;
                other->left->color=BLACK;
                rbtree_right_rotate(tree, parent);
                node = tree->root;
                break;
            }
        }
    }
    if (node)
    {
        node->color=BLACK;
    }
}

int RB_erase(RB_Tree*tree,void*data)
{
    RB_Node*node=RB_find1(tree,data);
    if(node==NULL)
    {
        return 0;
    }
    tree->size--; 
    RB_Node *child, *parent;
    int color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        RB_Node *replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
        {
            replace = replace->left;
        }

        // "RB_Node节点"不是根节点(只有根节点不存在父节点)
        if (node->parent)
        {
            if (node->left == node)
            {
                node->parent->left = replace;
            }
            else
            {
                node->parent->right = replace;
            }
        } 
        else
        { 
            // "RB_Node节点"是根节点，更新根节点。
            tree->root=replace;
        }
        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = replace->parent;
        // 保存"取代节点"的颜色
        color = replace->color;

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child不为空
            if (child)
            {
                child->parent=parent;
            }
            parent->left = child;

            replace->right = node->right;
            node->right=replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
        {
            rbtree_delete_fixup(tree, child, parent);
        }
    //    printf("hre\n");
        tree->del(node->data);
        free(node);

        return 1;
    }

    if (node->left !=NULL)
    {
        child = node->left;
    }
    else
    { 
        child = node->right;
    }   
    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
    {
        child->parent = parent;
    }

    // "RB_Node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
    }
    else
    {
        tree->root = child;
    }

    if (color == BLACK)
    {
        rbtree_delete_fixup(tree, child, parent);
    }
    tree->del(node->data);
    free(node);
   // printf("hre\n");
    return 1;
}
RB_Tree_func(int)
RB_Tree_func(double)

/* 
 * 查找最小结点：返回tree为根结点的红黑树的最小结点。
 */
/*


int rbtree_minimum(RBRoot *root, int *val)
{

}
 */
/* 
 * 查找最大结点：返回tree为根结点的红黑树的最大结点。
 */
/*

*/


/*
 * 创建结点
 *
 * 参数说明：
 *     key 是键值。
 *     parent 是父结点。
 *     left 是左孩子。
 *     right 是右孩子。
 */
/*
static RB_Node* create_rbtree_RB_Node(Type key, RB_Node *parent, RB_Node *left, RB_Node* right)
{
    RB_Node* p;

    if ((p = (RB_Node *)malloc(sizeof(RB_Node))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK; // 默认为黑色

    return p;
}
*/
/* 
 * 新建结点(节点键值为key)，并将其插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根
 *     key 插入结点的键值
 * 返回值：
 *     0，插入成功
 *     -1，插入失败
 */
/*
int insert_rbtree(RBRoot *root, Type key)
{
    RB_Node *RB_Node;    // 新建结点

    // 不允许插入相同键值的节点。
    // (若想允许插入相同键值的节点，注释掉下面两句话即可！)
    if (search(root->RB_Node, key) != NULL)
        return -1;

    // 如果新建结点失败，则返回。
    if ((RB_Node=create_rbtree_RB_Node(key, NULL, NULL, NULL)) == NULL)
        return -1;

    rbtree_insert(root, RB_Node);

    return 0;
}*/



/* 
 * 删除结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     RB_Node 删除的结点
 */
/*
void rbtree_delete(RBRoot *root, RB_Node *RB_Node)
{

}
*/
/* 
 * 删除键值为key的结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 键值
 */
/*
void delete_rbtree(RBRoot *root, Type key)
{
    RB_Node *z, *RB_Node; 

    if ((z = search(root->RB_Node, key)) != NULL)
        rbtree_delete(root, z);
}
*/
/*
 * 销毁红黑树
 */
/*

*/
/*
 * 打印"红黑树"
 *
 * tree       -- 红黑树的节点
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
/*
static void rbtree_print(RBTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            printf("%2d(B) is root\n", tree->key);
        else                // tree是分支节点
            printf("%2d(%s) is %2d's %6s child\n", tree->key, rb_is_red(tree)?"R":"B", key, direction==1?"right" : "left");

        rbtree_print(tree->left, tree->key, -1);
        rbtree_print(tree->right,tree->key,  1);
    }
}

void print_rbtree(RBRoot *root)
{
    if (root!=NULL && root->RB_Node!=NULL)
        rbtree_print(root->RB_Node, root->RB_Node->key, 0);
}*/
#undef RED
#undef BLACK