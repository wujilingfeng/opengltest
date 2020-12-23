#include<stdio.h>
//#include<Math/Viewer_Matrix4x4.h>
//#include "tools_node.h"
//#include<Viewer_Interpreter/Viewer_OpenglAlg.h>
//#include<Viewer_World_Manager/Viewer_World_Manager.h>
#include<Viewer_Interpreter/Viewer_OpenGL_Interpreter.h>
//#include<GLFW/glfw3.h>
#include<config.h>

#include "include/Arcroll.h"
#define Matrix4x4 Viewer_Matrix4x4_
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//#include<ft2build.h>
//#include FT_FREETYPE_H
typedef struct UP_Data{
    Viewer_Opengl_Interpreter* voi;
    Viewer_Faces* vf; 


} UP_Data;



static void upd_key_callback(Viewer_Intera* vi)
{
    UP_Data* upd=(UP_Data*)(vi->representation);
    Viewer_Opengl_Interpreter* voi=upd->voi;
    float color[]={1.0,0.0,0.0,1.0};
   // upd->vf->set_color(upd->vf,color);
    
    voi->update_data(voi);
  //  printf("update\n");
}
static void load_data(Viewer_Opengl_Interpreter_Shader_Program *voisp)
{
    if(voisp->program==0)
    {
    
        _Shader_(voisp->shaders);
        voisp->program=_Program_(voisp->shaders); 
    }
    //glUseProgram(voisp->program);
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
    voisp->tex=(GLuint*)malloc(sizeof(GLuint));

    ImageInfo* imi=_ReadImageFile_((char*)"lena.jpg");
    // texture 1
    // ---------
    glGenTextures(2, voisp->tex);
    glBindTexture(GL_TEXTURE_2D, voisp->tex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imi->width, imi->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imi->data);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    //int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    //unsigned char *data = stbi_load("lena.jpg", &width, &height, &nrChannels, 0);
    //printf("nch:%d\n",nrChannels);
    if (imi->data)
    {
        
    }
    else
    {
        printf("failed to load testure11\n");
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    ImageInfo_free(imi);
    imi=_ReadImageFile_((char*)"linyueru.jpg");
    _Texture_(imi,voisp->tex[1]);
    ImageInfo_free(imi);
    //stbi_image_free(data);
    
    glUseProgram(voisp->program);
    glUniform1i(glGetUniformLocation(voisp->program,"texture1"),0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, voisp->tex[0]);
    glBindTexture(GL_TEXTURE_2D, voisp->tex[1]);

}
static void render(Viewer_Opengl_Interpreter_Shader_Program*voisp)
{

		/* 着色前，清除深度缓冲 和颜色缓冲 */
	glUseProgram(voisp->program);
    
    // create transformations 
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
    //glUseProgram(voisp->program);

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
	unsigned int indices[] = {  
    0, 1, 2, 
    1, 2, 3,  
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
    //glViewport(0,0,500,500);
	glUseProgram(voisp->program);
    glUniform4f(glGetUniformLocation(voisp->program, "ourColor"), 0.5f, 0.5, 0.7f, 0.5f);

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
    char* p_v=(char*)malloc(sizeof(char)*60);
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/tst1_v.vs");
    char* p_f=(char*)malloc(sizeof(char)*60);
    memset(p_f,0,sizeof(char)*60);

    strcat(strcat(p_f,MESH_VIEWER_PATH),"/tst1_f.fs");
    
    voi.create_shader_program(&voi,p_v,p_f,load_data1,render1); 
    
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/tst2_v.vs");
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/tst2_f.fs"); 
    voi.create_shader_program(&voi,p_v,p_f,load_data,render);
    
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"ui.vert");
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"ui.frag");
    voi.create_shader_program(&voi,p_v,p_f,NULL,NULL);

    free(p_v);free(p_f);
    voi.interpreter(&voi);
}

