#ifndef OpenglAlg
#define OpenglAlg
//#include<cstdio.h>
#include<stdio.h>
#include<stdlib.h>
#include <Dense>
#include <tool/tools_node.h>
//#include<cstl/cvector.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include<stb_image.h>
#include<glad/glad.h>
//#include<GL/gl.h>
#define _Program_  OpenglAlg_Program
#define _ReadFile_ OpenglAlg_ReadFile
#define _Shader_ OpenglAlg_Shader
#define _Texture_ OpenglAlg_Texture
typedef struct GlobalInfo{
float run_time=-1;
float *mouse_coord=NULL;
int *resolution=NULL;
int button=-1;
int mouse_action=-1;
int key=-1;
int key_action=0;
unsigned char *readpixelcolor;
}GlobalInfo;
typedef struct Mesh_view_data{
    Node* F_V=NULL;
    Node* F_F=NULL;
    Node* E_V=NULL;
    Node* E_E=NULL;
    float** F_color=NULL;
	int information=-1;
	Node* marked_edges=NULL;
	Node* marked_vertices=NULL;
	Node* marked_faces=NULL;
    int* F_color_size=NULL;
    GLuint* VAOs=NULL;
	GLuint** Buffers=NULL;

}Mesh_view_data;
void Mesh_view_data_init(Mesh_view_data* );
//Mesh_view_data m_v_data;

void GlobalInfo_init(GlobalInfo* ginf);
typedef struct ShaderInfo{
GLenum type;
const char* filename;
GLuint shader;

}ShaderInfo;
typedef struct ImageInfo{

unsigned char *data;
int width,height,n;

}ImageInfo;
Eigen::MatrixXf Projection(float,float,float,float);
const GLchar* _ReadFile_ (const char* filename);


void _Shader_(ShaderInfo* shaders);



GLuint _Program_ (ShaderInfo* shaderinfos);

void _Texture_ (ImageInfo& image,GLuint texture);


#endif
