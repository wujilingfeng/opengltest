#ifndef VIEWER_H
#define VIEWER_H
#include "Viewer_Interpreter/Viewer_OpenGL_Interpreter.h"
#include "config.h"
#define Matrix4x4 Viewer_Matrix4x4_
#define V_oisp Viewer_Opengl_Interpreter_Shader_Program
#ifdef __cplusplus
extern "C"
{
#endif
static void Viewer_default_load_data(V_oisp* voisp);
static void Viewer_default_init_uniform(V_oisp*);
void Viewer_default_set_uniform(V_oisp*);




#ifdef __cplusplus
}
#endif
#undef Matrix4x4
#undef V_oisp
#endif