void test2()
{
    Viewer_World vw;
    Viewer_World_init(&vw);
    char camera[]="Camera";
    Node* n=vw.create_something(&vw,camera);
    Viewer_Something*ms=(Viewer_Something*)(n->value);
    Viewer_Camera*mc=(Viewer_Camera*)(ms->evolution);
    mc->is_using=1;
    Matrix4x4 *p=Projection(M_PI/3.0f,(float)(vw.g_info->resolution[0])/(float)(vw.g_info->resolution[1]),0.5f,200.0f);
    p->copy_data(mc->Proj,p);
    Matrix4x4_free(p);

    free_node(n);
    
    char points[]="Points";
    n=vw.create_something(&vw,points);
    ms=(Viewer_Something*)(n->value);
    Viewer_Points * mp=(Viewer_Points*)(ms->evolution);
    mp->pointsize=20.0;
    mp->Data_rows=3;
    //mp->color_rows=mp->Data_rows;
    mp->Data=(float*)malloc(sizeof(float)*3*mp->Data_rows);
    mp->Data[0]=0.5;mp->Data[1]=0.6;mp->Data[2]=0.2;
    mp->Data[3]=0.1;mp->Data[4]=1.1;mp->Data[5]=0.1;
    mp->Data[6]=1.0;mp->Data[7]=1.0;mp->Data[8]=1.0;
    float colorp[]={1,0,0,1};
    mp->set_color(mp,colorp);
    free_node(n);
    char intera[]="Intera";
    n=vw.create_something(&vw,intera);
    ms=(Viewer_Something*)(n->value);
    Viewer_Intera* mi=(Viewer_Intera*)(ms->evolution);
    Viewer_Arcroll*ma=(Viewer_Arcroll*)malloc(sizeof(Viewer_Arcroll));
    Viewer_Arcroll_init(ma);
    ma->mc=mc;
    ma->vw=&vw;
    mi->representation=(void*)ma;
    mi->cursor_position_callback=viewer_Arcroll_cursor_position_callback;
    mi->scroll_callback=viewer_Arcroll_scroll_callback;
    mi->mouse_button_callback=viewer_Arcroll_mouse_button_callback;
    free_node(n);

    n=vw.create_something(&vw,intera);
    ms=(Viewer_Something*)(n->value);
    mi=(Viewer_Intera*)(ms->evolution);
    mi->representation=(void*)(&vw);
    free_node(n);
    //***************************
    n=vw.create_something(&vw,intera);
    ms=(Viewer_Something*)(n->value);
    mi=(Viewer_Intera*)(ms->evolution);
    UP_Data* upd=(UP_Data*)malloc(sizeof(UP_Data));
    //upd-> 
    mi->representation=(void*)upd;
    mi->key_callback=upd_key_callback;
    free_node(n); 
      
//********************
    char  faces[]="Faces";
    n=vw.create_something(&vw,faces);    
    ms=(Viewer_Something*)(n->value);
   // ms->disappear=1;
    Viewer_Faces* mf=(Viewer_Faces*)(ms->evolution);
    upd->vf=mf;
    free_node(node_reverse(n));
    mf->color_rows=8;mf->normal_rows=12;
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
    texcoords[7]=3;
    texcoords[8]=1.0;texcoords[9]=0.0;
    texcoords[10]=0.0,texcoords[11]=1.0;
    texcoords[12]=1.0;texcoords[13]=1.0;
    mf->Data=v;
    mf->Data_index=f;
    mf->Data_rows=8;
    mf->Data_index_rows=12;
    //是否开启透明
    //mf->is_transparent=1;

    //*******************

    //************************
    char texture[]="Texture";
    n=vw.create_something(&vw,texture);
    ms=(Viewer_Something*)(n->value);
    free_node(n);
    Viewer_Texture*mt=(Viewer_Texture*)(ms->evolution);
    mf->texture=ms;
    mt->image_file=(char*)malloc(sizeof(char)*20);
    strcpy(mt->image_file,"linyueru.jpg");
    mt->each_face_texture_coord=texcoords;







    char edges[]="Edges";
//**********************************

    n=vw.create_something(&vw,edges);
    auto vs=(Viewer_Something*)(n->value);
  //  vs->disappear=1;
    auto ve=(Viewer_Edges*)(vs->evolution);
    ve->Data_rows=4;
    ve->Data_index_rows=3;
    ve->Data=(float*)malloc(sizeof(float)*3*ve->Data_rows);
    ve->Data_index=(unsigned int*)malloc(sizeof(unsigned int)*2*ve->Data_index_rows);     
    ve->Data[0]=0;ve->Data[1]=0;ve->Data[2]=0;
    ve->Data[3]=1;ve->Data[4]=0;ve->Data[5]=0;
    ve->Data[6]=0;ve->Data[7]=1;ve->Data[8]=0; 
    ve->Data[9]=0;ve->Data[10]=0;ve->Data[11]=1;
   

    ve->Data_index[0]=0;ve->Data_index[1]=1;
    ve->Data_index[2]=0;ve->Data_index[3]=2; 
    ve->Data_index[4]=0;ve->Data_index[5]=3;


    ve->color_rows=ve->Data_index_rows;
    ve->color=(float*)malloc(sizeof(float)*4*ve->color_rows);
    memset(ve->color,0,sizeof(float)*4*ve->color_rows);

    ve->color[0]=1;ve->color[1]=0; ve->color[2]=0;ve->color[3]=1;
    ve->color[4]=0;ve->color[5]=1; ve->color[6]=0;ve->color[7]=1;
    ve->color[8]=0;ve->color[9]=0; ve->color[10]=1;ve->color[11]=1;
    ma->vs=vs;

    //**************************************
    char cursor_shape[]="Cursor_Shape";
    n=vw.create_something(&vw,cursor_shape);
    vs=(Viewer_Something*)(n->value);
    auto vcs=(Viewer_Cursor_Shape*)(vs->evolution);
    vcs->shape_name=(char*)malloc(sizeof(char)*100);
    memset(vcs->shape_name,0,sizeof(char)*100);
    strcpy(vcs->shape_name,"ibeam");
    vcs->is_using=1;

    char texts[]="Texts";
    n=vw.create_something(&vw,texts);
    vs=(Viewer_Something*)(n->value);
    auto vtexts=(Viewer_Texts*)(vs->evolution);
    //float colors[4]={0.5,0.8,0.3,1.0};
    //Viewer_Texts_initn(vtexts,"my name is: ",-1,-0.9,0.001,colors,NULL);
    vtexts->str=(char*)malloc(sizeof(char)*40);
    memset(vtexts->str,0,sizeof(char)*40);
    strcpy(vtexts->str,"myname is : libo12138||");
    vtexts->xy[0]=-1.0;vtexts->xy[1]=-0.9;vtexts->scale=0.001;
   
    vtexts->colors[0*4+0]=1.0;vtexts->colors[0*4+1]=0.0;vtexts->colors[0*4+2]=0.0;vtexts->colors[0*4+3]=1.0;
    vtexts->colors[1*4+0]=1.0;vtexts->colors[1*4+1]=0.0;vtexts->colors[1*4+2]=0.0;vtexts->colors[1*4+3]=1.0;
    vtexts->colors[2*4+0]=1.0;vtexts->colors[2*4+1]=0.0;vtexts->colors[2*4+2]=0.0;vtexts->colors[2*4+3]=1.0;
    vtexts->colors[3*4+0]=1.0;vtexts->colors[3*4+1]=0.0;vtexts->colors[3*4+2]=0.0;vtexts->colors[3*4+3]=1.0;
    //((float*)(vtexts->mat->data))[0*4+3]=0.3;

    //vs->disappear=1;



    vw.print_self(&vw);


        

    Viewer_Opengl_Interpreter voi;
    Viewer_Opengl_Interpreter_init(&voi);
  
    upd->voi=&voi;
    voi.world=&vw;
    voi.interpreter(&voi);

}



//unsigned char image[H]
int main(int argc,char**argv)
{
    ImageInfo* imi=_ReadImageFile_("lena.jpg");

    _is_reverse_image_writing(1);
    //_is_reverse_image_reading(0);
    _Write_PNG_File_("mytestpng.png",imi);
    ImageInfo_free(imi);
    //test1();  
    test2();
    return 0;
}
