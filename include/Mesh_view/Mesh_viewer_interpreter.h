#ifndef MESH_VIEWER_OPENGL_INTERPRETER
#define MESH_VIEWER_OPENGL_INTERPRETER
#include "glfw_callback.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#ifdef __cplusplus
extern "C"
{
#endif


typedef struct Mesh_viewer_opengl_Interpreter
{

GLuint VAO;
GLuint* Buffers;
GLuint faces_len;
GLuint faces_vertices_len;
Node* node;
ShaderInfo *shaders;
GLuint program;

Mesh_viewer_world* world;
void *prop;
}Mesh_viewer_opengl_Interpreter;
void Mesh_viewer_opengl_Interpreter_init(Mesh_viewer_opengl_Interpreter*);

void init_uniform(Mesh_viewer_opengl_Interpreter*);
void test_add_array_to_shader(Mesh_viewer_opengl_Interpreter*);
void draw_elements(Mesh_viewer_opengl_Interpreter*);

void add_texture_to_shader(int*,char*);
void prepare_mesh_viewer_world_data(Mesh_viewer_opengl_Interpreter*);

void set_uniform(Mesh_viewer_opengl_Interpreter*);

void display_setting();

void routine_show(Mesh_viewer_opengl_Interpreter*);

void render_draw_elements(Mesh_viewer_opengl_Interpreter*);
void prepare_render_data(Mesh_viewer_opengl_Interpreter*);
void render(Mesh_viewer_opengl_Interpreter*);
void render(Mesh_viewer_opengl_Interpreter* moi)
{
    printf("begin show\n");  
   Mesh_viewer_world* mw=moi->world; 
   glfwInit();
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

  
    prepare_render_data(moi);

   
  	char mesh_vert[]="render.vert";
	char mesh_frag[]="render.frag";
    ShaderInfo shaders[]={
    { GL_VERTEX_SHADER, mesh_vert },
        { GL_FRAGMENT_SHADER, mesh_frag},
        { GL_NONE, NULL }   
    };
    moi->shaders=shaders;
    _Shader_(moi->shaders);
    moi->program=_Program_(moi->shaders);
       
    glUseProgram(moi->program);//开启这个词更合适
    init_uniform(moi);

    clock_t start,finish;
    start=clock();
    while (!glfwWindowShouldClose(window))
    {   
        finish=clock();
      //  set_uniform(program,mw);
    

        mw->g_info->run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
        set_uniform(moi);
        //set_uniform(program);
       // glUniform1f(glGetUniforLocation())
        //display_setting();
        render_draw_elements(moi);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

}
void prepare_render_data(Mesh_viewer_opengl_Interpreter*moi)
{
    GLfloat*vertices=(GLfloat*)malloc(sizeof(GLfloat)*3*4);
    memset(vertices,0,sizeof(GLfloat)*3*4);
    vertices[0]=-1.0;vertices[1]=-1;
    vertices[1*3+0]=1.0;vertices[1*3+1]=-1.0;
    vertices[2*3+0]=1.0;vertices[2*3+1]=1.0;
    vertices[3*3+0]=-1.0;vertices[3*3+1]=1.0;
    GLuint index[6]={0,1,3,1,2,3};

    if(moi->Buffers!=0)
    {
        free(moi->Buffers);
        moi->Buffers=0;
    }
    moi->Buffers=(GLuint*)malloc(sizeof(GLuint));
    glGenVertexArrays(1,&(moi->VAO));
    glBindVertexArray(moi->VAO);

    glCreateBuffers(2,moi->Buffers);
    glBindBuffer(GL_ARRAY_BUFFER,moi->Buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*4,vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,moi->Buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,moi->Buffers[0]);
    glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 ); 

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    test_add_array_to_shader(moi);
	//printf("test:%d %d\n",rs->faces_len,rs->faces_vertices_len);
    Node* n_iter=moi->node;
   n_iter=node_reverse(n_iter);
    int num_i=0;
    while(n_iter!=0)
    {
        glActiveTexture(GL_TEXTURE1+num_i);
        glBindTexture(GL_TEXTURE_2D,*((int*)(n_iter->value)));
        n_iter=(Node*)(n_iter->Prev);
        num_i++;
    
    }
    free(vertices);
}
void render_draw_elements(Mesh_viewer_opengl_Interpreter* moi)
{
    glBindVertexArray(moi->VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


}
void routine_show(Mesh_viewer_opengl_Interpreter* moi)
{
   Mesh_viewer_world* mw=moi->world; 
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

    //prepare_rendering_data(mw);
    prepare_mesh_viewer_world_data(moi);
  
  	/*char mesh_vert[]="mesh.vert";
	char mesh_frag[]="mesh.frag";
    ShaderInfo shaders[]={
    { GL_VERTEX_SHADER, mesh_vert },
        { GL_FRAGMENT_SHADER, mesh_frag},
        { GL_NONE, NULL }   
    };*/
    
    _Shader_(moi->shaders);
    moi->program=_Program_(moi->shaders);
       
    glUseProgram(moi->program);//开启这个词更合适
    init_uniform(moi);
    //char image_file[]="linyueru.jpg";
    //add_texture_to_shader(GL_TEXTURE0,image_file);
//*****************************************

    clock_t start,finish;
    start=clock();
   //set_callback(window);
   
   // init_uniform(program);
    while (!glfwWindowShouldClose(window))
    {
      
        
        finish=clock();
        mw->g_info->run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
        set_uniform(moi);
       // glUniform1f(glGetUniforLocation())
        display_setting();
        draw_elements(moi);
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

void set_uniform(Mesh_viewer_opengl_Interpreter*moi)
{  
    Mesh_viewer_world* mw=moi->world;
    GLuint program=moi->program;
    Interactor_GlobalInfo* g_info=mw->g_info;
    glUniform2f(glGetUniformLocation(program,"iMouse"),(float)g_info->mouse_coord[0],(float)g_info->mouse_coord[1]);
    glUniform2f(glGetUniformLocation(program,"iResolution"),(float)g_info->resolution[0],(float)g_info->resolution[1]);
    glUniform1f(glGetUniformLocation(program,"iTime"),g_info->run_time);
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

    if(mc!=0)
    {
        float* data=(float*)(mc->matrix_inverse->data);    
        glUniformMatrix4fv(glGetUniformLocation(program,"Camera_Matrix"),1,GL_TRUE,data);

    }
    free_node_value(id);
    free_node(id);

/*glUniform1i(glGetUniformLocation(program,"key_action"),(int)globalinfo.key_action);
    glUniform1i(glGetUniformLocation(program,"key"),(int)globalinfo.key);
    glUniform2f(glGetUniformLocation(program,"mousecoord"),(float)globalinfo.mouse_coord[0],(float)globalinfo.mouse_coord[1]);
    glUniform1i(glGetUniformLocation(program,"action"),(int)globalinfo.mouse_action);
    glUniform1i(glGetUniformLocation(program,"button"),(int)globalinfo.button);

    glUniform1f(glGetUniformLocation(program,"iTime"),globalinfo.run_time);
    glUniformMatrix4fv(glGetUniformLocation(program,"Matrix"),1,GL_TRUE,arc.get_data(&arc));
    */

}

void prepare_mesh_viewer_world_data(Mesh_viewer_opengl_Interpreter*moi)
{

	Mesh_viewer_world* mw=moi->world;
    char names[]="faces";
    Node* names_id=Mesh_viewer_world_find_species(mw,names);
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(names_id->value)));
    if(iter!=mw->species2somethings.end())
    {
        for(auto iter1=(iter->second)->begin();iter1!=(iter->second)->end();iter1++)
        {
            Mesh_viewer_something *ms=iter1->second;
            Mesh_viewer_faces *mf=(Mesh_viewer_faces*)(ms->evolution);
            mf->Buffers=(GLuint*)malloc(sizeof(GLuint));
            if(ms->disappear==1||mf->Data_index_rows==0)
            {continue;}
            //vertex array
            int v_size=0,temp_i=0;
            for(int i=0;i<mf->Data_index_rows;i++)
            {

                int j=mf->Data_index[temp_i];
                v_size+=(j-2)*3;
                temp_i+=(j+1); 
            }
            if(v_size==0)
            {
                continue;
            }
            GLfloat *vertices=(GLfloat*)malloc(sizeof(GLfloat)*v_size*3);
            GLfloat* colors=(GLfloat*)malloc(sizeof(GLfloat)*v_size*3);
            GLfloat* texcoords=(GLfloat*)malloc(sizeof(GLfloat)*v_size*2);
            memset(texcoords,0,sizeof(GLfloat)*v_size*2);
            memset(colors,0,sizeof(GLfloat)*v_size*3);
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

            //color
            if(mf->color!=0)
            {
                temp_i=0;v_size=0;
                for(int i=0;i<mf->Data_index_rows;i++)
                {
                    int j=mf->Data_index[temp_i];
                    for(int l=0;l<(j-2)*3;l++)
                    {
                    
                        for(int k=0;k<3;k++)
                        {
                    
                            colors[v_size*3+k]=mf->color[i*3+k];
                        }
                        v_size++;
                    }
                    temp_i+=(j+1);                   
                } 
            }

            //texture
            if(mf->texture->image_file!=0&&mf->texture->each_face_texture_coord!=0)
            {
                //printf("%s\n",mf->texture->image_file);
                int * value_t=(int*)malloc(sizeof(int));

                add_texture_to_shader(value_t,mf->texture->image_file); 
                moi->node=node_overlying(moi->node,(void*)value_t);
                Mesh_viewer_texture* texture=mf->texture;
                temp_i=0;v_size=0;
                for(int i=0;i<mf->Data_index_rows;i++)
                {
                    int j=texture->each_face_texture_coord[temp_i];
                    for(int l=0;l<(j-2);l++)
                    {
                        texcoords[v_size*2+0]=texture->each_face_texture_coord[temp_i+1+0];
                        texcoords[v_size*2+1]=texture->each_face_texture_coord[temp_i+1+1];
                        
                        v_size++;
                        texcoords[v_size*2+0]=texture->each_face_texture_coord[temp_i+1+2*(l+1)+0];
                        texcoords[v_size*2+1]=texture->each_face_texture_coord[temp_i+1+2*(l+1)+1];
                        v_size++;
                        texcoords[v_size*2+0]=texture->each_face_texture_coord[temp_i+1+2*(l+2)+0];
                        texcoords[v_size*2+1]=texture->each_face_texture_coord[temp_i+1+2*(l+2)+1];
                        v_size++;
                    }
                    temp_i+=(j*2+1);                   
                } 

            }

            glDeleteBuffers(1,mf->Buffers);
            glDeleteVertexArrays(1,&(mf->VAO));
            glGenVertexArrays(1,&(mf->VAO));
            glBindVertexArray(mf->VAO);
            glCreateBuffers(3,mf->Buffers);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[0]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*3,vertices,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[1]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*3,colors,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[2]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*2,texcoords,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[0]);
            glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
            
            glEnableVertexAttribArray( 0 );
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[1]);
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[2]);
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
 
            free(vertices);
            free(colors);
        
        }
    
    
    }
    test_add_array_to_shader(moi);

	Node* n_iter=moi->node;
    n_iter=node_reverse(n_iter);
    int num_i=0;
    while(n_iter!=0)
    {
        glActiveTexture(GL_TEXTURE0+num_i);
        glBindTexture(GL_TEXTURE_2D,*((int*)(n_iter->value)));
        n_iter=(Node*)(n_iter->Prev);
        num_i++;
    
    }
    free_node_value(moi->node);
    free_node(moi->node);
    moi->node=0;
    free_node_value(names_id);
    free_node(names_id);
   //printf("faces:%d\n",*((int*)(names_id->value)));

}


