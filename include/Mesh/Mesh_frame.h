#ifndef Mesh_frame
#define Mesh_frame
#include "Cell_Traits.h"
typedef struct Vertex{
    int id=0;
    double *point=NULL;
    int point_size=0;
    VertexT traits;
    Node * cells=NULL;
    Node *faces=NULL;
    void *prop=NULL;
}Vertex;
typedef struct HalfFace{
int id=0;
void** vertices=NULL;
int vertices_size=0;
void* cell=NULL;
void* face=NULL;
void *prop=NULL;
HalfT traits;
}HalfFace;

typedef struct Face{


int id=0;
void **vertices=NULL;
int vertices_size=0;
template_hf** halffaces=NULL;
//int halffaces_size=0;
FaceT traits;
void *prop=NULL;
}Face;





typedef struct Cell{
int id=0;
CellT traits;
void **vertices=NULL;
int vertices_size=0;
Node* halffaces=NULL;
void *prop=NULL;
}Cell;

#endif
