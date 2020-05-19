#ifndef NODE_CONTAINER_H
#define NODE_CONTAINER_H
#ifdef __cplusplus
extern "C"{
#endif
#include<stdlib.h>
typedef struct Node
{
    void* Prev;
    void* value;
    void*  Next;
    void* traits;

}Node;
void free_node(Node*);
void free_node_value(Node*);
Node* node_find(Node*,void*);
void Node_init(Node*);
Node* node_copy(Node*);
int node_size(Node*);
Node* node_overlying(Node*,void*);
Node* node_reverse(Node*);
Node* node_pushback(Node*,void*);
void node_elimnate(Node*);
Node *node_delete_value(Node*,void*);
Node* node_splicing(Node*n1,Node*n2);
#ifdef __cplusplus
}
#endif
#endif