void add_texture_to_shader(int *gl_tex_num,char*image_file)
{
    GLuint* textures=(GLuint*)malloc(sizeof(GLuint)*1);
    glGenTextures(1,textures);
   
    ImageInfo image;
    image.data=(void*)stbi_load(image_file,&image.width,&image.height,&image.n,0);
/*    for(int i=0;i<18;i++)
    {
        printf("%u  ",image.data[i]);
    }*/
    if(!image.data)
    {
        printf("cant add texture\n");
    }
    

    _Texture_(&image,textures[0]);
    stbi_image_free(image.data);
    *gl_tex_num=textures[0];
//先把纹理绑定一个纹理单元GL_TEXTURE0(纹理位置)
    //glActiveTexture(gl_tex_num);
    //glBindTexture(GL_TEXTURE_2D,textures[0]);
}

void draw_elements(Mesh_viewer_opengl_Interpreter* moi)
{
    Mesh_viewer_world* mw=moi->world;
    char names[]="faces";
    Node* names_id=Mesh_viewer_world_find_species(mw,names);

    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(names_id->value)));

    if(iter!=mw->species2somethings.end())
    {
        for(auto iter1=(iter->second)->begin();iter1!=(iter->second)->end();iter1++)
        {
        
            Mesh_viewer_something *ms=iter1->second;
            Mesh_viewer_faces *mf=(Mesh_viewer_faces*)(ms->evolution);
            if(ms->disappear==1||mf->Data_index_rows==0||mf->VAO==0||mf->Buffers==0)
            {continue;}
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
    free_node_value(names_id);
    free_node(names_id);


}


void test_add_array_to_shader(Mesh_viewer_opengl_Interpreter* moi)
{
    Mesh_viewer_world* mw=moi->world;
    char names[]="faces";
    GLfloat* vertices=0,*index=0;
    int len_rows=0,len_index_rows=0,len_index=0;
    Node* names_id=Mesh_viewer_world_find_species(mw,names);
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(names_id->value)));
    if(iter!=mw->species2somethings.end())
    {
        for(auto iter1=(iter->second)->begin();iter1!=(iter->second)->end();iter1++)
        {
            Mesh_viewer_something *ms=iter1->second;
            Mesh_viewer_faces *mf=(Mesh_viewer_faces*)(ms->evolution);
            len_rows+=mf->Data_rows;
            len_index_rows+=mf->Data_index_rows;
            int temp_i=0,j=0;
            for(int i=0;i<mf->Data_index_rows;i++)
            {
                j=mf->Data_index[temp_i];
                temp_i+=(j+1);
                
            }
            len_index+=temp_i;
        }
    
    }
    if(len_index==0)
    {
        free_node_value(names_id);
        free_node(names_id);
        return;
    }
    ImageInfo image,image1;
    image.height=(len_rows/1000+1);
    image.width=1000;
    image1.height=(len_index/1000+1);
    image1.width=1000;
    vertices=(GLfloat*)malloc(sizeof(GLfloat)*image.width*image.height*3);
    memset(vertices,0,sizeof(GLfloat)*image.width*image.height);
    index=(GLfloat*)malloc(sizeof(GLfloat)*image1.width*image1.height);
    memset(index,0,sizeof(GLfloat)*image1.width*image1.height);
    int temp_i=0,temp_j=0,temp_k=0;
    if(iter!=mw->species2somethings.end())
    {
        for(auto iter1=(iter->second)->begin();iter1!=(iter->second)->end();iter1++)
        {
            Mesh_viewer_something *ms=iter1->second;
            Mesh_viewer_faces *mf=(Mesh_viewer_faces*)(ms->evolution);
            temp_i=0;
            for(int i=0;i<mf->Data_index_rows;i++)
            {
                int k=mf->Data_index[temp_i];
                index[temp_k]=mf->Data_index[temp_i];
                temp_k++;
                for(int j=0;j<k;j++)
                {

                    index[temp_k]=mf->Data_index[temp_i+1+j]+temp_j;
                    temp_k++;
                
                }
                temp_i+=(k+1);
                
            }
            for(int i=0;i<mf->Data_rows;i++)
            {
                for(int j=0;j<3;j++)
                {
                    
                    vertices[temp_j*3+j]=mf->Data[i*3+j];
                }
                temp_j++;
            }
           
            
        } 
    }
    image.data=(void*)vertices;
    image1.data=(void*)index;
    for(int i=0;i<len_rows;i++)
    {
        for(int j=0;j<3;j++)
        {
           // vertices[i*3+j]=i*3+j;
            printf("%lf ",vertices[i*3+j]);
        }
        printf("\n");
    }
    temp_i=0;
    for(int i=0;i<len_index_rows;i++)
    {
        
       int k=index[temp_i]; 
        for(int j=0;j<k;j++)
        {
            printf("%lf  ",index[temp_i+1+j]);
        
        }

        temp_i+=(k+1);
        printf("\n");
    }
	
	
	moi->faces_len=len_index;
	moi->faces_vertices_len=len_rows;
    GLuint* textures=(GLuint*)malloc(sizeof(GLuint)*2);
    glGenTextures(2,textures);
    _Texture_Array_GL_FLOAT(&image,textures[0]);
    _Texture_Array_GL_R32UI(&image1,textures[1]);
    int *value=(int*)malloc(sizeof(int));
    *value=textures[0];
    moi->node=node_overlying(moi->node,(void*)value);
    value=(int*)malloc(sizeof(int));
    *value=textures[1]; 
    moi->node=node_overlying(moi->node,(void*)value);
    free(vertices);
    free(index);
    /*glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,textures[0]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,textures[1]);
    */
    free_node_value(names_id);
    free_node(names_id);

}

