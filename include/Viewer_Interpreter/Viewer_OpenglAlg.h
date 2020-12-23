#ifndef VIEWER_OPENGLALG_H
#define VIEWER_OPENGLALG_H
#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
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
    void* prop;

}ImageInfo;

GLchar* _ReadFile_ (char* filename);
ImageInfo *_ReadImageFile_(char*);
void _Write_PNG_File_(char* filename,ImageInfo* imi);
void _Write_BMP_File_(char* filename,ImageInfo* imi);
void _is_reverse_image_reading(int is_reverse);
void _is_reverse_image_writing(int is_reverse);
void ImageInfo_free(ImageInfo*);
void _Shader_(ShaderInfo* shaders);



GLuint _Program_ (ShaderInfo* shaderinfos);

void _Texture_ (ImageInfo* image,GLuint texture);

void _Texture_Array_GL_FLOAT(ImageInfo*,GLuint texture);
void _Texture_Array_GL_R32UI(ImageInfo*,GLuint texture);



#ifdef __cplusplus
}
#endif
#undef _ReadFile_ 
#endif
