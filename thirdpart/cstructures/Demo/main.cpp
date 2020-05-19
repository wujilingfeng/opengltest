#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tools_rbtree.h>
/*typedef struct rb_t
{
    int key;
    void *value;

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
*/
void test_rb()
{

   /* RB_Tree* tree=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init(tree);
    tree->cmp=t_cmp;
    tree->copy=t_copy;
    rb_t t1;
    t1.key=3;
    tree->insert(tree,&t1);
    t1.key=2;
    tree->insert(tree,&t1);
    t1.key=-3;
    tree->insert(tree,&t1);
    t1.key=0;
    tree->insert(tree,&t1);
    t1.key=99;
    tree->insert(tree,&t1);
    t1.key=-82;
    tree->insert(tree,&t1);
    for(int i=0;i<34;i++)
    {
        t1.key=i;
        tree->insert(tree,&t1);
    }  
    print_self(tree);
    t1.key=20;
    tree->erase(tree,&t1);
    t1.key=-100;
    tree->erase(tree,&t1);
    print_self(tree);*/
}
void print_self(RB_Tree* tree)
{
    RB_Trav* it=tree->begin(tree);
    printf("size:%d\n",tree->size);
    for(;it->it!=NULL;it->next(it))
    {

        printf("%d   ",((RB_int*)(it->it->data))->key);
    
    }
    printf("\n");
    free(it);
}
int main(int argc,char**argv)
{
    


    RB_Tree*tree=(RB_Tree*)malloc(sizeof(RB_Tree));
    RB_Tree_init_int(tree);
    RB_int rbt,*rbt1;
    for(int i=0;i<99;i++)
    {
        rbt.key=i;
        tree->insert(tree,&rbt);
    }
    print_self(tree);
    rbt.key=240;
    rbt1=(RB_int*)(tree->find(tree,&rbt));
    tree->insert(tree,&rbt);
    print_self(tree);
    if(rbt1==NULL)
    {
        printf("dfsdfdn\n");
    }
   // rbt1=(RB_int*)(tree->find(tree,&rbt));
   // printf("find:%d\n",rbt1->key);
    /*printf("size:%d\n",tree->size);
    t1.key=30;
    tree->erase(tree,&t1);
    printf("size:%d\n",tree->size);*/
   //printf("size:%d\n",tree->size);
   // printf("%ld\n",tree->size);

  //  RB_Tree_free(tree);

    //RB_Tree_free(tree);

    return 0;
}
