#include<Math/Mesh_viewer_matrix4x4.h>
#ifndef MESH_VIEWER_BASE_SPECIES
#define MESH_VIEWER_BASE_SPECIES
#ifdef __cplusplus
extern "C" {
#endif
typedef struct Mesh_viewer_texture
{
	char* image_file;
	int width,height,n;
	unsigned char* data;
	float* each_face_texture_coord;
	
	void* prop;
}Mesh_viewer_texture;

void Mesh_viewer_texture_init(Mesh_viewer_texture*);

typedef struct Mesh_viewer_faces
{
	float *Data,*color,*normal;
	unsigned int* Data_index;
	
	unsigned int* marked_faces_index;
	unsigned int VAO,*Buffers;
    	int Data_index_rows;
	int Data_rows;
	void* prop;
	void* evolution;
	Mesh_viewer_texture* texture;
	

}Mesh_viewer_faces;
void Mesh_viewer_faces_init(Mesh_viewer_faces*);
typedef struct Mesh_viewer_camera
{
	Matrix4x4* matrix;
	Matrix4x4* matrix_inverse;
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
}Mesh_viewer_points;
void Mesh_viewer_points_init(struct Mesh_viewer_points*);

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
void Mesh_viewer_edges_init(struct Mesh_viewer_edges*);

#ifdef __cplusplus
}
#endif
#endif
