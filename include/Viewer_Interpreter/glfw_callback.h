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
/* 以下函数待实现 */
void viewer_animation(Viewer_World*);
/* 实现拖拽读取文件的功能 */
void viewer_drop_callback(GLFWwindow* window,int count,const char** paths);
/*
glfwSetDropCallback(window, drop_callback);

The callback function receives an array of paths encoded as UTF-8.

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
int i;
for (i = 0;  i < count;  i++)
    handle_dropped_file(paths[i]);
}

*/

//
#ifdef __cplusplus
}
#endif
#endif

