#ifndef LIB_CELL_TRAITS
#define LIB_CELL_TRAITS
//#define FACE_REQUIRE
//表示我要处理的是单形cell
#define SIMPLEX_REQUIRE
//表示我要按照流形的标准来处理
#define MANIFOLD_REQUIRE
#define template_v Vertex
#define template_f Face
#define template_c Cell
#define template_hf HalfFace

#define template_m Mesh
#include<stdlib.h>
#include <tool/tools_node.h>
#ifdef SIMPLEX_REQUIRE

#endif

typedef struct VertexT{}VertexT;
typedef struct CellT{}CellT;
typedef struct MeshT{}MeshT;
typedef struct FaceT{}FaceT;
typedef struct HalfT{}HalfT;

//Node operator++(Node);
#endif
