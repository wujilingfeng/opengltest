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
//printf("%lf",x);
if(globalinfo.button==GLFW_MOUSE_BUTTON_LEFT&&globalinfo.mouse_action==GLFW_PRESS)
{
    arc.L_move(&arc);

}
else if(globalinfo.button==GLFW_MOUSE_BUTTON_RIGHT&&globalinfo.mouse_action==GLFW_PRESS)
{
arc.R_move(&arc);
}

//printf("BUCUO%d\r\n",globalinfo.button);
return;


}
void mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{
globalinfo.button=button;
globalinfo.mouse_action=action;
//printf("nihao");
if(action==GLFW_PRESS)
{
switch(button)
{
    case GLFW_MOUSE_BUTTON_LEFT:
        arc.L_init(&arc);
       // printf("nihao\r\n");
    case GLFW_MOUSE_BUTTON_RIGHT:
        arc.R_init(&arc);
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
//最后一步将得到的画面显示在窗口的占位置
glViewport(0.0,0.0,w,h);
//return;
}
void key_callback(GLFWwindow* window,int key,int scancdoe,int action,int mods)
{
globalinfo.key=key;
globalinfo.key_action=action;
return;


}
void scroll_callback(GLFWwindow* window,double x,double y)
{
    //printf("%lf",y);
arc.M_move(&arc,y);
return;
}
#endif
