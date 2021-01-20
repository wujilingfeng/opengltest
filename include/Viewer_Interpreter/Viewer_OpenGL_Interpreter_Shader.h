#ifndef VIEWER_OPENGL_INTERPRETER_LOAD_RENDER_H
#define VIEWER_OPENGL_INTERPRETER_LOAD_RENDER_H
#include<ft2build.h>
#include FT_FREETYPE_H
#include "glfw_callback.h"

#include <config.h>

//#include "Viewer_OpenglAlg.h"

//#include <Viewer_World_Manager/Viewer_World_Manager.h>
//#include<GLFW/glfw3.h>
//#include "glfw_callback.h"
//#include <config.h>
#ifdef __cplusplus
extern "C"
{
#endif
#define Viewer_oisp Viewer_Opengl_Interpreter_Shader_Program
    
RB_Tree_func_declare(char)
typedef struct Viewer_FrameBuffer{
    GLuint framebuffer;
    GLuint colortex;
    GLuint rbo;
    void* prop;
}Viewer_FrameBuffer;

void Viewer_FrameBuffer_init(Viewer_FrameBuffer* vfb);

typedef struct Viewer_Opengl_Interpreter_Shader_Program
{
    ShaderInfo* shaders;
    GLuint program;
    void(*load_data)(struct Viewer_Opengl_Interpreter_Shader_Program*);
    void(*render)(struct Viewer_Opengl_Interpreter_Shader_Program*);
    GLuint *VAO;
    GLuint**Buffers;
    GLuint* tex;
    struct Viewer_World *vw;
    Viewer_FrameBuffer *vfb;
    //struct Viewer_Opengl_Interpreter* voi;
    void* prop;

}Viewer_Opengl_Interpreter_Shader_Program;


void Viewer_Opengl_Interpreter_Shader_Program_init(Viewer_Opengl_Interpreter_Shader_Program*);
GLuint* test_add_array_to_shader(Viewer_oisp* voisp);



void Viewer_default_load_data(Viewer_oisp* voisp);

void Viewer_default_render(Viewer_oisp* voisp);


void Viewer_load_quad_data(Viewer_oisp* voisp);
void Viewer_render_quad(Viewer_oisp* voisp);

void Viewer_load_ui_data(Viewer_Opengl_Interpreter_Shader_Program *voisp);
void Viewer_render_ui(Viewer_Opengl_Interpreter_Shader_Program*voisp);

#undef Viewer_oisp
#ifdef __cplusplus
}
#endif
#endif