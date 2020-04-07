#include<iterator/cstruct_iterator.h>
bool operator==(const Node& node1,const Node& node2)
{

    return (node1.value==node2.value);

}
Node operator++(Node& node)
{
    if(node.Next==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node2;
    }

    node=*((Node*)node.Next);
    return node;
}
Node operator++(Node &node,int)
{
    Node node1=node;
    if(node.Next==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node1;
    }

    node=*((Node*)node.Next);
    return node1;
}
Node operator--(Node&node)
{
    if(node.Prev==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node2;
    }

    node=*((Node*)node.Prev);
    return node;

}
Node operator--(Node&node,int)
{
    Node node1=node;
    if(node.Prev==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node1;
    }

    node=*((Node*)node.Prev);
    return node1;


}
void* operator*(Node& node)
{
    return node.value;

}
