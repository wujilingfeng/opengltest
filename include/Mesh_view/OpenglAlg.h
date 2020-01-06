#ifndef OpenglAlg
#define OpenglAlg
#include<stdio.h>
#include<stdlib.h>

#include<glad/glad.h>
#include "Interactor_GlobalInfo.h"
#define _Program_  OpenglAlg_Program
#define _ReadFile_ OpenglAlg_ReadFile
#define _Shader_ OpenglAlg_Shader
#define _Texture_ OpenglAlg_Texture
#define _Texture_Array OpenglAlg_Texture_Array
#ifdef __cplusplus
extern "C" {
#endif



typedef struct ShaderInfo{
GLenum type;
char* filename;
GLuint shader;

}ShaderInfo;
typedef struct ImageInfo{

unsigned char *data;
int width,height,n;

}ImageInfo;

GLchar* _ReadFile_ (char* filename);

void _Shader_(ShaderInfo* shaders);



GLuint _Program_ (ShaderInfo* shaderinfos);

void _Texture_ (ImageInfo* image,GLuint texture);
void _Texture_Array(ImageInfo*, GLenum dataType, GLenum data_component, GLint GPU_internalFormat,GLuint texture);
#ifdef __cplusplus
}
#endif
#endif
