/*
  Red Black balanced tree library

    > Created (Julienne Walker): August 23, 2003
    > Modified (Julienne Walker): March 14, 2008
    >Modified (libo):2020
*/
#include "tools_rbtree.h"

#ifdef __cplusplus
#include <cstdlib>

using std::malloc;
using std::free;
using std::size_t;
#else
#include <stdlib.h>
#endif
static void *start ( RB_Trav *trav, RB_Tree *tree, int dir )
{
  trav->tree = tree;
  trav->it = tree->root;
  trav->top = 0;

  /* Save the path for later traversal */
  if ( trav->it != NULL ) 
  {
    while ( trav->it->link[dir] != NULL ) 
    {
      trav->path[trav->top++] = trav->it;
      trav->it = trav->it->link[dir];
    }
  }

  return trav->it == NULL ? NULL : trav->it->data;
}

static void *move ( RB_Trav *trav, int dir )
{
  if ( trav->it->link[dir] != NULL ) 
  {
    /* Continue down this branch */
    trav->path[trav->top++] = trav->it;
    trav->it = trav->it->link[dir];

    while ( trav->it->link[!dir] != NULL ) 
    {
      trav->path[trav->top++] = trav->it;
      trav->it = trav->it->link[!dir];
    }
  }
  else 
  {
    /* Move to the next branch */
    RB_Node *last;

    do 
    {
      if ( trav->top == 0 ) 
      {
        trav->it = NULL;
        break;
      }

      last = trav->it;
      trav->it = trav->path[--trav->top];
    } while ( last == trav->it->link[dir] );
  }

  return trav->it == NULL ? NULL : trav->it->data;
}

static void *RB_next ( RB_Trav *trav )
{
  return move ( trav, 1 ); /* Toward larger items */
}

static void *RB_prev ( RB_Trav *trav )
{
  return move ( trav, 0 ); /* Toward smaller items */
}

