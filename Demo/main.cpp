#include<Mesh_view/Mesh_viewer_interpreter.h>
#include "include/Arcroll.h"
void test_manager();
void test_intera(Mesh_viewer_world*);

void test_mesh_viewer();
void test_matrix();
int main(int argc,char*argv[]) 
{
    char* str1=(char*)malloc(sizeof(char)*100);
       printf("%s \n", strcat(strcat(str1,MESH_VIEWER_PATH),"/mesh.frag")
);
    test_matrix(); 
        //初始化GLFW
    test_manager();
       return 0;
}
void test_matrix()
{
    Matrix4x4 m;
    Matrix4x4_init_float(&m);
    float *data=(float*)(m.data);
    data[0*4+0]=1;data[0*4+1]=0;data[0*4+2]=3;data[0*4+3]=0;
    data[1*4+0]=1;data[1*4+1]=-5;data[1*4+2]=6;data[1*4+3]=0;
    data[2*4+0]=11;data[2*4+1]=0;data[2*4+2]=9;data[2*4+3]=0;
    data[3*4+0]=0;data[3*4+1]=0;data[3*4+2]=0;data[3*4+3]=1;
    Matrix4x4* p1;
    p1=m.inverse(&m);
    p1->print_self(p1);
    Matrix4x4_free(p1);
}
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
    mi->scroll_callback=Mesh_viewer_Arcroll_scroll_callback;
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

    Mesh_viewer_faces* mf=(Mesh_viewer_faces*)(ms->evolution);
    free_node(node_reverse(n));
    mf->color_rows=12;mf->normal_rows=12;
    float *v=(float*)malloc(sizeof(float)*8*3);
    unsigned int *f=(unsigned int*)malloc(sizeof(unsigned int)*4*12);
    float *texcoords=(float*)malloc(sizeof(float)*12*7);
    memset(texcoords,0,sizeof(float)*12*7);
    mf->random_color(mf);
    //ms->disappear=1;
    v[0*3+0]=-0.500000;v[0*3+1]=-0.500000;v[0*3+2]=0.500000; 
    v[1*3+0]=0.500000; v[1*3+1]=-0.500000; v[1*3+2]=0.500000; 
    v[2*3+0]=-0.500000;v[2*3+1]= 0.500000;v[2*3+2] =0.500000; 
    v[3*3+0]=0.500000;v[3*3+1]=0.500000;v[3*3+2] =0.500000; 
    v[4*3+0]=-0.500000;v[4*3+1]= 0.500000;v[4*3+2]= -0.500000; 
    v[5*3+0]=0.500000;v[5*3+1]= 0.500000;v[5*3+2]= -0.500000; 
    v[6*3+0]=-0.500000;v[6*3+1]= -0.500000;v[6*3+2]= -0.500000; 
    v[7*3+0]=0.500000;v[7*3+1]= -0.500000;v[7*3+2]= -0.500000;
    f[0*4+0]=3; f[0*4+1]=3;f[0*4+2]=2;f[0*4+3]=1;
    f[1*4+0]=3; f[1*4+1]=1;f[1*4+2]=2;f[1*4+3]=0;
    f[2*4+0]=3; f[2*4+1]=5;f[2*4+2]=4;f[2*4+3]=3;
    f[3*4+0]=3; f[3*4+1]=3;f[3*4+2]=4;f[3*4+3]=2;
    f[4*4+0]=3; f[4*4+1]=7;f[4*4+2]=6;f[4*4+3]=5;
    f[5*4+0]=3; f[5*4+1]=5;f[5*4+2]=6;f[5*4+3]=4;
    f[6*4+0]=3; f[6*4+1]=1;f[6*4+2]=0;f[6*4+3]=7;
    f[7*4+0]=3; f[7*4+1]=7;f[7*4+2]=0;f[7*4+3]=6;
    f[8*4+0]=3; f[8*4+1]=5;f[8*4+2]=3;f[8*4+3]=7;
    f[9*4+0]=3; f[9*4+1]=7;f[9*4+2]=3;f[9*4+3]=1;
    f[10*4+0]=3; f[10*4+1]=2;f[10*4+2]=4;f[10*4+3]=0;
    f[11*4+0]=3;f[11*4+1]=0;f[11*4+2]=4;f[11*4+3]=6;
    
    for(int i=0;i<12;i++)
    {
        texcoords[i*7]=3;
    
    }
   /* texcoords[0]=3;
    texcoords[1]=1.0;texcoords[2]=0.0;
    texcoords[3]=0.0;texcoords[4]=0.0;
    texcoords[5]=0.0;texcoords[6]=1.0;*/
    texcoords[7]=3;
    texcoords[8]=1.0;texcoords[9]=0.0;
    texcoords[10]=0.0,texcoords[11]=1.0;
    texcoords[12]=1.0;texcoords[13]=1.0;
    mf->Data=v;
    mf->Data_index=f;
    mf->Data_rows=8;
    mf->Data_index_rows=12;
    char texture[]="Texture";
    n=mw.create_something(&mw,texture);
    ms=(Mesh_viewer_something*)(n->value);
    free_node(n);
    Mesh_viewer_texture*mt=(Mesh_viewer_texture*)(ms->evolution);
    mf->texture=ms;
    mt->image_file=(char*)malloc(sizeof(char)*20);
    strcpy(mt->image_file,"linyueru.jpg");
    mt->each_face_texture_coord=texcoords;
    char camera[]="Camera";
    n=Mesh_viewer_world_create_something(&mw,camera);
    ms=(Mesh_viewer_something*)(n->value);
    Mesh_viewer_camera* mc=(Mesh_viewer_camera*)(ms->evolution);
    mc->is_using=1;
    Matrix4x4* p=Projection(M_PI/3.0f,(float)(mw.g_info->resolution[0])/(float)(mw.g_info->resolution[1]),0.5f,200.0f);
    Matrix4x4_copy_data_float(mc->Proj,p);
    Matrix4x4_free(p); 
    free_node(n);
    test_intera(&mw);
    Mesh_viewer_world_printself(&mw);
    printf("GLFW_REPEAT:%d,GLFW_MOD_CONTROL:%d,GLFW_MOD_SHIFT:%d  GLFW_MOD_ALT:%d GLFW_MOD_SUPER:%d\n",GLFW_REPEAT,GLFW_MOD_CONTROL,GLFW_MOD_SHIFT,GLFW_MOD_ALT,GLFW_MOD_SUPER); 
    Mesh_viewer_opengl_Interpreter moi;
    Mesh_viewer_opengl_Interpreter_init(&moi);
    moi.world=&mw;
    moi.routine_show(&moi);
  // moi.render(&moi);

}

