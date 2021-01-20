#include <Viewer_Interpreter/Viewer_OpenGL_Interpreter.h>
#define Viewer_oisp Viewer_Opengl_Interpreter_Shader_Program
#define Matrix4x4 Viewer_Matrix4x4_

static struct Viewer_oisp* Viewer_create_shader_program(Viewer_Opengl_Interpreter* voi,char*s1,char*s2,void(*load_data)(struct Viewer_oisp*),void(*render)(struct Viewer_oisp*),Viewer_World* vw)
{
	Viewer_oisp* voisp=(Viewer_oisp*)malloc(sizeof(Viewer_oisp));
	
	Viewer_Opengl_Interpreter_Shader_Program_init(voisp);
	char* p_v=(char*)malloc(sizeof(char)*120);
    	memset(p_v,0,sizeof(char)*120);
    	strcat(p_v,s1);
   	char* p_f=(char*)malloc(sizeof(char)*120);
    	memset(p_f,0,sizeof(char)*120);
    	strcat(p_f,s2);
    	voisp->shaders[0].type=GL_VERTEX_SHADER;
    	voisp->shaders[0].filename=p_v;
    	voisp->shaders[1].type=GL_FRAGMENT_SHADER;
    	voisp->shaders[1].filename=p_f;
    	voisp->shaders[2].type=GL_NONE;
    	voisp->shaders[2].filename=NULL;
    	voisp->load_data=load_data;
    	voisp->render=render;
	//voisp->voi=voi;
	voisp->vw=vw;
    voi->user_shader_program=node_overlying(voi->user_shader_program,voisp);
	
	return voisp;
	
}

static void Viewer_Interpreter_update_data(Viewer_Opengl_Interpreter* voi)
{
        for(Node* it=node_reverse(voi->user_shader_program);it!=NULL;it=(Node*)(it->Prev))
        {
        
            Viewer_Opengl_Interpreter_Shader_Program* voisp=(Viewer_Opengl_Interpreter_Shader_Program*)(it->value);
            voisp->load_data(voisp);
        }

}

void Viewer_Opengl_Interpreter_init(Viewer_Opengl_Interpreter*moi)
{
    moi->world=NULL;
  /*  char* p_v=(char*)malloc(sizeof(char)*60);
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/mesh.vert");
    char* p_f=(char*)malloc(sizeof(char)*60);
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/mesh.frag");
    moi->shaders=(ShaderInfo*)malloc(sizeof(ShaderInfo)*3);
    moi->shaders[0].type=GL_VERTEX_SHADER;
    moi->shaders[0].filename=p_v;
    moi->shaders[1].type=GL_FRAGMENT_SHADER;
    moi->shaders[1].filename=p_f;
    moi->shaders[2].type=GL_NONE;
    moi->shaders[2].filename=NULL;*/
    moi->interpreter=Viewer_Opengl_Interpreter_interpreter;
      moi->update_data=Viewer_Interpreter_update_data;
    moi->user_shader_program=NULL;
	moi->create_shader_program=Viewer_create_shader_program;
   /* char* p_v=(char*)malloc(sizeof(char)*120);
    memset(p_v,0,sizeof(char)*120);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/mesh.vert");
    char* p_f=(char*)malloc(sizeof(char)*120);
    memset(p_f,0,sizeof(char)*120);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/mesh.frag");
    moi->create_shader_program(moi,p_v,p_f,Viewer_default_load_data,Viewer_default_render);
    memset(p_v,0,sizeof(char)*120);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/ui.vert");
    memset(p_f,0,sizeof(char)*120);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/ui.frag");
    moi->create_shader_program(moi,p_v,p_f,load_data2,render2);
    free(p_v);free(p_f);
    */
    //moi->s_e=0;
    moi->update=0;
    moi->prop=NULL;	
}
void Viewer_Opengl_Interpreter_initd(Viewer_Opengl_Interpreter*voi,Viewer_World*vw )
{
    Viewer_Opengl_Interpreter_init(voi);
    voi->world=vw;
    char* p_v=(char*)malloc(sizeof(char)*120);
    memset(p_v,0,sizeof(char)*120);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/mesh.vert");
    char* p_f=(char*)malloc(sizeof(char)*120);
    memset(p_f,0,sizeof(char)*120);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/mesh.frag");
    Viewer_oisp* voisp= voi->create_shader_program(voi,p_v,p_f,Viewer_default_load_data,Viewer_default_render,vw);

    Viewer_FrameBuffer* vfb=(Viewer_FrameBuffer*)malloc(sizeof(Viewer_FrameBuffer));
    Viewer_FrameBuffer_init(vfb);
    voisp->prop=vfb;


    memset(p_v,0,sizeof(char)*120);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/ui.vert");
    memset(p_f,0,sizeof(char)*120);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/ui.frag");
    Viewer_oisp*voisp1=voi->create_shader_program(voi,p_v,p_f,Viewer_load_ui_data,Viewer_render_ui,vw);
    free(voisp1->vfb);
    voisp1->vfb=voisp->vfb;


    memset(p_v,0,sizeof(char)*120);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/quad.vert");

    memset(p_f,0,sizeof(char)*120);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/quad.frag");

    Viewer_oisp* voisp2= voi->create_shader_program(voi,p_v,p_f,Viewer_load_quad_data,Viewer_render_quad,NULL);
    voisp2->tex=&(voisp->vfb->colortex);
  
    free(p_v);free(p_f);
    //printf("%d\n",node_size(voi->user_shader_program));
    
}

