#ifndef GLFW_CALLBACK
#define GLFW_CALLBACK
//#undef OpenglAlg
#include "OpenglAlg.h"
#include <Mesh_Viewer_World_Manager/Mesh_viewer_manager.h>
#include<GLFW/glfw3.h>
#ifdef __cplusplus
extern "C" {
#endif


void mesh_viewer_cursor_position_callback(GLFWwindow* window,double x,double y);
void mesh_viewer_mouse_button_callback(GLFWwindow* window,int button,int action,int mods);
void mesh_viewer_framebuffer_size_callback(GLFWwindow* window,int w,int h);
void mesh_viewer_key_callback(GLFWwindow* ,int,int,int,int );
void mesh_viewer_scroll_callback(GLFWwindow* window,double x,double y);
void mesh_viewer_set_callback(GLFWwindow* window);
//以下函数待实现
void mesh_viewer_animation(Mesh_viewer_world*);

//
#ifdef __cplusplus
}
#endif
#endif

