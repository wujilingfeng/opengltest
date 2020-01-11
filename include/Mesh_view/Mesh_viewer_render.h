#include "Mesh_viewer.h"
#ifndef MESH_VIEWER_RENDER
#define MESH_VIEWER_RENDER
#ifdef __cplusplus
extern "C"{
#endif
typedef struct render_struct{
GLuint VAO;
GLuint *Buffers;
GLuint faces_rows;

}render_struct;
void render_struct_init(render_struct*);
void render_prepare(render_struct*,Mesh_viewer_world*);
void render_draw(GLuint);
void render_struct_init(render_struct * rs){
rs->VAO=0;
rs->Buffers=0;
rs->faces_rows=0;

}

void render_draw(GLuint VAO)
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


}

void render_prepare(render_struct* rs,Mesh_viewer_world*mw)
{
    GLfloat*vertices=(GLfloat*)malloc(sizeof(GLfloat)*3*4);
    memset(vertices,0,sizeof(GLfloat)*3*4);
    vertices[0]=-1.0;vertices[1]=-1;
    vertices[1*3+0]=1.0;vertices[1*3+1]=-1.0;
    vertices[2*3+0]=1.0;vertices[2*3+1]=1.0;
    vertices[3*3+0]=-1.0;vertices[3*3+1]=1.0;
    GLuint index[6]={0,1,3,1,2,3};

    if(rs->Buffers!=0)
    {
        free(rs->Buffers);
        rs->Buffers=0;
    }
    rs->Buffers=(GLuint*)malloc(sizeof(GLuint));
    glGenVertexArrays(1,&(rs->VAO));
    glBindVertexArray(rs->VAO);

    glCreateBuffers(2,rs->Buffers);
    glBindBuffer(GL_ARRAY_BUFFER,rs->Buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*4,vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rs->Buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,rs->Buffers[0]);
    glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 ); 

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    test_add_array_to_shader(mw);
    Node* n_iter=(Node*)mw->prop;
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
    
void render(Mesh_viewer_world* mw)
{
    printf("begin show\n");  
    
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

    render_struct rs;
    render_struct_init(&rs);
    //GLuint VAO,*Buffers=(GLuint*)malloc(sizeof(GLuint));
    render_prepare(&rs,mw);

   
  	char mesh_vert[]="render.vert";
	char mesh_frag[]="render.frag";
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

    clock_t start,finish;
    start=clock();
    while (!glfwWindowShouldClose(window))
    {
      
        
        finish=clock();
      //  set_uniform(program,mw);
    

        mw->g_info->run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
        set_uniform(program,mw);
        //set_uniform(program);
       // glUniform1f(glGetUniforLocation())
        //display_setting();
        render_draw(rs.VAO);
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
