#include<stdio.h>
#include<Math/Viewer_Matrix4x4.h>
#include "tools_node.h"
#include<Viewer_Interpreter/Viewer_OpenglAlg.h>
#include<Viewer_World_Manager/Viewer_World_Manager.h>
#include<Viewer_Interpreter/Viewer_OpenGL_Interpreter.h>
#include<GLFW/glfw3.h>
#include<config.h>
#define Matrix4x4 Viewer_Matrix4x4_
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
//#include<ft2build.h>
//#include FT_FREETYPE_H
static void load_data(Viewer_Opengl_Interpreter_Shader_Program *voisp)
{
    if(voisp->program==0)
    {
    
        _Shader_(voisp->shaders);
        voisp->program=_Program_(voisp->shaders); 
    }
    float vertices[] = 
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    voisp->VAO=(GLuint*)malloc(sizeof(GLuint));
    voisp->Buffers=(GLuint**)malloc(sizeof(GLuint*));
    voisp->Buffers[0]=(GLuint*)malloc(sizeof(GLuint));
    GLuint* VAO=voisp->VAO;
    GLuint* VBO=voisp->Buffers[0];
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("lena.jpg", &width, &height, &nrChannels, 0);
    printf("nch:%d\n",nrChannels);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("failed to load testure11\n");
    }
    stbi_image_free(data);
    
    glUseProgram(voisp->program);
    voisp->tex1=texture1;
    glUniform1i(glGetUniformLocation(voisp->program,"texture1"),0);
    
}
static void render(Viewer_Opengl_Interpreter_Shader_Program*voisp)
{

		//着色前，清除深度缓冲 和颜色缓冲
	glUseProgram(voisp->program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, voisp->tex1);
 
            // create transformations  构造变换矩阵，先初始化为单位矩阵
        Matrix4x4 model,temp_m;
        Matrix4x4_init_float(&model);Matrix4x4_init_float(&temp_m);
        float *data=(float*)(temp_m.data);
        float tempx=0.9*((float)glfwGetTime()),tempy=0.65*((float)glfwGetTime());
        data[0*4+0]=cos(tempx);data[0*4+1]=-sin(tempx)*sin(tempy);
        data[0*4+2]=sin(tempx)*cos(tempy);
        data[1*4+1]=cos(tempy);
        data[1*4+2]=sin(tempy);
        data[2*4+0]=-sin(tempx);
        data[2*4+1]=-cos(tempx)*sin(tempy);
        data[2*4+2]=cos(tempx)*cos(tempy);
        model.mult(&model,&temp_m);
        ((float*)model.data)[2*4+3]=2.0;
        Matrix4x4 *p=Projection(M_PI/3.0f,800.0/600.0,0.5f,200.0f);
	    glUniformMatrix4fv(glGetUniformLocation(voisp->program, "Proj"), 1, GL_TRUE, (float*)(p->data));
        glUniformMatrix4fv(glGetUniformLocation(voisp->program,"Object_Matrix"),1,GL_TRUE,(float*)(model.data));
        Matrix4x4_free(p);
        free(model.data);free(temp_m.data);

        // render box
        //glViewport(0.0,0.0,300,200);
        glBindVertexArray(voisp->VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
}
static void load_data1(Viewer_Opengl_Interpreter_Shader_Program*voisp)
{
    if(voisp->program==0)
    { 
        _Shader_(voisp->shaders);
        voisp->program=_Program_(voisp->shaders); 
    }

	float vertices2[] = {
		-0.6f, -0.6f, 0.6f, 
		0.6f, -0.6f, 0.6f, 
		-0.6f, 0.6f, 0.6f, 
		0.6f, 0.6f, 0.6f,  
		-0.6f, -0.6f, 0.8f, 
		0.6f, -0.6f, 0.8f, 
		-0.6f, 0.6f, 0.8f, 
		0.6f, 0.6f, 0.8f,  
	};
	unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 2, // 第一个三角形
    1, 2, 3,  // 第二个三角形
	4,5,6,5,6,7,

	0,1,4,1,4,5,
	2,3,6,3,6,7,

	0,2,4,2,4,6,
	1,3,4,3,4,7
	};
    voisp->VAO=(GLuint*)malloc(sizeof(GLuint));
    voisp->Buffers=(GLuint**)malloc(sizeof(GLuint*));
    voisp->Buffers[0]=(GLuint*)malloc(sizeof(GLuint));
    GLuint*VAO=voisp->VAO;
    GLuint*VBO=voisp->Buffers[0];

	glGenVertexArrays(1, VAO);
	glGenBuffers(2, VBO);
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 
}
static void render1(Viewer_Opengl_Interpreter_Shader_Program* voisp)
{
	glUseProgram(voisp->program);
    glUniform4f(glGetUniformLocation(voisp->program, "ourColor"), 0.2f, 0.5, 0.7f, 0.5f);

            // create transformations  构造变换矩阵，先初始化为单位矩阵
    Matrix4x4 model,temp_m;
    Matrix4x4_init_float(&model);Matrix4x4_init_float(&temp_m);
    float *data=(float*)(temp_m.data);
    float tempx=0.9*((float)glfwGetTime()),tempy=0.65*((float)glfwGetTime());
    data[0*4+0]=cos(tempx);data[0*4+1]=-sin(tempx)*sin(tempy);
    data[0*4+2]=sin(tempx)*cos(tempy);
    data[1*4+1]=cos(tempy);
    data[1*4+2]=sin(tempy);
    data[2*4+0]=-sin(tempx);
    data[2*4+1]=-cos(tempx)*sin(tempy);
    data[2*4+2]=cos(tempx)*cos(tempy);
    model.mult(&model,&temp_m);
    ((float*)model.data)[2*4+3]=2.0;
    Matrix4x4 *p=Projection(M_PI/3.0f,800.0/600.0,0.5f,200.0f);
	glUniformMatrix4fv(glGetUniformLocation(voisp->program, "Proj"), 1, GL_TRUE, (float*)(p->data));
    glUniformMatrix4fv(glGetUniformLocation(voisp->program,"Object_Matrix"),1,GL_TRUE,(float*)(model.data));
    Matrix4x4_free(p);
    free(model.data);free(temp_m.data);

        // render box
        //glViewport(0.0,0.0,300,200);
    glBindVertexArray(voisp->VAO[0]);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}
