//
//#include<myopengl.h>
#undef OpenglAlg

#include "glfw_callback.h"
//#include<tool/tools_node.h>
#include<time.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

#include<iostream>
//#include<Algorithm.h>
//GLuint *VAOs=(GLuint*)malloc(sizeof(GLuint)); //*textures=(GLuint*)malloc(sizeof(GLuint)*2);
void set_callback(GLFWwindow* window)
{
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetCursorPosCallback(window,cursor_position_callback);
    glfwSetKeyCallback(window,key_callback); 
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwGetFramebufferSize(window,&globalinfo.resolution[0],&globalinfo.resolution[1]);
    glfwSetScrollCallback(window,scroll_callback);
}
void init_uniform(GLuint program)
{//vec3 iR=vec3(800,600,0);
//glUniform1i(glGetUniformLocation(program,"iResolution"),iR);
    //glm::
    //x,y正负1范围,
    //z/w也是
    Eigen::MatrixXf p=Projection(M_PI/6.0f,(float)globalinfo.resolution[0]/(float)globalinfo.resolution[1],0.1f,200.0f);
     /*Eigen::MatrixXi *F=(Eigen::MatrixXi*)(m_v_data.F_F->value);
     int F_data[F->rows()*3];
     for(int i=0;i<F->rows();i++)
     {
        for(int j=0;j<3;j++)
        {
            F_data[i*3+j]=F->coeff(i,j);
        
        }
     
     }
    glUniform1iv(glGetUniformLocation(program,"F"),F->rows()*3,F_data);*/
   //printf("test: %d\n",F->data()[3]); 

/*glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)globalinfo.resolution[0]/(float)globalinfo.resolution[1], 0.2f, 100.0f);
for(int i=0;i<4;i++)
{
for(int j=0)
}*/
    glUniformMatrix4fv(glGetUniformLocation(program,"Proj"),1,GL_FALSE,p.data());
    glUniformMatrix4fv(glGetUniformLocation(program,"Matrix"),1,GL_TRUE,arc.get_data(&arc));
Eigen::VectorXf a(2);
    a.coeffRef(0)=(float)globalinfo.resolution[0];
    a.coeffRef(1)=(float)globalinfo.resolution[1];
    glUniform2fv(glGetUniformLocation(program,"iResolution"),1,(float*)a.data());
//把像素着色器的纹理绑定纹理单元GL_TEXURE0
	glUniform1i(glGetUniformLocation(program,"ourTexture"),0);
    if((m_v_data.F_V->value)!=NULL)
    {
    
    glUniform1i(glGetUniformLocation(program,"Vsize"),((Eigen::MatrixXf*)(m_v_data.F_V->value))->rows());
    }

}
void set_uniform(GLuint program)
{  



    glUniform1i(glGetUniformLocation(program,"key_action"),(int)globalinfo.key_action);
    glUniform1i(glGetUniformLocation(program,"key"),(int)globalinfo.key);
    glUniform2f(glGetUniformLocation(program,"mousecoord"),(float)globalinfo.mouse_coord[0],(float)globalinfo.mouse_coord[1]);
    glUniform1i(glGetUniformLocation(program,"action"),(int)globalinfo.mouse_action);
    glUniform1i(glGetUniformLocation(program,"button"),(int)globalinfo.button);


    glUniform2f(glGetUniformLocation(program,"iResolution"),(float)globalinfo.resolution[0],(float)globalinfo.resolution[1]);

    glUniform1f(glGetUniformLocation(program,"iTime"),globalinfo.run_time);
    glUniformMatrix4fv(glGetUniformLocation(program,"Matrix"),1,GL_TRUE,arc.get_data(&arc));
    /*unsigned char *readpixelcolor=(unsigned char*)malloc(sizeof(unsigned char)*36);
    float y;
    y=(float)globalinfo.resolution[0];*/

}
void prepare_edge_data()
{
    int size=node_size(m_v_data.F_V),size1=node_size(m_v_data.E_V);
     Node* E_V=m_v_data.E_V,*E_E=m_v_data.E_E;


    for(int node_i=size;node_i<size+size1;node_i++)
    {
        Eigen::MatrixXf *V=(Eigen::MatrixXf*)(E_V->value);
        Eigen::MatrixXi *E=(Eigen::MatrixXi*)(E_E->value);
        if(V->rows()==0)
        {
            E_V=(Node*)E_V->Next;E_E=(Node*)E_E->Next;

            continue;
        }
        GLfloat vertices[V->rows()][3];
        unsigned int indices[E->rows()][2];
        for(int i=0;i<V->rows();i++)
        {
            for(int j=0;j<3;j++)
            {
                vertices[i][j]=V->coeff(i,j);
            }
        }
        for(int i=0;i<E->rows();i++)
        {
            for(int j=0;j<2;j++)
            {
                indices[i][j]=E->coeff(i,j);
            }
        }
    
	    glBindVertexArray(m_v_data.VAOs[node_i]);
    
	    m_v_data.Buffers[node_i]=(GLuint*)malloc(sizeof(GLuint));
	    glCreateBuffers(2,m_v_data.Buffers[node_i]);
        GLuint*Buffers =m_v_data.Buffers[node_i];
	    glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
    //printf("sizeof vertices: %d\n",sizeof(vertices));
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Buffers[1]);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	    glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
	    glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
        glEnableVertexAttribArray( 0 );
	 //glVertexAttribPointer(1,2,)
	    glBindBuffer(GL_ARRAY_BUFFER,0);
	    glBindVertexArray(0);
        E_V=(Node*)E_V->Next;E_E=(Node*)E_E->Next;

    }
    printf("size+size1:%d\n",size+size1);
        glBindVertexArray(m_v_data.VAOs[size+size1]);
        m_v_data.Buffers[size+size1]=(GLuint*)malloc(sizeof(GLuint));
        glCreateBuffers(1,m_v_data.Buffers[size+size1]);
        GLuint* Buffers=m_v_data.Buffers[size+size1];

        glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
        glBufferData(GL_ARRAY_BUFFER,100*2*3*sizeof(GLfloat),0,GL_STATIC_DRAW);
       // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Buffers[1]);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
        glEnableVertexAttribArray( 0 );
	 //glVertexAttribPointer(1,2,)
	    glBindBuffer(GL_ARRAY_BUFFER,0);
	    glBindVertexArray(0);
 

 }