void Viewer_Opengl_Interpreter_interpreter(Viewer_Opengl_Interpreter*moi)
{
 	  Viewer_World* mw=moi->world;
      if(mw==NULL)
      {
        return ;
      }
	 glfwInit();
	
 
   // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(800,600,"Viewer1.0",NULL,NULL);
    //GLFWwindow* window1=glfwCreateWindow(800,600,"Windows1",NULL,NULL);

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

   

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //printf("node size user shader:%d\n",node_size(moi->user_shader_program));
    for(Node* it=node_reverse(moi->user_shader_program);it!=NULL;it=(Node*)(it->Prev))
	{
		
		Viewer_Opengl_Interpreter_Shader_Program* voisp=(Viewer_Opengl_Interpreter_Shader_Program*)(it->value);
        //voisp->vw=moi->world;
		if(voisp->load_data!=NULL)
        {
            voisp->load_data(voisp);
        }
	}
    glfwSetWindowUserPointer(window,(void*)mw);
    mw->g_info->window=(void*)window; 
   // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    viewer_set_callback(window);
	
	clock_t start,finish;
	start=clock();


    //set cursor shape
    //if(window)
    //GLFWcursor*cursor=glfwCreateStandardCursor(VIEWER_HAND_CURSOR);
    //GLFWcursor*cursor=glfwCreateStandardCursor(VIEWER_HRESIZE_CURSOR);
   // GLFWcursor*cursor=glfwCreateStandardCursor(VIEWER_VRESIZE_CURSOR);
    //GLFWcursor*cursor=glfwCreateStandardCursor(VIEWER_IBEAM_CURSOR);
    //GLFWcursor*cursor=glfwCreateStandardCursor(VIEWER_CROSSHAIR_CURSOR);
   // GLFWcursor*cursor=glfwCreateStandardCursor(VIEWER_ARROW_CURSOR);
    //glfwSetCursor(window,cursor);
//clipboard
    //glfwGetClipboardString(window);
//gflwSetClipboardString(window,"some new string");
    //glfwSetInputMode(window, GLFW_CURSOR, VIEWER_HAND_CURSOR) ;	
   // Viewer_Opengl_Interpreter_test_text();
	while(!glfwWindowShouldClose(window))
	{	
        if(moi->update==1)
        {
            for(Node* it=node_reverse(moi->user_shader_program);it!=NULL;it=(Node*)(it->Prev))
            {
        
                Viewer_Opengl_Interpreter_Shader_Program* voisp=(Viewer_Opengl_Interpreter_Shader_Program*)(it->value);
        //voisp->vw=moi->world;
                if(voisp->load_data!=NULL)
                {
                    voisp->load_data(voisp);
                }
            }

            printf("update\n");
            moi->update=0; 
        }
	   glfwMakeContextCurrent(window);	
       //glBindFramebuffer(GL_FRAMEBUFFER,0);
      //  glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
	   //	glClearColor(mw->background_color[0],mw->background_color[1],mw->background_color[2],mw->background_color[3]);
       // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        //glClear(GL_DEPTH_BUFFER_BIT);

        finish=clock();
        mw->g_info->run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
        
		for(Node* it=node_reverse(moi->user_shader_program);it!=NULL;it=(Node*)(it->Prev))
		{	
			Viewer_Opengl_Interpreter_Shader_Program* voisp=(Viewer_Opengl_Interpreter_Shader_Program*)(it->value);
			if(voisp->render!=NULL)
            {
                voisp->render(voisp);
            }
		}
        //set_uniform(moi);
        //display_setting();
        //draw_elements(moi);  
        glfwSwapBuffers(window);
        /*
        if(window1!=NULL)
        {
            if(!glfwWindowShouldClose(window1))
            {
                glfwMakeContextCurrent(window1);

                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(window1);
            } 
            else
            {
                glfwDestroyWindow(window1);
                window1=NULL;
            }
        }*/
        glfwPollEvents();	
	}
  
	glfwDestroyWindow(window);
    glfwTerminate();
//***********************************************
//****************************************************
    
    // free_node_value(names_id);
    // free_node(names_id);
    // char edges[]="Edges";
    // names_id=mw->find_species(mw,edges);
    // rbt.key=*((int*)(names_id->value));
    // rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
    // if(rbt1!=NULL)
    // {
    //     tree=(RB_Tree*)(rbt1->value);
    //     iter1=tree->begin(tree);
    //     for(;iter1->it!=NULL;iter1->next(iter1))
    //     {
    //         Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
    //         Viewer_Edges *ve=(Viewer_Edges*)(vs->evolution);
    //         glDeleteBuffers(3,ve->Buffers);
    //         glDeleteVertexArrays(1,&(ve->VAO));

    //     }    
    // }
    // free_node_value(names_id);
    // free_node(names_id);
    // char faces[]="Faces";
    // names_id=mw->find_species(mw,faces);
    // rbt.key=*((int*)(names_id->value));
    // rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);

    // if(rbt1!=NULL)
    // {
    //     tree=(RB_Tree*)(rbt1->value);
    //     iter1=tree->begin(tree);
    //     for(;iter1->it!=NULL;iter1->next(iter1))
    //     {
    //         Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
    //         Viewer_Faces* vf=(Viewer_Faces*)(vs->evolution);
    //         glDeleteBuffers(6,vf->Buffers);
    //         glDeleteVertexArrays(1,&(vf->VAO));
    //     }

    // }
  

}

#undef Viewer_oisp 
/*void Viewer_Opengl_Interpreter_routine_render(Viewer_Opengl_Interpreter* moi)
{ 
    moi->load_data(moi); 
    //prepare_rendering_data(mw);
   // prepare_mesh_viewer_world_data(moi); 
    _Shader_(moi->shaders);
    moi->program=_Program_(moi->shaders); 
    //glUseProgram(moi->program);//开启这个词更合适
    init_uniform(moi);
    //char image_file[]="linyueru.jpg";
    //add_texture_to_shader(GL_TEXTURE0,image_file);

    clock_t start,finish;
    start=clock();
   //set_callback(window);
   // init_uniform(program);
    while (!glfwWindowShouldClose(window))
    {
      
        glBindFramebuffer(GL_FRAMEBUFFER,0);
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
*/
