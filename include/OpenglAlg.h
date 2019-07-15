#ifndef OpenglAlg
#define OpenglAlg
//#include<cstdio.h>
#include<stdio.h>
#include<stdlib.h>
#include "Dense"
//#include<cstl/cvector.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include<stb_image.h>
#include<glad/glad.h>
#include<GL/gl.h>
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
int key_action=-1;
}GlobalInfo;
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
/*vector_t* _Shader_(ShaderInfo* shaders)
{
vector_t* pvec_v1=create_vector(int);
if(pvec_v1==NULL)
{
printf("this \r\n");
return NULL;
}
vector_init(pvec_v1);
ShaderInfo* entry=shaders;	
while(entry->type!=GL_NONE)
{
	GLuint shader=glCreateShader(entry->type);
const GLchar* source= _ReadFile_(entry->filename);
	if(source==NULL)
	{
	printf("this file is blank\r\n");
	
	return NULL;
	}
glShaderSource(shader,1,&source,NULL);
free((GLchar *)source);
glCompileShader(shader);
GLint compiled;
glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
if(!compiled)
{
#ifdef _DEBUG
	GLsizei len;
	glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&len);
	GLchar* log=(GLchar*)malloc(len+1);
	glGetShaderInfoLog(shader,len,&len,log);
	printf("shader compiled error,%s\r\n",log);
	free(log);
#endif
	return NULL;

}

vector_push_back(pvec_v1,shader);
entry++;
}
return pvec_v1;

}




GLuint _Program_ (vector_t* pvec_v1,bool burning=false)
{
	if(pvec_v1==NULL)
	{
	
		printf("pvec_v2 is null\r\n");
		return 0;
	}
int size=vector_size(pvec_v1);
if(size==0)
{
	return 0;
}
GLuint program=glCreateProgram();
for(int i=0;i<size;i++)
{
glAttachShader(program,*(GLuint*)vector_at(pvec_v1,i));

}
glLinkProgram(program);
GLint linked;
glGetProgramiv(program,GL_LINK_STATUS,&linked);
if(!linked)
{
#ifdef _DEBUG

              GLint infoLen;
glGetProgrmiv(program,GL_INFO_LOG_LENGTH,&infolen)
char* strinfo=(char*)malloc(infolen+1);
glGetProgramInfoLog(program,infolen,NULL,strinfo);
printf("can't linked ,&s\r\n",strinfo);
free(strinfo);
#endif
glDeleteProgram(program);
return 0;

}
if(burning)
{
for(int i=0;i<size;i++)
{
glDeleteShader(*(GLuint*)vector_at(pvec_v1,i));
//vector_destroy(pvec_v1);
//glDetachShader(program,*(GLuint*)vector_at(pvec_v1,i));
}
}
return program;

//return program;


}
*/
void _Shader_(ShaderInfo* shaders);



GLuint _Program_ (ShaderInfo* shaderinfos);

void _Texture_ (ImageInfo& image,GLuint texture);


#endif
