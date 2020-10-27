//#include<Mesh_IO/Mesh_IO.h>
#ifndef VIEWERER_WORLD_MANAGER_H
#define VIEWERER_WORLD_MANAGER_H

#include<string.h>
#include<time.h>
#include "Viewer_Base_Species.h"
#include "Interactor_GlobalInfo.h"
#include <tools_rbtree.h>
#ifdef  __cplusplus
extern "C" {
#endif
//strcmp 比较字符串跟整数比较类似


//void Mesh_viewer_world_registe1(Mesh_viewer_world*,char**,int);

typedef struct Viewer_World{
	int species_id;
	RB_Tree *species2somethings;//<int,<int Viewer_Something>>
	RB_Tree *species_name_registe;//<int, char*>
	RB_Tree *something_id;//<int,int>
	//std::map<int,std::map<int,Mesh_viewer_something*>*>species2somethings;
	//std::map<int,char*>species_name_registe;
//use for give a single name
	//std::map<int,int>something_id;
	Interactor_GlobalInfo *g_info;
	Node* (*create_something)(struct Viewer_World*,char*);
	void (*remove_something)(struct Viewer_World*,Viewer_Something*);
	void (*print_self)(struct Viewer_World*);
	Node* (*find_species)(struct Viewer_World*,char*);
	Node*(*registe)(struct Viewer_World*,char*);
	float background_color[4];
	//char cursor_shape[40];	
	void *prop;
	void* *prop1;
}Viewer_World;
void Viewer_World_init(struct Viewer_World*);
Node* Viewer_World_find_species(struct Viewer_World*,char*);
Node* Viewer_World_registe(struct Viewer_World*,char*);
Node* Viewer_World_from_something_evolute(Node*,struct Viewer_World*);
Node* Viewer_World_create_something(struct Viewer_World*,char *);
void Viewer_World_remove_something(struct Viewer_World*,Viewer_Something*);
void Viewer_World_printself(Viewer_World*);

//void Mesh_viewer_add_face_data(Mesh_viewer_faces*,double *v,int v_cols,int v_rows,int *index,int i_cols,int i_rows,double *color);


#ifdef __cplusplus
}
#endif
#endif
