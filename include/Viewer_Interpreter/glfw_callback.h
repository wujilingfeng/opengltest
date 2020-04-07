#ifndef GLFW_CALLBACK_H
#define GLFW_CALLBACK_H
//#undef OpenglAlg
#include "Viewer_OpenglAlg.h"
#include <Viewer_World_Manager/Viewer_World_Manager.h>
#include<GLFW/glfw3.h>
#ifdef __cplusplus
extern "C" {
#endif


void viewer_cursor_position_callback(GLFWwindow* window,double x,double y);
void viewer_mouse_button_callback(GLFWwindow* window,int button,int action,int mods);
void viewer_framebuffer_size_callback(GLFWwindow* window,int w,int h);
void viewer_key_callback(GLFWwindow* ,int,int,int,int );
void viewer_scroll_callback(GLFWwindow* window,double x,double y);
void viewer_set_callback(GLFWwindow* window);
//以下函数待实现
void viewer_animation(Viewer_World*);

//
#ifdef __cplusplus
}
#endif
#endif

