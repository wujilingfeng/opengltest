#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tools_rbtree.h>

typedef struct  rb_t
{
    int key;
    void *data;
}rb_t;
static void*t_copy(void* p)
{
    void* dup_p=malloc(sizeof(rb_t));
    memmove(dup_p,p,sizeof(rb_t));
    return dup_p;
}
static int t_cmp(const void* p1,const void* p2)
{
   rb_t* q1=(rb_t*)p1,*q2=(rb_t*)p2;
   if(q1->key>q2->key)
   {
        return 1;
   }
   else if(q1->key<q2->key)
   {
        return -1;
   }
   return 0;
}


void test_rb()
{
    RB_Tree* tree=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init(tree);
    tree->cmp=t_cmp;
    tree->copy=t_copy;
    rb_t t1;
    t1.key=1;
    tree->insert(tree,&t1);
    t1.key=9;
    tree->insert(tree,&t1);
    t1.key=5;
    tree->insert(tree,&t1);

    for(auto iter=tree->begin(tree);iter->it!=NULL;iter->next(iter))
    {
        printf("key:%d \n",((rb_t*)(iter->it->data))->key); 
    }
    for(auto iter=tree->rbegin(tree);iter->it!=NULL;iter->prev(iter))
    {
        printf("key:%d \n",((rb_t*)(iter->it->data))->key); 
    }


    /*jsw_rbtree_t *tree=jsw_rbnew(t_cmp,t_dup,t_rel);
    rb_t t1;
    t1.key=1;
    jsw_rbinsert(tree,&t1); 
    t1.key=9;
    jsw_rbinsert(tree,&t1);
    void *re=NULL;
        re=jsw_rbfind(tree,&t1);
    if(re!=NULL)
    {
        printf("shi\n");
        printf("re:%d\n",((rb_t*)(re))->key);
    }
    jsw_rbtrav_t* iter=jsw_rbtnew();

    void* re1=NULL;
    re1=jsw_rbtfirst(iter,tree);
    printf("key:%d\n",((rb_t*)(re1))->key);
*/
   // tree=jsw_rbnew(t_cmp,t_dup,t_rel);
    //jsw_rbinsert();
}

int main(int argc,char**argv)
{
    RB_Tree *tree=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init_int(tree);
    //RB_Tree_int_double
    RB_int r;
    r.key=0;
    tree->insert(tree,&r);
    r.key=-2;
    tree->insert(tree,&r);
    r.key=100;
   tree->insert(tree,&r);
    auto iter=tree->rbegin(tree);
    for(;iter->it!=NULL;iter->prev(iter))
    {
        iter->second(iter);
        printf("%d  ",*((int*)(iter->first(iter))));
    }
    free(iter);

    RB_Tree_free(tree);

    return 0;
}
