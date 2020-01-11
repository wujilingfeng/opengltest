//#include<Mesh_IO/Mesh_IO.h>
#ifndef MESH_VIEWERER_MANAGER
#define MESH_VIEWERER_MANAGER
#define SPECIES2SOMETHING std::map<int,std::map<int,Mesh_viewer_something*>*>
#include<map>
#include<string.h>
#include<time.h>
#include "Mesh_viewer_base_species.h"
#include "Interactor_GlobalInfo.h"
#ifdef  __cplusplus
extern "C" {
#endif
//strcmp 比较字符串跟整数比较类似

void Mesh_viewer_something_init(struct Mesh_view_something*);
typedef struct Mesh_view_something{
	char* name;
	int name_id;
	int id;
	unsigned int create_date;
	int disappear;
	void* prop;
	void* mesh;
	//（历史记录）分身
	Node* history_avatar;
	//继承信息
	void* evolution;
}Mesh_viewer_something;
Node* Mesh_viewer_world_create_something(struct Mesh_viewer_world*,char *);
void Mesh_viewer_world_remove_something(struct Mesh_viewer_world*,Mesh_viewer_something*);

//void Mesh_viewer_world_registe1(Mesh_viewer_world*,char**,int);
Node* Mesh_viewer_world_registe(struct Mesh_viewer_world*,char*);
void Mesh_viewer_world_init(struct Mesh_viewer_world*);
Node* Mesh_viewer_world_find_species(struct Mesh_viewer_world*,char*);
Node* Mesh_viewer_from_something_evolute(Node*);

typedef struct Mesh_viewer_world{
	int species_id;
	std::map<int,std::map<int,Mesh_viewer_something*>*>species2somethings;
	std::map<int,char*>species_name_registe;
//use for give a single name
	std::map<int,int>something_id;
	Interactor_GlobalInfo *g_info;
	void *prop;
	void* *prop1;
}Mesh_viewer_world;
void Mesh_viewer_world_printself(Mesh_viewer_world*);

//void Mesh_viewer_add_face_data(Mesh_viewer_faces*,double *v,int v_cols,int v_rows,int *index,int i_cols,int i_rows,double *color);


#ifdef __cplusplus
}
#endif
#endif
