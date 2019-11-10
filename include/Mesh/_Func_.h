//#include<Vertex.h>
//#include<Face.h>
//#include<Cell.h>
//#include<Mesh_frame.h>
#include "Mesh.h"

//#include<Cell.h>
//#include<Mesh.h>
//template_v *new_v();
//template_c* new_c(int);
//template_m* new_m(int);
/*bool is_equal(vector_t *pv1,vector_t*pv2);
iterator_t find(map_t *pm,vector_t *pv);*/
//

//int node_size(Node*);

//void free_node(Node*);

void Vertex_init_(template_v*);
void Face_init_(template_f*);
void Cell_init_(template_c*);
void HalfFace_init_(template_hf*);
void free_Vertex(template_v*);
void free_Face(template_f*);
void free_HalfFace(template_hf*);
void free_Cell(template_c*);
void Face_remove_c(template_f*,template_c*);
void Vertex_remove_f(template_v*,template_f*);
void Vertex_remove_c(template_v*v,template_c*c);
void Cell_remove_f(template_c*,template_f*);
void lib_cell_init();