void test1()
{
    Viewer_World vw;
    Viewer_World_init(&vw);
    vw.print_self(&vw);
    Viewer_Opengl_Interpreter voi;
    Viewer_Opengl_Interpreter_init(&voi);
    voi.world=&vw;
    Viewer_Opengl_Interpreter_Shader_Program *voisp=(Viewer_Opengl_Interpreter_Shader_Program*)malloc(sizeof(Viewer_Opengl_Interpreter_Shader_Program));
    Viewer_Opengl_Interpreter_Shader_Program_init(voisp);
    char* p_v=(char*)malloc(sizeof(char)*60);
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/tst2_v.vs");
    char* p_f=(char*)malloc(sizeof(char)*60);
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/tst2_f.fs");
    voisp->shaders[0].type=GL_VERTEX_SHADER;
    voisp->shaders[0].filename=p_v;
    voisp->shaders[1].type=GL_FRAGMENT_SHADER;
    voisp->shaders[1].filename=p_f;
    voisp->shaders[2].type=GL_NONE;
    voisp->shaders[2].filename=NULL;
    voisp->load_data=load_data;
    voisp->render=render;
    voi.user_shader_program=node_overlying(voi.user_shader_program,(void*)voisp);
    voisp=(Viewer_Opengl_Interpreter_Shader_Program*)malloc(sizeof(Viewer_Opengl_Interpreter_Shader_Program));
    Viewer_Opengl_Interpreter_Shader_Program_init(voisp);

    p_v=(char*)malloc(sizeof(char)*60);
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/tst1_v.vs");
    p_f=(char*)malloc(sizeof(char)*60);
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/tst1_f.fs");
    voisp->shaders[0].type=GL_VERTEX_SHADER;
    voisp->shaders[0].filename=p_v;
    voisp->shaders[1].type=GL_FRAGMENT_SHADER;
    voisp->shaders[1].filename=p_f;
    voisp->shaders[2].type=GL_NONE;
    voisp->shaders[2].filename=NULL;
    voisp->load_data=load_data1;
    voisp->render=render1;
    voi.user_shader_program=node_overlying(voi.user_shader_program,(void*)voisp);
    voi.interpreter(&voi);

}
void test_opengl(Node*li,Node*l2)
{
    glfwInit();
   
    GLFWwindow* window = glfwCreateWindow(800, 600, "www.liwenz.com", NULL, NULL);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    if (window == NULL)
    {
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return ;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 使能深度测，就是位置上前面能遮住后面的，而不是顺序上后面数据覆盖前面数据

    // build and compile our shader zprogram
    // ------------------------------------ 
   	Viewer_Opengl_Interpreter_Shader_Program* voisp=(Viewer_Opengl_Interpreter_Shader_Program*)(li->value);
    voisp->load_data(voisp);
    /*ShaderInfo shader1[]={{GL_VERTEX_SHADER,(char*)"./tst2_v.vs"},
        {GL_FRAGMENT_SHADER,(char*)"./tst2_f.fs"},
        {GL_NONE,NULL}};
        _Shader_(shader1);   
    GLuint pro1=_Program_(shader1);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("lena.jpg", &width, &height, &nrChannels, 0);
    printf("nch:%d\n",nrChannels);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
    }
    stbi_image_free(data);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    glUseProgram(pro1);
    glUniform1i(glGetUniformLocation(pro1,"texture1"),0);
    */
   	Viewer_Opengl_Interpreter_Shader_Program*voisp1=(Viewer_Opengl_Interpreter_Shader_Program*)(l2->value);
    voisp1->load_data(voisp1);
/*
    ShaderInfo shader2[]={{GL_VERTEX_SHADER,(char*)"./tst1_v.vs"},
        {GL_FRAGMENT_SHADER,(char*)"./tst1_f.fs"},
        {GL_NONE,NULL}};

    _Shader_(shader2);
    GLuint pro2=_Program_(shader2);
	float vertices2[] = {
		-0.6f, -0.6f, 0.6f, 
		0.6f, -0.6f, 0.6f, 
		-0.6f, 0.6f, 0.6f, 
		0.6f, 0.6f, 0.6f,  
		-0.6f, -0.6f, 0.8f, 
		0.6f, -0.6f, 0.8f, 
		-0.6f, 0.6f, 0.8f, 
		0.6f, 0.6f, 0.8f,  
	};
	unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 2, // 第一个三角形
    1, 2, 3,  // 第二个三角形
	4,5,6,5,6,7,

	0,1,4,1,4,5,
	2,3,6,3,6,7,

	0,2,4,2,4,6,
	1,3,4,3,4,7
	};


	//--------------------------------------------------
	 unsigned int m_iVBO2, m_iVAO2;
	 unsigned int m_iEBO;
     GLuint* pvbo=(GLuint*)malloc(sizeof(GLuint));
	glGenVertexArrays(1, &m_iVAO2);
	glGenBuffers(2, pvbo);

	glBindVertexArray(m_iVAO2);

	glBindBuffer(GL_ARRAY_BUFFER, pvbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	//glGenBuffers(1, &m_iEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pvbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */
	//--------------------------------------------------
    clock_t start,finish;
    start=clock();
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----

        // render
        // ------
		glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
		//着色前，清除深度缓冲 和颜色缓冲
        finish=clock();
/*		glUseProgram(pro1);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // create transformations  构造变换矩阵，先初始化为单位矩阵
            Matrix4x4 model,temp_m;
        Matrix4x4_init_float(&model);Matrix4x4_init_float(&temp_m);
        float *data=(float*)(temp_m.data);
        float tempx=0.9*((float)glfwGetTime()),tempy=0.65*((float)glfwGetTime());
        data[0*4+0]=cos(tempx);data[0*4+1]=-sin(tempx)*sin(tempy);
        data[0*4+2]=sin(tempx)*cos(tempy);
        data[1*4+1]=cos(tempy);
        data[1*4+2]=sin(tempy);
        data[2*4+0]=-sin(tempx);
        data[2*4+1]=-cos(tempx)*sin(tempy);
        data[2*4+2]=cos(tempx)*cos(tempy);
        model.mult(&model,&temp_m);
        ((float*)model.data)[2*4+3]=2.0;
        Matrix4x4 *p=Projection(M_PI/3.0f,800.0/600.0,0.5f,200.0f);
	    glUniformMatrix4fv(glGetUniformLocation(pro1, "Proj"), 1, GL_TRUE, (float*)(p->data));
        glUniformMatrix4fv(glGetUniformLocation(pro1,"Object_Matrix"),1,GL_TRUE,(float*)(model.data));
           // render box
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
*/
        voisp1->render(voisp1);

        voisp->render(voisp);
/*
      Matrix4x4 model,temp_m;
        Matrix4x4_init_float(&model);Matrix4x4_init_float(&temp_m);
        float *data=(float*)(temp_m.data);
        float tempx=0.9*((float)glfwGetTime()),tempy=0.65*((float)glfwGetTime());
        data[0*4+0]=cos(tempx);data[0*4+1]=-sin(tempx)*sin(tempy);
        data[0*4+2]=sin(tempx)*cos(tempy);
        data[1*4+1]=cos(tempy);
        data[1*4+2]=sin(tempy);
        data[2*4+0]=-sin(tempx);
        data[2*4+1]=-cos(tempx)*sin(tempy);
        data[2*4+2]=cos(tempx)*cos(tempy);
        model.mult(&model,&temp_m);
        ((float*)model.data)[2*4+3]=2.0;
        Matrix4x4 *p=Projection(M_PI/3.0f,800.0/600.0,0.5f,200.0f);

	glUseProgram(pro2);

	glUniform4f(glGetUniformLocation(pro2, "ourColor"), 0.2f, 0.5, 0.7f, 0.5f);
	glUniformMatrix4fv(glGetUniformLocation(pro2, "Proj"), 1, GL_TRUE, (float*)(p->data));
    glUniformMatrix4fv(glGetUniformLocation(pro2,"Object_Matrix"),1,GL_TRUE,(float*)(model.data));
     Matrix4x4_free(p);
    free(model.data);free(temp_m.data); 

//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iEBO);
	 glBindVertexArray(m_iVAO2);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

*/
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();


}
int main(int argc,char**argv)
{
    Viewer_Opengl_Interpreter_Shader_Program *voisp=(Viewer_Opengl_Interpreter_Shader_Program*)malloc(sizeof(Viewer_Opengl_Interpreter_Shader_Program));
    Viewer_Opengl_Interpreter_Shader_Program_init(voisp);
    char* p_v=(char*)malloc(sizeof(char)*60);
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/tst2_v.vs");
    char* p_f=(char*)malloc(sizeof(char)*60);
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/tst2_f.fs");
    voisp->shaders[0].type=GL_VERTEX_SHADER;
    voisp->shaders[0].filename=p_v;
    voisp->shaders[1].type=GL_FRAGMENT_SHADER;
    voisp->shaders[1].filename=p_f;
    voisp->shaders[2].type=GL_NONE;
    voisp->shaders[2].filename=NULL;
    voisp->load_data=load_data;
    voisp->render=render;
     Node* li=NULL,*l2=NULL;
    li=node_overlying(li,(void*)voisp);
   voisp=(Viewer_Opengl_Interpreter_Shader_Program*)malloc(sizeof(Viewer_Opengl_Interpreter_Shader_Program));
    Viewer_Opengl_Interpreter_Shader_Program_init(voisp);

    p_v=(char*)malloc(sizeof(char)*60);
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/tst1_v.vs");
    p_f=(char*)malloc(sizeof(char)*60);
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/tst1_f.fs");
    voisp->shaders[0].type=GL_VERTEX_SHADER;
    voisp->shaders[0].filename=p_v;
    voisp->shaders[1].type=GL_FRAGMENT_SHADER;
    voisp->shaders[1].filename=p_f;
    voisp->shaders[2].type=GL_NONE;
    voisp->shaders[2].filename=NULL;
    voisp->load_data=load_data1;
    voisp->render=render1;
    l2=node_overlying(l2,(void*)voisp);
    test_opengl(li,l2);

 //   test1();
    return 0;
}
