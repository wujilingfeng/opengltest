
#ifndef MESH_VIEWER
#define MESH_VIEWER
#include "glfw_callback.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>



#ifdef __cplusplus
extern "C" {
#endif
void init_uniform(GLuint,Mesh_viewer_world*);
void set_uniform(GLuint,Mesh_viewer_world*);
void display_setting();
void show(Mesh_viewer_world*);
void prepare_mesh_viewer_world_data(Mesh_viewer_world*);
void add_texture(int,char*);
void draw_elements(Mesh_viewer_world*);
void draw_elements(Mesh_viewer_world* mw)
{
    char names[]="faces";
    Node* names_id=Mesh_viewer_world_find_species(mw,names);

    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(names_id->value)));

    if(iter!=mw->species2somethings.end())
    {
        for(auto iter1=(iter->second)->begin();iter1!=(iter->second)->end();iter1++)
        {
        
            Mesh_viewer_something *ms=iter1->second;
            Mesh_viewer_faces *mf=(Mesh_viewer_faces*)(ms->evolution);
            int v_size=0,temp_i=0;
            for(int i=0;i<mf->Data_index_rows;i++)
            {

                int j=mf->Data_index[temp_i];
                v_size+=(j-2)*3;
                temp_i+=(j+1);
            }
            glBindVertexArray(mf->VAO);
            
            glDrawArrays(GL_TRIANGLES,0,v_size); 
        }
    
    
    
    }



}
void add_texture(int gl_tex_num,char*image_file)
{
    GLuint* textures=(GLuint*)malloc(sizeof(GLuint)*2);
    glGenTextures(2,textures);
    ImageInfo image;
    image.data=stbi_load(image_file,&image.width,&image.height,&image.n,0);
/*    for(int i=0;i<18;i++)
    {
        printf("%u  ",image.data[i]);
    }
    if(image.data)
    {
        printf("width %d height %d\r\n",image.width,image.height);
    }
    */

    _Texture_(&image,textures[0]);
    stbi_image_free(image.data);
//先把纹理绑定一个纹理单元GL_TEXTURE0(纹理位置)
    glActiveTexture(gl_tex_num);

    glBindTexture(GL_TEXTURE_2D,textures[0]);




}

