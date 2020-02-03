#include<Math/Mesh_viewer_matrix4x4.h>
#include <tool/tools_node.h>
#ifndef MESH_VIEWER_BASE_SPECIES
#define MESH_VIEWER_BASE_SPECIES
#ifdef __cplusplus
extern "C" {
#endif
typedef struct Mesh_viewer_something{
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
void Mesh_viewer_something_init( Mesh_viewer_something*);
typedef struct Mesh_viewer_texture
{
	char* image_file;
	int width,height,n;
	unsigned char* data;
	float* each_face_texture_coord;
	unsigned int tex;
	void* prop;
}Mesh_viewer_texture;

void Mesh_viewer_texture_init(Mesh_viewer_texture*);

typedef struct Mesh_viewer_faces
{
	float *Data,*color,*normal;
	unsigned int* Data_index;
	unsigned int normal_rows;
	unsigned int color_rows;
	unsigned int* marked_faces_index;
	unsigned int VAO,*Buffers;
    	unsigned int Data_index_rows;
	unsigned int Data_rows;
	void* prop;
	void* evolution;
	void(*compute_normal)(struct Mesh_viewer_faces*);
	void (*random_color)(struct Mesh_viewer_faces*);
	Matrix4x4 *mat;
	Mesh_viewer_something* texture;
}Mesh_viewer_faces;
void Mesh_viewer_faces_compute_normal(Mesh_viewer_faces*);
void Mesh_viewer_faces_random_color(Mesh_viewer_faces*);
void Mesh_viewer_faces_init(Mesh_viewer_faces*);
typedef struct Mesh_viewer_camera
{
	Matrix4x4* matrix;
	Matrix4x4* matrix_inverse;
	Matrix4x4* Proj;
	int is_using;
	float focal_distance;
	void* prop;

}Mesh_viewer_camera;
void Mesh_viewer_camera_init(Mesh_viewer_camera*);

typedef struct Mesh_viewer_points
{
	float *Data,*color;
	unsigned int* Data_index;
	unsigned int VAO,*Buffers;
    	int Data_index_rows;
	int Data_rows;
	void *prop;
	void* evolution;
	Matrix4x4* mat;
}Mesh_viewer_points;
void Mesh_viewer_points_init(struct Mesh_viewer_points*);

typedef struct Mesh_viewer_edges
{
	float *Data,*color;
	unsigned int* Data_index;
	unsigned int VAO,*Buffers;
    	unsigned int Data_index_rows,Data_rows,color_rows;
	void *prop;
	void* evolution;
	Matrix4x4* mat;
}Mesh_viewer_edges;
void Mesh_viewer_edges_init(struct Mesh_viewer_edges*);

#ifdef __cplusplus
}
#endif
#endif
