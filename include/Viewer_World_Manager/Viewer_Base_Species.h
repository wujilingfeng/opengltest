#ifndef VIEWER_BASE_SPECIES_H
#define VIEWER_BASE_SPECIES_H
#include<Math/Viewer_Matrix4x4.h>
#include <tools_node.h>
#define Matrix4x4 Viewer_Matrix4x4_
//颜色要变成4通道
#ifdef __cplusplus
extern "C" {
#endif
typedef struct Viewer_Something{
	char* name;
	int name_id;
	int id;
	unsigned int create_date;
	int disappear;
	//对应glViewport函数
	int viewport[4];
//指向一个结构库
	int marked_element;
	void* mesh;
	//（历史记录）分身
	//Node* history_avatar;
	//继承信息
	void* evolution;
	void* prop;
}Viewer_Something;
void Viewer_Something_init( Viewer_Something*);
//应该修改为一个texture可以对应多个曲面
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

//四通道颜色
	float *Data,*color,*normal;
	unsigned int* Data_index;
	unsigned int normal_rows;
	unsigned int color_rows;
	unsigned int* marked_faces_index;
	
//面的数量
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
//以下变量为opengl解释器特别提供
	unsigned int VAO,*Buffers;
}Viewer_Faces;
void Viewer_Faces_set_color(Viewer_Faces*,float*);
void Viewer_Faces_compute_normal(Viewer_Faces*);
void Viewer_Faces_random_color(Viewer_Faces*);
void Viewer_Faces_init(Viewer_Faces*);
typedef struct Viewer_Camera
{
	//四维矩阵表示了相机的旋转（相机镜头方向），和位置。主要是修改这个矩阵
	Matrix4x4* matrix;
	//这个是上面矩阵的逆，加速运算
	Matrix4x4* matrix_inverse;
	Matrix4x4* Proj;
	int is_using;
	//相机的聚焦点，主要用来旋转相机的轴点
	float focal_distance;
	void* prop;

}Viewer_Camera;
void Viewer_Camera_init(Viewer_Camera*);

typedef struct Viewer_Points
{
	float *Data,*color;
	unsigned int Data_rows;
	//应该去除这个变量
	//unsigned int color_rows;
	//
	void (*set_color)(struct Viewer_Points*,float*);
	void (*random_color)(struct Viewer_Points*);	
	void* evolution;
	Matrix4x4* mat;
	float pointsize;
	void *prop;
//以下变量为opengl解释器特别提供
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
//以下变量为opengl解释器特别提供
	unsigned int VAO,*Buffers;
}Viewer_Edges;
void Viewer_Edges_init(struct Viewer_Edges*);
void Viewer_Edges_set_color(Viewer_Edges*,float*v);
typedef struct Viewer_Cursor_Shape{
	char shape_name[40];
	char image_path[70];
	void * obj;
	void* prop;	

}Viewer_Cursor_Shape;

#ifdef __cplusplus
}
#endif
#undef Matrix4x4
#endif
