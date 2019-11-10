#ifndef LIB_CELL_MESH
#define LIB_CELL_MESH
//#include<Traits.h>
//#include<Vertex.h>
//#include<Face.h>
//#include<Cell.h>
//#include<cstl/cmap.h>
#include<map>
#include "lib_cell_Iterator.h"
//#include<Mesh_frame.h>
template_v  Mesh_get_vertex(struct Mesh*,int);
template_c  Mesh_get_cell(struct Mesh*,int);
template_f Mesh_get_face(struct Mesh*,int);
template_f* Mesh_get_facev(struct Mesh*,template_v**,int);
int Mesh_num_v(struct Mesh*);
int Mesh_num_c(struct Mesh*);
int Mesh_num_f(struct Mesh*);
int Mesh_num_hf(struct Mesh*);
template_v * Mesh_create_vertex(struct Mesh*);
template_v* Mesh_create_vertexv(struct Mesh*,double*,int);
template_c * Mesh_create_cell(struct Mesh*);
template_f * Mesh_create_face(struct Mesh*);
template_c* Mesh_create_cellv(struct Mesh*,template_v**,int);
template_c* Mesh_create_cellf(struct Mesh*,template_hf**,int size);
template_f * Mesh_create_facev(struct Mesh*,template_v**,int);
template_hf* Mesh_create_halfface(struct Mesh*,template_f*,template_v**,int);
bool Mesh_delete_vertex(struct Mesh*,template_v&,bool burning);
bool Mesh_delete_face(struct Mesh*,template_f&,bool burning);
bool Mesh_delete_cell(struct Mesh*,template_c&,bool burning);
bool Mesh_vertex_is_boundary(struct Mesh*,template_v&);
bool Mesh_face_is_boundary(struct Mesh*,template_f*);
Node* Mesh_node_of_boundary_face(struct Mesh*,template_f*);
void Mesh_external_cell_init_(struct Mesh*);
template_hf Mesh_opposite_halfface(template_hf&);
//void Mesh_cell_division(struct Mesh*,template_c*);
void reset_c_prop(struct Mesh*);
void reset_v_prop(struct Mesh*);
void reset_f_prop(struct Mesh*);
//bool mesh_delete_vertex(struct Mesh*,template_v *);
//bool mesh_delete_cell(struct Mesh*,template_c *);
//void mesh_rearrange_id(struct Mesh*);
typedef struct Mesh{
//	std::map<template_v *,std::vector<template_c *>> v_to_c;
    template_c external_cell;
	std::map<int,template_c*> cells;
	std::map<int, template_f*> faces;
	std::map<int,template_v*>vertices;
    std::map<int,template_hf*> halffaces;

	//map_t* cells=create_map(int,void*);

	int cell_id=0,vertex_id=0,face_id=0,halfface_id=0;
	MeshT traits;
    template_v  (*get_vertex)(struct Mesh*,int)=Mesh_get_vertex;
    template_c (*get_cell)(struct Mesh*,int)=Mesh_get_cell;
    template_f (*get_face)(struct Mesh*,int)=Mesh_get_face;
	template_f*(*get_facev)(struct Mesh*,template_v**,int)=Mesh_get_facev;
	int (*num_v)(struct Mesh*)=Mesh_num_v;
	int (*num_c)(struct Mesh*)=Mesh_num_c;
	int (*num_f)(struct Mesh*)=Mesh_num_f;
    int (*num_hf)(struct Mesh*)=Mesh_num_hf;
//	bool (*delete_vertex)(struct Mesh*,template_v *)=mesh_delete_vertex;
  //      bool (*delete_cell)(struct Mesh*,template_c *)=mesh_delete_cell;	
	template_v *(*create_vertex)(struct Mesh*)=Mesh_create_vertex;
   // template_v*(*create_myd)(struct Mesh*,double*,int)=Mesh_create_vertexv;
    
    template_v* (*create_vertexv)(struct Mesh*,double*,int)=Mesh_create_vertexv;
	template_c *(*create_cell)(struct Mesh*)=Mesh_create_cell;
    template_f*(*create_face)(struct Mesh*)=Mesh_create_face;
    
    template_c *(*create_cellv)(struct Mesh*,template_v**,int)=Mesh_create_cellv;
    template_c *(*create_cellf)(struct Mesh*,template_hf**,int)=Mesh_create_cellf;
    template_f *(*create_facev)(struct Mesh*,template_v**,int)=Mesh_create_facev;
    template_hf*(*create_halfface)(struct Mesh*,template_f*,template_v**,int)=Mesh_create_halfface;
//	void (*rearrange_id)(struct Mesh*)=mesh_rearrange_id;
    bool (*delete_cell)(struct Mesh*,template_c&,bool)=Mesh_delete_cell;       bool (*delete_vertex)(struct Mesh*,template_v&,bool)=Mesh_delete_vertex; 
    bool (*delete_face)(struct Mesh*,template_f&,bool)=Mesh_delete_face;
    bool (*vertex_is_boundary)(struct Mesh*,template_v&)=Mesh_vertex_is_boundary;
    bool (*face_is_boundary)(struct Mesh*,template_f*)=Mesh_face_is_boundary;
    Node* (*node_of_boundary_face)(struct Mesh*,template_f*)=Mesh_node_of_boundary_face;
    void (*external_cell_init_)(struct Mesh*)=Mesh_external_cell_init_;
    template_hf (*opposite_halfface)(template_hf&)=Mesh_opposite_halfface;
	iterator_v (*cv_begin)(struct Mesh*,const template_c&)=Mesh_cv_begin;
    iterator_v (*fv_begin)(struct Mesh*,const template_f&)=Mesh_fv_begin;
    iterator_v (*fv_end)(struct Mesh*,const template_f&)=Mesh_fv_end;
	iterator_v (*cv_end)(struct Mesh*,const template_c&)=Mesh_cv_end;
    iterator_c (*vc_begin)(struct Mesh*,const template_v&)=Mesh_vc_begin;
    iterator_c (*vc_end)(struct Mesh*,const template_v& )=Mesh_vc_end;
    iterator_f (*chf_begin)(struct Mesh*,const template_c&)=Mesh_chf_begin;
    iterator_f (*chf_end)(struct Mesh*,const template_c&)=Mesh_chf_end;
	void (*reset_c_prop)(struct Mesh*)=reset_c_prop;
	void (*reset_v_prop)(struct Mesh*)=reset_v_prop;
    void (*reset_f_prop)(struct Mesh*)=reset_f_prop;

	int simplex=1;
#ifdef MANIFOLD_REQUIRE
    int dimension=2;
#endif
        	
}Mesh;
#endif
