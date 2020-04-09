#ifndef VIEWER_OPENGL_INTERPRETER_H
#define VIEWER_OPENGL_INTERPRETER_H
#include "glfw_callback.h"
#include <config.h>
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
	struct Viewer_oisp*(*create_shader_program)(struct Viewer_Opengl_Interpreter* voi,char*s1,char*s2,void(*load_data)(struct Viewer_oisp*),void(*render)(struct Viewer_oisp*));
	void *prop;
}Viewer_Opengl_Interpreter;
void Viewer_Opengl_Interpreter_init(Viewer_Opengl_Interpreter*);
void Viewer_Opengl_Interpreter_interpreter(Viewer_Opengl_Interpreter*moi);


typedef struct Viewer_Opengl_Interpreter_Shader_Program
{
	ShaderInfo* shaders;
	GLuint program;
	void(*load_data)(struct Viewer_Opengl_Interpreter_Shader_Program*);
	void(*render)(struct Viewer_Opengl_Interpreter_Shader_Program*);
	GLuint *VAO;
	GLuint**Buffers;
	GLuint* tex;
	Viewer_Opengl_Interpreter* voi;
	void* prop;


}Viewer_Opengl_Interpreter_Shader_Program;
void Viewer_Opengl_Interpreter_Shader_Program_init(Viewer_Opengl_Interpreter_Shader_Program*);
GLuint* test_add_array_to_shader(Viewer_oisp* voisp);

#undef Viewer_oisp
#ifdef __cplusplus
}
#endif
#endif
