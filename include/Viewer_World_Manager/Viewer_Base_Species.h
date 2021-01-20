#ifndef VIEWER_BASE_SPECIES_H
#define VIEWER_BASE_SPECIES_H
#include<Math/Viewer_Matrix4x4.h>
#include <tools_node.h>
#define Matrix4x4 Viewer_Matrix4x4_

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Viewer_Something{
	char* name;
	int name_id;
	int id;
	unsigned int create_date;
	int disappear;
	
	int viewport[4];

	int marked_element;
	void* mesh;

	//Node* history_avatar;

	void* evolution;
	void* prop;
}Viewer_Something;
void Viewer_Something_init( Viewer_Something*);

typedef struct Viewer_Texture
{
	char* image_file;
	int width,height,n;
	unsigned char* data;
	float* each_face_texture_coord;
	unsigned int tex;
	void* prop;
}Viewer_Texture;

void Viewer_Texture_init(Viewer_Texture*);

typedef struct Viewer_Faces
{


	float *Data,*color,*normal;
	unsigned int* Data_index;
	unsigned int normal_rows;
	unsigned int color_rows;
	//
	unsigned int* marked_faces_index;
	

    	unsigned int Data_index_rows;
	unsigned int Data_rows;
	float triangle_coordinate[3];	
	
	void(*compute_normal)(struct Viewer_Faces*);
	void (*random_color)(struct Viewer_Faces*);
	void (*set_color)(struct Viewer_Faces*,float*);
	int is_reversal_normal;
	Matrix4x4 *mat;
	Viewer_Something* texture;
	int is_transparent;
	void* evolution;
	void* prop;

	unsigned int VAO,*Buffers;
}Viewer_Faces;
void Viewer_Faces_set_color(Viewer_Faces*,float*);
void Viewer_Faces_compute_normal(Viewer_Faces*);
void Viewer_Faces_random_color(Viewer_Faces*);
void Viewer_Faces_init(Viewer_Faces*);
typedef struct Viewer_Camera
{
	/* 四维矩阵表示了相机的旋转（相机镜头方向），和位置。主要是修改这个矩阵 */
	/*该矩阵的上矩阵块应该是3阶单位正交阵*/
	Matrix4x4* matrix;
	/* 这个是上面矩阵的逆，加速运算 */

	
	Matrix4x4* matrix_inverse;
	Matrix4x4* Proj;
	//void (*set_using)(struct Viewer_world*,struct Viewer_Camera* c);
	int is_using;
	/* 相机的聚焦点，主要用来旋转相机的轴点 */
	float focal_distance;
	void* prop;

}Viewer_Camera;
void Viewer_Camera_init(Viewer_Camera*);

typedef struct Viewer_Points
{
	float *Data,*color;
	unsigned int Data_rows;
	
	//unsigned int color_rows;
	//
	void (*set_color)(struct Viewer_Points*,float*);
	void (*random_color)(struct Viewer_Points*);	
	void* evolution;
	Matrix4x4* mat;
	float pointsize;
	void *prop;

	unsigned int VAO,*Buffers;
}Viewer_Points;
void Viewer_Points_init(struct Viewer_Points*);

typedef struct Viewer_Edges
{
	float *Data,*color;
	unsigned int* Data_index;
	
    	unsigned int Data_index_rows,Data_rows,color_rows;
	
	float edgesize;
	void (*set_color)(struct Viewer_Edges*,float*);
	void (*random_color)(struct Viewer_Edges*);
	Matrix4x4* mat;
	
	void* evolution;
	void *prop;

	unsigned int VAO,*Buffers;
}Viewer_Edges;
void Viewer_Edges_init(struct Viewer_Edges*);
void Viewer_Edges_set_color(Viewer_Edges*,float*v);
typedef struct Viewer_Cursor_Shape{
	char *shape_name;
	char *image_path;
	//void (*set_using)(struct Viewer_world*,struct Viewer_Cursor_Shape*);
	int is_using;	
	void * obj;
	void* prop;	

}Viewer_Cursor_Shape;

void Viewer_Cursor_Shape_init(struct Viewer_Cursor_Shape* vcs);


typedef struct Viewer_Texts{
	char * str;
	float xy[2],scale;	
	float colors[16];
	char* font_path;
	unsigned int VAO;
	unsigned int VBO[3];

	Matrix4x4 *mat;
	Matrix4x4* Proj;
	void* prop;
}Viewer_Texts;
void Viewer_Texts_init(struct Viewer_Texts*vtext );
void Viewer_Texts_initn(struct Viewer_Texts* vtext,char const *str,float x,float y,float s,float* c,char const *font_path);

typedef struct Viewer_UI_Mesh{

	float *Data,*color;
	unsigned int* Data_index;
	unsigned int color_rows;
	unsigned int* marked_faces_index;

    unsigned int Data_index_rows;
	unsigned int Data_rows;
	float triangle_coordinate[3];	
	
//	void (*random_color)(struct Viewer_Faces*);
	void (*set_color)(struct Viewer_Faces*,float*);
	Matrix4x4 *mat;
	Matrix4x4* Proj;
	Viewer_Something* texture;
	int is_transparent;
	void* evolution;
	void* prop;

	unsigned int VAO,*Buffers;
}Viewer_UI_Mesh;

void Viewer_UI_Mesh_init(Viewer_UI_Mesh* vum);


#ifdef __cplusplus
}
#endif
#undef Matrix4x4
#endif