void init_uniform(Mesh_viewer_opengl_Interpreter* moi)
{
    //x,y正负1范围,
    //z/w也是
    Mesh_viewer_world* mw=moi->world;
    GLuint program=moi->program;
    Interactor_GlobalInfo* g_info=mw->g_info;
    
    //printf("pro:%lf\n",(float)())
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

    if(mc!=0)
    {
        float* data=(float*)(mc->matrix_inverse->data);    
        glUniformMatrix4fv(glGetUniformLocation(program,"Camera_Matrix"),1,GL_TRUE,data);

        glUniformMatrix4fv(glGetUniformLocation(program,"Proj"),1,GL_TRUE,(float*)(mc->Proj->data));
         data=(float*)(mc->Proj->data);
        //printf("prj:%lf\n",-1/(1/data[2*4+3]+data[2*4+2]/data[2*4+3]));
    }
    free_node_value(id);
    free_node(id);
     GLfloat a[2];
    a[0]=(GLfloat)(g_info->resolution[0]);
    a[1]=(GLfloat)(g_info->resolution[1]);
    //printf("resolution:%lf %lf\n",a[0],a[1]);
    glUniform2fv(glGetUniformLocation(program,"iResolution"),1,a);
//把像素着色器的纹理绑定纹理单元GL_TEXURE0（也就是纹理位置）
    glUniform1i(glGetUniformLocation(program,"ourTexture"),0);
    glUniform1i(glGetUniformLocation(program,"Faces_Vertices"),1);
    glUniform1i(glGetUniformLocation(program,"Faces_Index"),2);
	
	if(mw->prop!=0)
	{
        //printf("")
        glUniform1f(glGetUniformLocation(program,"Faces_len"),(float)(moi->faces_len));
        glUniform1f(glGetUniformLocation(program,"Faces_Vertices_rows"),(float)(moi->faces_vertices_len));
        //glUniform1f(glGetUniformLocation(program,""))
    }
}