void RB_Node_init(RB_Node* jsw_n)
{
    jsw_n->red=1;
    jsw_n->data=NULL;
    jsw_n->prop=NULL;
    jsw_n->link[0]=NULL;
    jsw_n->link[1]=NULL;

}
static void default_free(void *p)
{
    free(p);
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

void RB_Trav_init(RB_Trav*trav)
{
    trav->tree=NULL;
    trav->it=NULL;
    trav->top=0;
	trav->first=NULL;
	trav->second=NULL;
    trav->prop=NULL;
    trav->next=RB_next;
    trav->prev=RB_prev;

}
static int is_red ( RB_Node *root )
{
  return root != NULL && root->red == 1;
}
static RB_Node *RB_single_ ( RB_Node *root, int dir )
{
  RB_Node *save = root->link[!dir];

  root->link[!dir] = save->link[dir];
  save->link[dir] = root;

  root->red = 1;
  save->red = 0;

  return save;
}
static RB_Node *RB_sdouble_ ( RB_Node *root, int dir )
{
  root->link[!dir] = RB_single_ ( root->link[!dir], !dir );

  return RB_single_ ( root, dir );
}
/*
RB_Tree *RB_Tree_new (int (*cmp)(const void*,const void*), void*(*copy)(void*), void (*del)(void*) )
{
  RB_Tree *rt = (RB_Tree *)malloc (sizeof(RB_Tree));

  if ( rt == NULL )
  {  return NULL;
  }
    RB_Tree_init(rt);

  rt->cmp = cmp;
  rt->copy = copy;

  rt->del = del;
  return rt;
}
*/
void RB_Tree_free ( RB_Tree *tree )
{
  RB_Node *it = tree->root;
  RB_Node *save;

  /*
    Rotate away the left links so that
    we can treat this like the destruction
    of a linked list
  */
  while ( it != NULL ) 
  {
    if ( it->link[0] == NULL )
    {
      /* No left links, just kill the node and move on */
      save = it->link[1];
      tree->del ( it->data );
      free ( it );
    }
    else {
      /* Rotate away the left link and check again */
      save = it->link[0];
      it->link[0] = save->link[1];
      save->link[1] = it;
    }

    it = save;
  }
  free ( tree );
}

void *RB_find ( RB_Tree *tree, void *data )
{
  RB_Node *it = tree->root;

  while ( it != NULL ) 
  {
    int cmp = tree->cmp ( it->data, data );

    if ( cmp == 0 )
    {
      break;
    }
    /*
      If the tree supports duplicates, they should be
      chained to the right subtree for this to work
    */
    it = it->link[cmp < 0];
  }

  return it == NULL ? NULL : it->data;
}

int RB_insert ( RB_Tree *tree, void *data )
{
  if ( tree->root == NULL ) 
  {
    /*
      We have an empty tree; attach the
      new node directly to the root
    */
    tree->root=(RB_Node*)malloc(sizeof(RB_Node));
    RB_Node_init(tree->root);
    tree->root->data=tree->copy(data);

    if ( tree->root == NULL )
    {return 0;
    }
  }
  else {
    RB_Node head = {0}; /* False tree root */
    RB_Node *g, *t;     /* Grandparent & parent */
    RB_Node *p, *q;     /* Iterator & parent */
    int dir = 0, last = 0;

    /* Set up our helpers */
    t = &head;
    g = p = NULL;
    q = t->link[1] = tree->root;

    /* Search down the tree for a place to insert */
    for ( ; ; ) 
    {
      if ( q == NULL ) 
      {
        /* Insert a new node at the first null link */
        p->link[dir]=q=(RB_Node*)malloc(sizeof(RB_Node));
        RB_Node_init(q);
        q->data=tree->copy(data);

        if ( q == NULL )
        {
        
          return 0;
        }
      }
      else if ( is_red ( q->link[0] ) && is_red ( q->link[1] ) ) 
      {
        /* Simple red violation: color flip */
        q->red = 1;
        q->link[0]->red = 0;
        q->link[1]->red = 0;
      }

      if ( is_red ( q ) && is_red ( p ) ) 
      {
        /* Hard red violation: rotations necessary */
        int dir2 = t->link[1] == g;

        if ( q == p->link[last] )
        {t->link[dir2] = RB_single_ ( g, !last );
        }
        else
        {
          t->link[dir2] = RB_sdouble_ ( g, !last );
        }
      }

      /*
        Stop working if we inserted a node. This
        check also disallows duplicates in the tree
      */
      if ( tree->cmp ( q->data, data ) == 0 )
      {
        break;
      }
      last = dir;
      dir = tree->cmp ( q->data, data ) < 0;

      /* Move the helpers down */
      if ( g != NULL )
      { t = g;
      }
      g = p, p = q;
      q = q->link[dir];
    }

    /* Update the root (it may be different) */
    tree->root = head.link[1];
  }

  /* Make the root black for simplified logic */
  tree->root->red = 0;
  ++tree->size;

  return 1;
}

int RB_erase ( RB_Tree *tree, void *data )
{
  if ( tree->root != NULL ) {
    RB_Node head = {0}; /* False tree root */
    RB_Node *q, *p, *g; /* Helpers */
    RB_Node *f = NULL;  /* Found item */
    int dir = 1;

    /* Set up our helpers */
    q = &head;
    g = p = NULL;
    q->link[1] = tree->root;

    /*
      Search and push a red node down
      to fix red violations as we go
    */
    while ( q->link[dir] != NULL ) 
    {
      int last = dir;

      /* Move the helpers down */
      g = p, p = q;
      q = q->link[dir];
      dir = tree->cmp ( q->data, data ) < 0;

      /*
        Save the node with matching data and keep
        going; we'll do removal tasks at the end
      */
      if ( tree->cmp ( q->data, data ) == 0 )
      {  f = q;
      }
      /* Push the red node down with rotations and color flips */
      if ( !is_red ( q ) && !is_red ( q->link[dir] ) ) 
      {
        if ( is_red ( q->link[!dir] ) )
        {   
            p = p->link[last] = RB_single_ ( q, dir );
        }
        else if ( !is_red ( q->link[!dir] ) ) 
        {
          RB_Node *s = p->link[!last];

          if ( s != NULL ) 
          {
            if ( !is_red ( s->link[!last] ) && !is_red ( s->link[last] ) ) 
            {
              /* Color flip */
              p->red = 0;
              s->red = 1;
              q->red = 1;
            }
            else {
              int dir2 = g->link[1] == p;

              if ( is_red ( s->link[last] ) )
              { 
                  g->link[dir2] = RB_sdouble_ ( p, last );
              }
              else if ( is_red ( s->link[!last] ) )
              {
                    g->link[dir2] = RB_single_ ( p, last );
              }
              /* Ensure correct coloring */
              q->red = g->link[dir2]->red = 1;
              g->link[dir2]->link[0]->red = 0;
              g->link[dir2]->link[1]->red = 0;
            }
          }
        }
      }
    }

    /* Replace and remove the saved node */
    if ( f != NULL ) {
      tree->del ( f->data );
      f->data = q->data;
      p->link[p->link[1] == q] =
        q->link[q->link[0] == NULL];
      free ( q );
    }

    /* Update the root (it may be different) */
    tree->root = head.link[1];

    /* Make the root black for simplified logic */
    if ( tree->root != NULL )
    {tree->root->red = 0;}

    --tree->size;
  }

  return 1;
}


RB_Trav* RB_begin(RB_Tree *tree)
{
    RB_Trav* re=(RB_Trav*)malloc(sizeof(RB_Trav));
    RB_Trav_init(re);
	if(tree->iterator_init!=NULL)
	{tree->iterator_init(re);}
    start(re,tree,0);
    return re;
}
RB_Trav*RB_rbegin(RB_Tree* tree)
{
    RB_Trav*re=(RB_Trav*)malloc(sizeof(RB_Trav));
    RB_Trav_init(re);
	if(tree->iterator_init!=NULL)
	{tree->iterator_init(re);}
    start(re,tree,1);
    return re;
}

RB_Tree_func(int)
RB_Tree_func(double)

