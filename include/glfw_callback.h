#ifndef GLFW_CALLBACK
#define GLFW_CALLBACK
#undef OpenglAlg
//#include<OpenglAlg.h>

#include<Arcroll.h>
#include<GLFW/glfw3.h>
GlobalInfo globalinfo;
Arcroll arc;
void cursor_position_callback(GLFWwindow* window,double x,double y)
{

globalinfo.mouse_coord[0]=x;
globalinfo.mouse_coord[1]=y;
if(globalinfo.button==GLFW_MOUSE_BUTTON_LEFT)
    printf("BUCUO%d\r\n",globalinfo.button);
return;


}
void mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{
globalinfo.button=button;
globalinfo.mouse_action=action;
if(action==GLFW_PRESS)
{
switch(button)
{
    case GLFW_MOUSE_BUTTON_LEFT:
        arc.L_init(&arc);
       // printf("nihao\r\n");

        break;
    default:
        return;

}

}
return;
}
void framebuffer_size_callback(GLFWwindow* window,int w,int h)
{
globalinfo.resolution[0]=(float)w;
globalinfo.resolution[1]=(float)h;
//可以尝试注释掉下面的语句
glViewport(0.0,0.0,w,h);
//return;
}
void key_callback(GLFWwindow* window,int key,int scancdoe,int action,int mods)
{
globalinfo.key=key;
globalinfo.key_action=action;
return;


}
#endif