void Mesh_viewer_opengl_Interpreter_init(Mesh_viewer_opengl_Interpreter*moi)
{
    moi->program=-1;
 	/*char mesh_vert[]="mesh.vert";
	char mesh_frag[]="mesh.frag";
    ShaderInfo shaders[]={
    { GL_VERTEX_SHADER, mesh_vert },
        { GL_FRAGMENT_SHADER, mesh_frag},
        { GL_NONE, NULL }   
    };*/
    char mesh_vert[]="mesh.vert";
    char mesh_frag[]="mesh.frag";
    char* p_v=(char*)malloc(sizeof(char)*10);
    strcpy(p_v,mesh_vert);
    char* p_f=(char*)malloc(sizeof(char)*10);
    strcpy(p_f,mesh_frag);
    moi->shaders=(ShaderInfo*)malloc(sizeof(ShaderInfo)*3);
    moi->shaders[0].type=GL_VERTEX_SHADER;
    moi->shaders[0].filename=p_v;
    moi->shaders[1].type=GL_FRAGMENT_SHADER;
    moi->shaders[1].filename=p_f;
    moi->shaders[2].type=GL_NONE;
    moi->shaders[2].filename=0;

    moi->VAO=0;
    moi->Buffers=0;
    moi->faces_len=0;
    moi->faces_vertices_len=0;
    moi->node=0;

    moi->world=0;
    moi->prop=0;


}

#ifdef __cplusplus
}
#endif
#endif
