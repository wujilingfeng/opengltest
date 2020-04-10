#ifndef RB_TREE_H
#define RB_TREE_H

/*
  Red Black balanced tree library

    > Created (Julienne Walker): August 23, 2003
    > Modified (Julienne Walker): March 14, 2008
	>Modified (libo):2020
  This code is in the public domain. Anyone may
  use it or change it in any way that they see
  fit. The author assumes no responsibility for 
  damages incurred through use of the original
  code or any variations thereof.

  It is requested, but not required, that due
  credit is given to the original author and
  anyone who has modified the code through
  a header comment, such as this one.
*/
#ifdef __cplusplus
#include <cstddef>

using std::size_t;

extern "C" {
#else
#include<stdlib.h>
#include<string.h>
#include <stddef.h>
#endif
#ifndef HEIGHT_LIMIT
#define HEIGHT_LIMIT 64 /* Tallest allowable tree */
#endif


typedef struct RB_Node {
  int                red;     
  void              *data;   
  struct RB_Node *link[2];
  void *prop;
}RB_Node;

typedef struct RB_Tree {
  RB_Node *root; 
  int (*cmp)(const void* p1,const void* p2);  
  void* (*copy)(void*); 
  void  (*del)(void*);  
  size_t        size; 
	void *(*find)(struct RB_Tree*,void*);
	int (*insert)(struct RB_Tree*,void*);
	int (*erase)(struct RB_Tree*,void*);
	struct RB_Trav* (*begin)(struct RB_Tree*);
	struct RB_Trav*(*rbegin)(struct RB_Tree*);
	void (*iterator_init)(struct RB_Trav*);
	
  void *prop;
}RB_Tree;
typedef struct RB_Trav {
  RB_Tree *tree;               
  RB_Node *it;                 
  RB_Node *path[HEIGHT_LIMIT];
  size_t        top;
	void * (*next)(struct RB_Trav*);
	void* (*prev)(struct RB_Trav*);   
	void* (*first)(struct RB_Trav*);//仿照map接口
	void* (*second)(struct RB_Trav*);//仿照map接口
  void* prop;
}RB_Trav;
void RB_Node_init(RB_Node*);
void RB_Tree_init(RB_Tree* );
void RB_Trav_init(RB_Trav*);


void          RB_Tree_free ( RB_Tree *tree );
void         *RB_find (RB_Tree *tree, void *data );
int           RB_insert (RB_Tree *tree, void *data );
int           RB_erase ( RB_Tree *tree, void *data );

RB_Trav* RB_begin(RB_Tree *tree);
RB_Trav*RB_rbegin(RB_Tree* tree);
/*void         *RB_first (RB_Trav *trav, RB_Tree *tree );
void         *RB_last ( RB_Trav*trav,RB_Tree *tree );
void         *RB_next ( RB_Trav *trav );
void         *RB_prev ( RB_Trav*trav );*/
#define RB_Tree_func_declare(typevalue) typedef struct RB_##typevalue{typevalue key;void* value;void* prop;}RB_##typevalue;\
void RB_init_##typevalue(RB_##typevalue*);\
int RB_cmp_##typevalue(const void*p1,const void*p2 );\
void RB_Tree_init_##typevalue(RB_Tree*);


#define RB_Tree_func(typevalue)  int RB_cmp_##typevalue(const void*p1,const void*p2)\
{\
RB_##typevalue *q1=(RB_##typevalue*)p1,*q2=(RB_##typevalue*)p2;\
	if(q1->key>q2->key)\
	{\
		return 1;\
	}\
	else if(q1->key<q2->key)\
	{\
		return -1;\
	}\
	return 0;\
}\
static void* RB_copy_##typevalue(void* p)\
{\
	void* re=malloc(sizeof(RB_##typevalue));\
	memmove(re,p,sizeof(RB_##typevalue));\
	return re;\
}\
static void * get_key_##typevalue(RB_Trav* trav)\
{\
	return (void*)(&(((RB_##typevalue*)(trav->it->data))->key));\
}\
static void* get_value_##typevalue(RB_Trav*trav)\
{\
	return ((RB_##typevalue*)(trav->it->data))->value;\
}\
static void iter_init_##typevalue(RB_Trav*trav)\
{\
	trav->first=get_key_##typevalue;\
	trav->second=get_value_##typevalue;\
}\
void RB_Tree_init_##typevalue(RB_Tree* tree)\
{\
	RB_Tree_init(tree);\
	tree->copy=RB_copy_##typevalue;\
	tree->cmp=RB_cmp_##typevalue;\
	tree->iterator_init=iter_init_##typevalue;\
}\
void RB_init_##typevalue(RB_##typevalue* t)\
{\
t->value=NULL;\
t->prop=NULL;\
}




RB_Tree_func_declare(int)
RB_Tree_func_declare(double)

#ifdef __cplusplus
}
#endif

#endif
