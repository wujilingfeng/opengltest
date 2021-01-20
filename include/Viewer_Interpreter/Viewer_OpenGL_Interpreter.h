#ifndef VIEWER_OPENGL_INTERPRETER_H
#define VIEWER_OPENGL_INTERPRETER_H
#include<ft2build.h>
#include FT_FREETYPE_H
#include "Viewer_OpenGL_Interpreter_Shader.h"
//#include "glfw_callback.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define Viewer_oisp Viewer_Opengl_Interpreter_Shader_Program

typedef struct Viewer_Opengl_Interpreter
{
	Viewer_World* world;
	void (*interpreter)(struct Viewer_Opengl_Interpreter*);
	void (*update_data)(struct Viewer_Opengl_Interpreter*);
	Node* user_shader_program;
    int update;
    //int s_e;
	struct Viewer_oisp*(*create_shader_program)(struct Viewer_Opengl_Interpreter* voi,char*s1,char*s2,void(*load_data)(struct Viewer_oisp*),void(*render)(struct Viewer_oisp*),Viewer_World* vw);
	void *prop;
}Viewer_Opengl_Interpreter;
void Viewer_Opengl_Interpreter_init(Viewer_Opengl_Interpreter*);
void Viewer_Opengl_Interpreter_initd(Viewer_Opengl_Interpreter*,Viewer_World* );
void Viewer_Opengl_Interpreter_interpreter(Viewer_Opengl_Interpreter*moi);
//struct Viewer_oisp* Viewer_create_shader_program(strcut Viewer_Opengl_Interpreter* voi,char*s1,char*s2,void(*load_data)(struct Viewer_oisp*),void(*render)(struct Viewer_oisp*));





#undef Viewer_oisp
#ifdef __cplusplus
}
#endif
#endif
