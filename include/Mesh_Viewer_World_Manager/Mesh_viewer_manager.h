//#include<Mesh_IO/Mesh_IO.h>
#ifndef MESH_VIEWERER_MANAGER
#define MESH_VIEWERER_MANAGER
#define SPECIES2SOMETHING std::map<int,std::map<int,Mesh_viewer_something*>*>
#include<map>
#include<string.h>
#include<time.h>
#include<Math/Mesh_viewer_matrix4x4.h>
#include<Mesh_view/Interactor_GlobalInfo.h>
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
	//Mesh_view_something*(*create_something)(struct 		Mesh_viewer_world*,char*)=Mesh_viewer_world_create_something;
}Mesh_viewer_world;
void Mesh_viewer_world_printself(Mesh_viewer_world*);
void Mesh_viewer_points_init(struct Mesh_viewer_points*);
typedef struct Mesh_viewer_points
{
	float *Data,*color;
	unsigned int* Data_index;
	unsigned int VAO,*Buffers;
    	int Data_index_rows;
	int Data_rows;
	void *prop;
	void* evolution;
}Mesh_viewer_points;
void Mesh_viewer_edges_init(struct Mesh_viewer_edges*);
typedef struct Mesh_viewer_edges
{
	float *Data,*color;
	unsigned int* Data_index;
	unsigned int VAO,*Buffers;
    	int Data_index_rows;
	int Data_rows;
	void *prop;
	void* evolution;

}Mesh_viewer_edges;
void Mesh_viewer_faces_init(struct Mesh_viewer_faces*);
typedef struct Mesh_viewer_faces
{
	float *Data,*color,*normal;
	unsigned int* Data_index;
	unsigned int* marked_faces_index;
	unsigned int VAO,*Buffers;
    	int Data_index_rows;
	int Data_index_cols;
	int Data_rows;
	void* prop;
	void* evolution;

}Mesh_viewer_faces;
//void Mesh_viewer_add_face_data(Mesh_viewer_faces*,double *v,int v_cols,int v_rows,int *index,int i_cols,int i_rows,double *color);

typedef struct Mesh_viewer_camera
{
	Matrix4x4* matrix;
	Matrix4x4* matrix_inverse;
	int is_using;
	float focal_distance;
	void* prop;

}Mesh_viewer_camera;
void Mesh_viewer_camera_init(Mesh_viewer_camera*);

#ifdef __cplusplus
}
#endif
#endif
