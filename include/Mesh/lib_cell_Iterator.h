#ifndef lib_cell_Iterator
#define lib_cell_Iterator
#define iterator_v lib_cell_iterator_vertices
#define iterator_f lib_cell_iterator_faces
#define iterator_c lib_cell_iterator_cells
#define quote lib_cell_quote
#include "Mesh_frame.h"
//#include<map>
bool operator==(const Node&,const Node&);
//bool operator!=(const Node&,const Node&);
//往下（next)遍历++
Node operator++(Node&);
Node operator++(Node&,int);
Node operator--(Node&);
Node operator--(Node&,int);
void* operator*(Node&);


std::map<int,template_f*>::iterator Mesh_faces_begin(struct Mesh*);
std::map<int,template_f*>::iterator Mesh_faces_end(struct Mesh*);
std::map<int,template_v*>::iterator Mesh_vertices_begin(struct Mesh*);
std::map<int,template_v*>::iterator Mesh_vertices_end(struct Mesh*);
std::map<int,template_c*>::iterator Mesh_cells_begin(struct Mesh*);
std::map<int,template_c*>::iterator Mesh_cells_end(struct Mesh*);
typedef struct iterator_v{
void** value=NULL;
int i=0;
}iterator_v;
iterator_v operator++(iterator_v&); 
iterator_v operator++(iterator_v&,int);
template_v* quote(iterator_v&);
template_v operator*(iterator_v& );
bool operator!=(const iterator_v&,const iterator_v&);
typedef struct iterator_f{
Node node;
}iterator_f;
iterator_f operator++(iterator_f&);
iterator_f operator++(iterator_f&,int);
template_f* quote(iterator_f&);
template_f operator*(iterator_f&);
bool operator!=(const iterator_f&,const iterator_f&);
typedef struct iterator_c{
Node node;
}iterator_c;
iterator_c operator++(iterator_c&);
iterator_c operator++(iterator_c&,int);
template_c operator*(iterator_c&);
template_c* quote(iterator_c&);
bool operator!=(const iterator_c&,const iterator_c&);
iterator_v Mesh_fv_begin(struct Mesh*,const template_f& );
iterator_v Mesh_fv_end(struct Mesh*,const template_f&);
iterator_v Mesh_hfv_begin(struct Mesh*,template_hf *);
iterator_v Mesh_hfv_end(struct Mesh*,template_hf *);
iterator_v Mesh_cv_begin(struct Mesh*,const template_c&);
iterator_v Mesh_cv_end(struct Mesh*,const template_c&);
//iterator_f
iterator_f Mesh_vf_begin(struct Mesh*,const template_v&);
iterator_f Mesh_vf_end(struct Mesh*,const template_v&);
iterator_f Mesh_chf_begin(struct Mesh*,const template_c&);
iterator_f Mesh_chf_end(struct Mesh*,const template_c&);
//iterator_c

iterator_c Mesh_vc_begin(struct Mesh*,const template_v&);
iterator_c Mesh_vc_end(struct Mesh*,const template_v&);

//auto Mesh_vertices_begin(struct Mesh*);
//auto Mesh_veritces_end(struct Mesh*);
#endif
