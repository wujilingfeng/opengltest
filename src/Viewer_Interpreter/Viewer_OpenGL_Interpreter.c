#include <Viewer_Interpreter/Viewer_OpenGL_Interpreter.h>
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
      moi->update_data=NULL;
    moi->user_shader_program=NULL;
    moi->prop=NULL;
	
}
void Viewer_Opengl_Interpreter_Shader_Program_init(Viewer_Opengl_Interpreter_Shader_Program*voisp)
{
	voisp->shaders=(ShaderInfo*)malloc(sizeof(ShaderInfo)*3);;
	voisp->program=0;
	voisp->load_data=NULL;
	voisp->render=NULL;
	voisp->VAO=NULL;
	voisp->Buffers=NULL;
	voisp->tex=NULL;
	voisp->prop=NULL;

}
void Viewer_Opengl_Interpreter_interpreter(Viewer_Opengl_Interpreter*moi)
{
 	Viewer_World* mw=moi->world;
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
glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for(Node* it=moi->user_shader_program;it!=NULL;it=(Node*)(it->Next))
	{
		
		Viewer_Opengl_Interpreter_Shader_Program* voisp=(Viewer_Opengl_Interpreter_Shader_Program*)(it->value);
		voisp->load_data(voisp);
	}
    glfwSetWindowUserPointer(window,(void*)mw);
    mw->g_info->window=(void*)window; 
    viewer_set_callback(window);
	
	clock_t start,finish;
	start=clock();
    	
	
	while(!glfwWindowShouldClose(window))
	{	
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        	finish=clock();
        	mw->g_info->run_time=(float)30.0*(finish-start)/CLOCKS_PER_SEC;
        	
		for(Node* it=moi->user_shader_program;it!=NULL;it=(Node*)(it->Next))
		{
		
			Viewer_Opengl_Interpreter_Shader_Program* voisp=(Viewer_Opengl_Interpreter_Shader_Program*)(it->value);
			voisp->render(voisp);
		}
        	//set_uniform(moi);
        	//display_setting();
        	//draw_elements(moi);
      
        	glfwSwapBuffers(window);
        	glfwPollEvents();
		
	}
	glfwDestroyWindow(window);
    	glfwTerminate();

}
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
//*****************************************

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
