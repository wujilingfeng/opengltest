#include<tool/tools_node.h>
int node_size(Node* node)
{
	int i=0;
    while(node!=NULL)
    {
        node=(Node*)node->Next;
        i++;
    }
    return i;
}
//标准不free value
void free_node(Node *node)
{
//Node* node1=node;

    Node* node1;
    while(node!=NULL)
    {
        node1=(Node*)node->Next;
        if(node->traits!=NULL)
        {free(node->traits);}
        free(node);
        node=node1;
    }

}
Node* node_find(Node* node,void* value)
{
    while(node!=NULL)
    {
        if(node->value==value)
        {break;}
        node=(Node*)node->Next;
    }
    return node;
}
//
Node* node_copy(Node* node)
{
	if(node==NULL)
	{
	return NULL;
	}
	Node* node1=(Node*)malloc(sizeof(Node));
	Node* node2=node1;
	Node_init(node1);
    while(node!=NULL)
    {
	    node2->value=node->value;
	    node=(Node*)node->Next;
	    if(node==NULL)
	    {
	        break;
	    }
        Node* node3=(Node*)malloc(sizeof(Node));
	    Node_init(node3);
	    node2->Next=(void*)node3;
	    node3->Prev=(void*)node2;
	    node2=node3;
    }

    return node1;
}
void Node_init(Node*node)
{

    node->Prev=NULL;
    node->Next=NULL;
    node->value=NULL;
    node->traits=NULL;
}
//node向前添加元素，与list.push_back相反
Node* node_overlying(Node*node,void *value)
{
    Node* node1=(Node*)malloc(sizeof(Node));
    Node_init(node1);
    node1->value=value;
    node1->Next=node;
    if(node!=NULL)
    {
        node->Prev=node1;

    }
    return node1;

}
Node* node_reverse(Node*node)
{
	if(node==NULL)
	{return NULL;}
	else
	{

		while(node->Next!=NULL)
		{
			node=(Node*)node->Next;

		}
		return node;
	}

}
void node_eliminate(Node* node)
{
    if(node==NULL)
    {
        return;
    }
    Node* node1=(Node*)node->Prev,*node2=(Node*)node->Next;
    if(node1!=NULL)
    {
        node1->Next=(void*)node2;
    }
    if(node2!=NULL)
    {
        node2->Prev=(void*)node1;
    }
    free(node);
    node=NULL;

}
//给一个node的开始节点，删除某个value的节点,并返回开始节点
Node* node_delete_value(Node* node,void* value)
{
    Node* node1=node_find(node,value);
    Node* re=node;
    if(node1->Prev==NULL)
    {
        re=(Node*)node1->Next;
    
    }
    node_eliminate(node1);
    return re;
}
