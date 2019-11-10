#ifndef GLFW_CALLBACK
#define GLFW_CALLBACK
#undef OpenglAlg
//#include<OpenglAlg.h>

#include "Arcroll.h"
#include<GLFW/glfw3.h>
GlobalInfo globalinfo;
Arcroll arc;

Mesh_view_data m_v_data;

void decode_globalinformation1()
{


    if(globalinfo.key==GLFW_KEY_F)
    {
        GLfloat* color;
        color= (GLfloat*)m_v_data.F_color[0];

        for(int i=0;i<3;i++)
        {
            color[m_v_data.information*9+i*3+0]=1.0;
            color[m_v_data.information*9+i*3+1]=0.0;
            color[m_v_data.information*9+i*3+2]=0.0;            
                         
                    
        }
        glBindBuffer(GL_ARRAY_BUFFER,m_v_data.Buffers[0][4]);
       // glBufferData(GL_ARRAY_BUFFER,m_v_data.F_color_size[0],0,GL_STATIC_DRAW);
                
        glBufferSubData(GL_ARRAY_BUFFER,sizeof(GLfloat)*9*m_v_data.information,sizeof(GLfloat)*9,&color[9*m_v_data.information]);
        glBindBuffer(GL_ARRAY_BUFFER,0);

    }
    else if(globalinfo.key==69)
    {
        Eigen::MatrixXf* V=(Eigen::MatrixXf*)m_v_data.F_V->value;
        Eigen::MatrixXi* F=(Eigen::MatrixXi*)m_v_data.F_F->value;
        GLfloat *v1=(GLfloat*)malloc(sizeof(GLfloat)*3),*v2=(GLfloat*)malloc(sizeof(GLfloat)*3);
        m_v_data.marked_edges=node_overlying(m_v_data.marked_edges,(void*)v1);
        m_v_data.marked_edges=node_overlying(m_v_data.marked_edges,(void*)v2);
        GLfloat vertices[2][3];
        for(int i=0;i<3;i++)
        {
            v1[i]=V->coeff(F->coeff(m_v_data.information,globalinfo.readpixelcolor[3]%3),i);
            v2[i]=V->coeff(F->coeff(m_v_data.information,globalinfo.readpixelcolor[3]/3),i);
        
            vertices[0][i]=v1[i];
            vertices[1][i]=v2[i];
        }
        int size=node_size(m_v_data.marked_edges),temp_size=node_size(m_v_data.F_V)+node_size(m_v_data.E_V);

        glBindBuffer(GL_ARRAY_BUFFER,m_v_data.Buffers[temp_size][0]);
        //有的教程不是说要先添加glBufferData么
        //glBufferData(GL_ARRAY_BUFFER,100*2*3*sizeof(GLfloat),0,GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER,(size-2)*sizeof(GLfloat)*3,sizeof(vertices),vertices);
        glBindBuffer(GL_ARRAY_BUFFER,0);


        //V->coeff(F->coeff(m_v_data.information,globalinfo.readpixelcolor[3]%3));
        //V->coeff(F->coeff(m_v_data.information,(int)globalinfo.readpixelcolor[3]/3));
         
        printf("node size: %d\n",size); 
                
                
    }


}


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
        //unsigned char *readpixelcolor=(unsigned char*)malloc(sizeof(unsigned char)*36);
                float y;

                y=(float)globalinfo.resolution[1]-globalinfo.mouse_coord[1];
        //unsigned char readpixelcolor[36];

                //printf("weizhi %lf %lf\n",globalinfo.mouse_coord[0],(float)globalinfo.resolution[1]-globalinfo.mouse_coord[1]);
                glReadPixels(globalinfo.mouse_coord[0],y,3,3,GL_RGBA,GL_UNSIGNED_BYTE,globalinfo.readpixelcolor);
        //printf()
                for(int i=0;i<36;i++)
                {
                    printf("%d ",globalinfo.readpixelcolor[i]);
                }
				m_v_data.information=globalinfo.readpixelcolor[0]*255*255+globalinfo.readpixelcolor[1]*255+globalinfo.readpixelcolor[2];
                printf("\n%d\n",m_v_data.information);          
                decode_globalinformation1();
                arc.L_init(&arc);
                break;
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
