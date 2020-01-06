#include<stdio.h>
#include<Mesh_view/Mesh_viewer.h>
#include "include/Arcroll.h"
void test_manager();
void test_intera(Mesh_viewer_world*);
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);//回调函数原型声明

void test_mesh_viewer();
int main() {
    //初始化GLFW
    test_manager();
    //Mesh_viewer_world mesh_viewer_world;
//Mesh_viewer_callback_information_init(&g_callback_info);
    //std::map<int,std::map<int,int>*> mymap;
    //test_show();
    //show(&mesh_viewer_world);
   return 0;
}

//输入控制，检查用户是否按下了返回键(Esc)
/*void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // 注意：对于视网膜(Retina)显示屏，width和height都会明显比原输入值更高一点。
    glViewport(0, 0, width, height);
}*/
void test_intera(Mesh_viewer_world* mw)
{
    char Intera[]="Intera";
    Node* n=Mesh_viewer_world_create_something(mw,Intera);
    Mesh_viewer_something *ms=(Mesh_viewer_something*)(n->value);
    Mesh_viewer_Intera* mi=(Mesh_viewer_Intera*)(ms->evolution);
    mi->g_info=mw->g_info;
    Mesh_viewer_camera* mc=0;
    char camera[]="Camera";
    Node*id=Mesh_viewer_world_find_species(mw,camera);
    
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(id->value)));
    for(auto iter1=iter->second->begin();iter1!=iter->second->end();iter1++)
    {
        mc=(Mesh_viewer_camera*)(iter1->second->evolution);
       if(iter1->second->disappear==0&&mc->is_using==1)
       {
           break;
       
       }
        else
        {
            mc=0;
        }
    }
    mi->prop=(void*)mc;
    Mesh_viewer_Arcroll* ma=(Mesh_viewer_Arcroll*)malloc(sizeof(Mesh_viewer_Arcroll));
    Mesh_viewer_Arcroll_init(ma);
    mi->representation=(void*)ma;
    mi->cursor_position_callback=Mesh_viewer_Arcroll_cursor_position_callback;
    free_node_value(id);
    free_node(id);
    free_node(n);
}
void test_manager()
{
    Mesh_viewer_world mw;
    Mesh_viewer_world_init(&mw);
    char  ch[]="faces";
    Node* n=Mesh_viewer_world_create_something(&mw,ch);
    
    Mesh_viewer_something* ms=(Mesh_viewer_something*)(n->value);
    free_node(node_reverse(n));
    float *v=(float*)malloc(sizeof(float)*8*3);
    unsigned int *f=(unsigned int*)malloc(sizeof(unsigned int)*4*12);
    v[0*3+0]=-0.500000;v[0*3+1]=-0.500000;v[0*3+2]=0.500000; 
    v[1*3+0]=0.500000; v[1*3+1]=-0.500000; v[1*3+2]=0.500000; 
    v[2*3+0]=-0.500000;v[2*3+1]= 0.500000;v[2*3+2] =0.500000; 
    v[3*3+0]=0.500000;v[3*3+1]=0.500000;v[3*3+2] =0.500000; 
    v[4*3+0]=-0.500000;v[4*3+1]= 0.500000;v[4*3+2]= -0.500000; 
    v[5*3+0]=0.500000;v[5*3+1]= 0.500000;v[5*3+2]= -0.500000; 
    v[6*3+0]=-0.500000;v[6*3+1]= -0.500000;v[6*3+2]= -0.500000; 
    v[7*3+0]=0.500000;v[7*3+1]= -0.500000;v[7*3+2]= -0.500000;
    f[0*4+0]=3; f[0*4+1]=2;f[0*4+2]=3;f[0*4+3]=1;
    f[1*4+0]=3; f[1*4+1]=2;f[1*4+2]=1;f[1*4+3]=0;
    f[2*4+0]=3; f[2*4+1]=4;f[2*4+2]=5;f[2*4+3]=3;
    f[3*4+0]=3; f[3*4+1]=4;f[3*4+2]=3;f[3*4+3]=2;
    f[4*4+0]=3; f[4*4+1]=6;f[4*4+2]=7;f[4*4+3]=5;
    f[5*4+0]=3; f[5*4+1]=6;f[5*4+2]=5;f[5*4+3]=4;
    f[6*4+0]=3; f[6*4+1]=0;f[6*4+2]=1;f[6*4+3]=7;
    f[7*4+0]=3; f[7*4+1]=0;f[7*4+2]=7;f[7*4+3]=6;
    f[8*4+0]=3; f[8*4+1]=3;f[8*4+2]=5;f[8*4+3]=7;
    f[9*4+0]=3; f[9*4+1]=3;f[9*4+2]=7;f[9*4+3]=1;
    f[10*4+0]=3; f[10*4+1]=4;f[10*4+2]=2;f[10*4+3]=0;
    f[11*4+0]=3;f[11*4+1]=4;f[11*4+2]=0;f[11*4+3]=6;
    Mesh_viewer_faces* mf=(Mesh_viewer_faces*)(ms->evolution);
    mf->Data=v;
    mf->Data_index=f;
    mf->Data_rows=8;
    mf->Data_index_rows=12;
    //mf->Data_index_cols=3;
    char camera[]="Camera";
    n=Mesh_viewer_world_create_something(&mw,camera);
    ms=(Mesh_viewer_something*)(n->value);
    Mesh_viewer_camera* mc=(Mesh_viewer_camera*)(ms->evolution);
    mc->is_using=1;
    free_node(n);
    test_intera(&mw);
    Mesh_viewer_world_printself(&mw);
    printf("GLFW_REPEAT:%d,GLFW_MOD_CONTROL:%d\n",GLFW_REPEAT,GLFW_MOD_CONTROL); 
    show(&mw);

}