void prepare_mesh_data()
{
	/*GLfloat vertices[6][2]={
		{ -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
        {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2	
	};*/
/*	GLfloat vertices[4][3]={{ -0.7f, -0.7f,-1.0f}, {  0.7f, -0.7f,-1.0f }, { -0.7f,  0.7f,-1.0f},{0.7f,0.7f,-1.0f}};*/
    int size=node_size(m_v_data.F_V);
    printf("size:%d\n",size);
    Node* F_V=m_v_data.F_V,*F_F=m_v_data.F_F;
    for(int node_i=0;node_i<size;node_i++)
    {
        Eigen::MatrixXf *V=(Eigen::MatrixXf*)(F_V->value);
        Eigen::MatrixXi *F=(Eigen::MatrixXi*)(F_F->value);
        if(F->rows()==0)
        {   F_V=(Node*)F_V->Next;F_F=(Node*)F_F->Next;
            printf("F rows==0\n");
            continue;
        }

        GLfloat vertices[F->rows()*3][3],normal[F->rows()*3][3];
        m_v_data.F_color_size[node_i]=sizeof(GLfloat)*F->rows()*3*3;

        GLfloat* color=(GLfloat*)malloc(m_v_data.F_color_size[node_i]);
        m_v_data.F_color[node_i]=color;
    
        for(int i=0;i<F->rows();i++)
        {
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<3;k++)
                {     
                    vertices[i*3+j][k]=V->coeff(F->coeff(i,j),k);
                    color[i*9+j*3+k]=0.7;
            
                }
    
            }
        }
     
    
        float nor[3][3];
        for(int i=0;i<F->rows();i++)
        {
            for(int j=0;j<3;j++)
            {
                nor[0][j]=V->coeff(F->coeff(i,1),j)-V->coeff(F->coeff(i,0),j);
                nor[1][j]=V->coeff(F->coeff(i,2),j)-V->coeff(F->coeff(i,0),j);
            }

        
                nor[2][0]=nor[0][1]*nor[1][2]-nor[0][2]*nor[1][1];
                nor[2][1]=-nor[0][0]*nor[1][2]+nor[1][0]*nor[0][2];
                nor[2][2]=nor[0][0]*nor[1][1]-nor[1][0]*nor[0][1];
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<3;k++)
                {
            
                    normal[3*i+j][k]+=nor[2][k];
            
                }
        
            }
        
    
        }

        unsigned int indices[F->rows()][3];
        for(int i=0;i<F->rows();i++)
        {
            for(int j=0;j<=F->cols();j++)
            {
                indices[i][j]=F->coeff(i,j);
        
            } 
        }
   
	    float texcoords[]={0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.0f};
        
    
	    glBindVertexArray(m_v_data.VAOs[node_i]);
        m_v_data.Buffers[node_i]=(GLuint*)malloc(sizeof(GLuint));  
	    glCreateBuffers(5,m_v_data.Buffers[node_i]);
        GLuint *Buffers=m_v_data.Buffers[node_i];
	    glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
    //printf("sizeof vertices: %d\n",sizeof(vertices));
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Buffers[1]);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	
        glBindBuffer(GL_ARRAY_BUFFER,Buffers[2]);
	    glBufferData(GL_ARRAY_BUFFER,sizeof(texcoords),texcoords,GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,Buffers[3]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(normal),normal,GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,Buffers[4]);
        glBufferData(GL_ARRAY_BUFFER,m_v_data.F_color_size[0],color,GL_STATIC_DRAW);
 

	    glBindBuffer(GL_ARRAY_BUFFER,Buffers[0]);
	    glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
        glEnableVertexAttribArray( 0 );
    
        glBindBuffer(GL_ARRAY_BUFFER,Buffers[4]);
        glVertexAttribPointer( 1, 3, GL_FLOAT,GL_FALSE,0,0);
        glEnableVertexAttribArray(1);


        glBindBuffer(GL_ARRAY_BUFFER,Buffers[2]);
	    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);

	    glEnableVertexAttribArray(2);
    
        glBindBuffer(GL_ARRAY_BUFFER,Buffers[3]);
        glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,0,0);
        glEnableVertexAttribArray(3);
    
	    glBindBuffer(GL_ARRAY_BUFFER,0);
	    glBindVertexArray(0);
        F_V=(Node*)F_V->Next;F_F=(Node*)F_F->Next;
    }

}
void init_texture()
{
	GLuint* textures=(GLuint*)malloc(sizeof(GLuint)*2);
    glGenTextures(2,textures);
    ImageInfo image;
    image.data=stbi_load("linyueru.jpg",&image.width,&image.height,&image.n,0);
    printf("%d",image.n);
/*if(image.data)
{
printf("width %d height %d\r\n",image.width,image.height);
}
*/
//printf("hello%dhello",(int)image.data[image.width*image.height*image.n+1]);
    _Texture_(image,textures[0]);
    stbi_image_free(image.data);
//先把纹理绑定一个纹理单元GL_TEXTURE0
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D,textures[0]);
//glUniform1i(glGetUniformLocation())

}
void draw_elements(GLuint program)
{

    glUniform1f(glGetUniformLocation(program,"Mesh_or_Edge"),0);
    int size=node_size(m_v_data.F_F);
    for(int node_i=0;node_i<size;node_i++)
    {
   
        glBindVertexArray(m_v_data.VAOs[node_i]);
    //glBindBuffer(GL_ARRAY_BUFFER,m_v_data.Buffers[4]);
    //glBufferData(GL_ARRAY_BUFFER,m_v_data.F_color_size,0,GL_STATIC_DRAW);
    //GLfloat* color=(GLfloat*)m_v_data.F_color->value;
    //for(int i=0;i<m_v_data.F_color_size;i++)
    //{
      //  color[i]=i/2000.0;
    //}
//    glBufferSubData(GL_ARRAY_BUFFER,0,m_v_data.F_color_size,color);

        Eigen::MatrixXi* F=(Eigen::MatrixXi*)m_v_data.F_F->value;
   // float color[F->rows()*3][3];
    //glBindBuffer(GL_ARRAY_BUFFER,Buffers[4]);
    //glBufferData(GL_ARRAY_BUFFER,sizeof(color),0,GL_STATIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER,)

    //glDrawElements(GL_TRIANGLES,F->rows()*3,GL_UNSIGNED_INT,0);
        glDrawArrays(GL_TRIANGLES,0,F->rows()*3);
   }

    glUniform1f(glGetUniformLocation(program,"Mesh_or_Edge"),1);
   int size1=node_size(m_v_data.E_V); 
   for(int node_i=size;node_i<size+size1;node_i++)
   {
         Eigen::MatrixXi* F=(Eigen::MatrixXi*)m_v_data.E_E->value;      if(F->rows()==0)
         {
            continue;
         }
        glBindVertexArray(m_v_data.VAOs[node_i]);

        glDrawElements(GL_LINES,F->rows()*2,GL_UNSIGNED_INT,0);
 
   
   }
   glBindVertexArray(m_v_data.VAOs[size+size1]);
   glDrawArrays(GL_LINES,0,node_size(m_v_data.marked_edges)*2);
    

       
    
}
void display(GLuint program)
{//以下两个语句成对使用
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    static const float black[]={0.0f,0.0f,0.0f,0.0f};
    glClearBufferfv(GL_COLOR,0,black);
//glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
//glDrawArrays(GL_TRIANGLES,0,6);


}
void show()
{
  
   glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(800,600,"learnopengl",NULL,NULL);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif
    if(window==NULL)
    {
        printf("Failed to create GLFW window\r\n");
        return;

    }
GlobalInfo_init(&globalinfo);
    arc.ginfo=&globalinfo;
    Arcroll_init(&arc);
//globalinfo.resolution[0]=800.0;
//globalinfo.resolution[1]=600.0;
    glfwMakeContextCurrent(window);
    //m_v_data.VAOs=(GLuint*)malloc(sizeof(GLuint));
    //m_v_data.Buffers=(GLuint*)malloc(sizeof(GLuint));


//glfwMakeContexCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to load glad\n");
        return;
    }

    Mesh_view_data_init(&m_v_data);
    //glGenVertexArrays(4,m_v_data.VAOs);
    //************************
    ShaderInfo shaders[]={
    { GL_VERTEX_SHADER, "mesh.vert" },
        { GL_FRAGMENT_SHADER, "mesh.frag" },
        { GL_NONE, NULL }   
    };

    _Shader_(shaders);
    GLuint program;
    program=_Program_(shaders);
        
    glUseProgram(program);//开启这个词更合适
//*****************************************
//glGenVertexArrays(1,VAOs);
    clock_t start,finish;
    start=clock();
   set_callback(window);
    init_uniform(program);

    init_texture();

//*****************************************
//glGenVertexArrays(1,VAOs);
    prepare_mesh_data();
    prepare_edge_data();
   
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
       

        // render
        // ------
        
         finish=clock();
        globalinfo.run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
        set_uniform(program);
       // glUniform1f(glGetUniforLocation())
        display(program);
        draw_elements(program);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

}

