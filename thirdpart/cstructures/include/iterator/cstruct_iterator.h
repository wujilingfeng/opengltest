#ifndef CSTRUCT_ITERATOR_H
#define CSTRUCT_ITERATOR_H
#include "../tools_node.h"

bool operator==(const Node&,const Node&);
//bool operator!=(const Node&,const Node&);
//往下（next)遍历++
Node operator++(Node&);
Node operator++(Node&,int);
Node operator--(Node&);
Node operator--(Node&,int);
void* operator*(Node&);



#endif