void prepare_mesh_viewer_world_data(Mesh_viewer_world*mw)
{
    char names[]="faces";
    Node* names_id=Mesh_viewer_world_find_species(mw,names);
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(names_id->value)));
    if(iter!=mw->species2somethings.end())
    {
        for(auto iter1=(iter->second)->begin();iter1!=(iter->second)->end();iter1++)
        {
            Mesh_viewer_something *ms=iter1->second;
            Mesh_viewer_faces *mf=(Mesh_viewer_faces*)(ms->evolution);
            glGenVertexArrays(1,&(mf->VAO));
            mf->Buffers=(GLuint*)malloc(sizeof(GLuint));
            if(mf->Data_index==0)
            {
                continue;
            }
            int v_size=0,temp_i=0;
            for(int i=0;i<mf->Data_index_rows;i++)
            {

                int j=mf->Data_index[temp_i];
                v_size+=(j-2)*3;
                temp_i+=(j+1);
            
            
            }
            GLfloat *vertices=(GLfloat*)malloc(sizeof(GLfloat)*v_size*3);
            GLfloat* colors=(GLfloat*)malloc(sizeof(GLfloat)*v_size*3);
            temp_i=0;v_size=0;
            for(int i=0;i<mf->Data_index_rows;i++)
            {
                int j=mf->Data_index[temp_i];
                for(int l=0;l<(j-2);l++)
                {
                    int k;
                    k=mf->Data_index[temp_i+1];
                    vertices[v_size*3+0]=mf->Data[k*3+0];vertices[v_size*3+1]=mf->Data[k*3+1];vertices[v_size*3+2]=mf->Data[k*3+2];
                    v_size++;
                    k=mf->Data_index[temp_i+1+l+1];

                    vertices[v_size*3+0]=mf->Data[k*3+0];vertices[v_size*3+1]=mf->Data[k*3+1];vertices[v_size*3+2]=mf->Data[k*3+2];

                    v_size++;
                    k=mf->Data_index[temp_i+1+l+2];

                    vertices[v_size*3+0]=mf->Data[k*3+0];vertices[v_size*3+1]=mf->Data[k*3+1];vertices[v_size*3+2]=mf->Data[k*3+2];

                    v_size++;
                    
                
                }
                temp_i+=(j+1);
                
            
            }
           
            glBindVertexArray(mf->VAO);
            glCreateBuffers(1,mf->Buffers);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[0]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*3,vertices,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[0]);
            glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
            glEnableVertexAttribArray( 0 );
            glBindVertexArray(0);

            
        
            
            free(vertices);
            free(colors);
        
        }
    
    
    }
    free_node_value(names_id);
    free_node(names_id);
   //printf("faces:%d\n",*((int*)(names_id->value)));



}
void init_uniform(GLuint program,Mesh_viewer_world* mw)
{
    //x,y正负1范围,
    //z/w也是
    Interactor_GlobalInfo* g_info=mw->g_info;
    g_info->resolution[0]=800;
    g_info->resolution[1]=600;
    //printf("pro:%lf\n",(float)())
    Matrix4x4* p=Projection(M_PI/2.0f,(float)(g_info->resolution[0])/(float)(g_info->resolution[1]),0.1f,200.0f);
    p->print_self(p); 
    glUniformMatrix4fv(glGetUniformLocation(program,"Proj"),1,GL_TRUE,(float*)(p->data));
    Matrix4x4 *p1=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(p1);
    float *data=(float*)(p1->data);
    //data[1*4+3]=0.3;
    glUniformMatrix4fv(glGetUniformLocation(program,"Camera_Matrix"),1,GL_TRUE,(float*)(p1->data));
    float a[2];
    a[0]=(float)(g_info->resolution[0]);
    a[1]=(float)(g_info->resolution[1]);
    glUniform2fv(glGetUniformLocation(program,"iResolution"),1,a);
//把像素着色器的纹理绑定纹理单元GL_TEXURE0（也就是纹理位置）
    glUniform1i(glGetUniformLocation(program,"ourTexture"),0);
	Matrix4x4_free(p);
    Matrix4x4_free(p1);
}
void set_uniform(GLuint program,Mesh_viewer_world* mw)
{  

    Interactor_GlobalInfo* g_info=mw->g_info;

    glUniform2f(glGetUniformLocation(program,"iResolution"),(float)g_info->resolution[0],(float)g_info->resolution[1]);

    Matrix4x4 *p1=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(p1);
    float *data=(float*)(p1->data);
    //data[1*4+3]=0.3;
    glUniformMatrix4fv(glGetUniformLocation(program,"Camera_Matrix"),1,GL_TRUE,(float*)(p1->data));

/*glUniform1i(glGetUniformLocation(program,"key_action"),(int)globalinfo.key_action);
    glUniform1i(glGetUniformLocation(program,"key"),(int)globalinfo.key);
    glUniform2f(glGetUniformLocation(program,"mousecoord"),(float)globalinfo.mouse_coord[0],(float)globalinfo.mouse_coord[1]);
    glUniform1i(glGetUniformLocation(program,"action"),(int)globalinfo.mouse_action);
    glUniform1i(glGetUniformLocation(program,"button"),(int)globalinfo.button);

    glUniform1f(glGetUniformLocation(program,"iTime"),globalinfo.run_time);
    glUniformMatrix4fv(glGetUniformLocation(program,"Matrix"),1,GL_TRUE,arc.get_data(&arc));
    */

}
void display_setting()
{
    glEnable(GL_DEPTH_TEST);
//以下两个语句成对使用
   // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//glClear(GL_COLOR_BUFFER_BIT);
//上面两个语句等同以下两个语句
	static const float black[]={0.2f,0.3f,0.3f,1.0f};
    glClearBufferfv(GL_COLOR,0,black);
   
	glClear(GL_DEPTH_BUFFER_BIT);


}
void show(Mesh_viewer_world* mw)
{
    printf("begin show\n");  
    
   glfwInit();
   //实践证明还是不指定版本号比较好
   // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(800,600,"learnopengl",NULL,NULL);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif
    if(window==NULL)
    {
	    glfwTerminate();
        printf("Failed to create GLFW window\r\n");
        return;

    }

   
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to load glad\n");
        return;
    }

    
    glfwSetWindowUserPointer(window,(void*)mw);
    mw->g_info->window=(void*)window; 
    mesh_viewer_set_callback(window);

    prepare_mesh_viewer_world_data(mw);
   
  	char mesh_vert[]="mesh.vert";
	char mesh_frag[]="mesh.frag";
    ShaderInfo shaders[]={
    { GL_VERTEX_SHADER, mesh_vert },
        { GL_FRAGMENT_SHADER, mesh_frag},
        { GL_NONE, NULL }   
    };
    
    _Shader_(shaders);
    GLuint program;
    program=_Program_(shaders);
       
    glUseProgram(program);//开启这个词更合适
    init_uniform(program,mw);
    char image_file[]="linyueru.jpg";
    add_texture(GL_TEXTURE0,image_file);
//*****************************************

    clock_t start,finish;
    start=clock();
   //set_callback(window);
   
   // init_uniform(program);
    while (!glfwWindowShouldClose(window))
    {
      
        
         finish=clock();
        //globalinfo.run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
        //set_uniform(program);
       // glUniform1f(glGetUniforLocation())
        display_setting();
        draw_elements(mw);
        //update_intera_information(window,g_callback_info->g_info);
                //draw_elements(program);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

}

#ifdef __cplusplus
}
#endif
#endif
