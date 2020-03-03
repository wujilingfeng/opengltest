#include <Mesh_view/glfw_callback.h>

void update_intera_information(GLFWwindow*window,Interactor_GlobalInfo*g_info)
{	
	double x,y;
        glfwGetCursorPos(window,&x,&y);
        g_info->mouse_coord[0]=x;
	g_info->mouse_coord[1]=y;
	int key=glfwGetKey(window,GLFW_KEY_F);
	if(key==GLFW_PRESS)
	{
        g_info->key=GLFW_KEY_F;
        g_info->key_action=GLFW_PRESS;
	}
    int mouse_action=glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    //printf("mous_action%d\n",mouse_action);
    if(mouse_action==GLFW_PRESS)
    {
        	g_info->button=GLFW_MOUSE_BUTTON_LEFT;
        	g_info->mouse_action=mouse_action;
    
    }
}
void mesh_viewer_cursor_position_callback(GLFWwindow* window,double x,double y)
{
    //获取的mousecoord是左上角为原点
    Mesh_viewer_world* mw=(Mesh_viewer_world*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    g_info->mouse_coord[0]=(float)x;
    g_info->mouse_coord[1]=(float)y;
          char intera[]="Intera";
    Node* id=Mesh_viewer_world_find_species(mw,intera);
    
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(id->value)));
    for(auto iter1=iter->second->rbegin();iter1!=iter->second->rend();iter1++)
    {
        Mesh_viewer_Intera* mi=(Mesh_viewer_Intera*)(iter1->second->evolution);
        mi->compute_state(mi);
        if(mi->cursor_position_callback!=0)
        {
        
            mi->cursor_position_callback(mi);
        }
        if(mi->state>=0)
        {
            break;
        }
    
    
    }
    free_node_value(id);
    free_node(id);
    
    return;

}
static void Mesh_viewer_decode_pickupinfo(Mesh_viewer_world* mw,Interactor_GlobalInfo* g_info)
{
    if(g_info->key==MESH_VIEWER_KEY_CONTROL&&g_info->key_action==1)
    {
        g_info->pick_something=0;
        char faces[]="faces";
        int id=g_info->readpixelcolor[0]*255*255+g_info->readpixelcolor[1]*255+g_info->readpixelcolor[2];
        Node* names_id=mw->find_species(mw,faces);
        std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(names_id->value)));
        int sum=0;
        for(auto iter1=iter->second->begin();iter1!=iter->second->end();iter1++)
        {
            sum+=((Mesh_viewer_faces*)(iter1->second->evolution))->Data_index_rows;
            if(id<sum)
            {
                g_info->pick_something=(void*)(iter1->second);
                break;
            }
        
        
        }
        free(names_id->value);
        free_node(names_id);

    }
    
}

void mesh_viewer_mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{
    
    Mesh_viewer_world* mw=(Mesh_viewer_world*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    glReadPixels(g_info->mouse_coord[0],g_info->resolution[1]-g_info->mouse_coord[1],3,3,GL_RGBA,GL_UNSIGNED_BYTE,g_info->readpixelcolor);

    if(action==MESH_VIEWER_PRESS)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<4;j++)
            {
                //printf("%d ",g_info->readpixelcolor[i*4+j]);
            }
            //printf("\n");
        }
    }
    
    g_info->button=button;
    g_info->mouse_action=action;
	g_info->mouse_mods=mods;

    Mesh_viewer_decode_pickupinfo(mw,g_info);  
    char intera[]="Intera";
    Node* id=Mesh_viewer_world_find_species(mw,intera);
    
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(id->value)));
    for(auto iter1=iter->second->rbegin();iter1!=iter->second->rend();iter1++)
    {
        Mesh_viewer_Intera* mi=(Mesh_viewer_Intera*)(iter1->second->evolution);
        mi->compute_state(mi);
        if(mi->mouse_button_callback!=0)
        {
        
            mi->mouse_button_callback(mi);
        }
        if(mi->state>=0)
        {
            break;
        }
    
    
    }
    free_node_value(id);
    free_node(id);
    return;
}
void mesh_viewer_framebuffer_size_callback(GLFWwindow* window,int w,int h)
{
    //w,h以像素为单位
    Mesh_viewer_world* mw=(Mesh_viewer_world*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    
    g_info->resolution[0]=w;
    g_info->resolution[1]=h;
    glViewport(0.0,0.0,w,h);
    char intera[]="Intera";
    Node* id=Mesh_viewer_world_find_species(mw,intera);
    
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(id->value)));
    for(auto iter1=iter->second->rbegin();iter1!=iter->second->rend();iter1++)
    {
        Mesh_viewer_Intera* mi=(Mesh_viewer_Intera*)(iter1->second->evolution);
        mi->compute_state(mi);
        if(mi->framebuffer_size_callback!=0)
        {
        
            mi->framebuffer_size_callback(mi);
        }
        if(mi->state>=0)
        {
            break;
        }
    
    
    }
    free_node_value(id);
    free_node(id);


    return;
}
void mesh_viewer_key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    Mesh_viewer_world* mw=(Mesh_viewer_world*)(glfwGetWindowUserPointer(window));
    //printf("%d\n",action);
    Interactor_GlobalInfo* g_info=mw->g_info;
    
    g_info->key=key;
    g_info->key_action=action;
//    printf("key action:%d\n",action);
    g_info->key_mods=mods;

    //printf("key:%d key_action:%d\n",key,action);    
    char intera[]="Intera";
    Node* id=Mesh_viewer_world_find_species(mw,intera);
    
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(id->value)));
    for(auto iter1=iter->second->rbegin();iter1!=iter->second->rend();iter1++)
    {
        Mesh_viewer_Intera* mi=(Mesh_viewer_Intera*)(iter1->second->evolution);
        mi->compute_state(mi);
        if(mi->key_callback!=0)
        {
        
            mi->key_callback(mi);
        }
        if(mi->state>=0)
        {
            break;
        }
    
    
    }
    free_node_value(id);
    free_node(id);
    


    return;
}
void mesh_viewer_scroll_callback(GLFWwindow* window,double x,double y)
{
   Mesh_viewer_world* mw=(Mesh_viewer_world*)(glfwGetWindowUserPointer(window));
    //Interactor_GlobalInfo* g_info=mw->g_info;

    char intera[]="Intera";
    Node* id=Mesh_viewer_world_find_species(mw,intera);
    
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(*((int*)(id->value)));
    for(auto iter1=iter->second->rbegin();iter1!=iter->second->rend();iter1++)
    {
        Mesh_viewer_Intera* mi=(Mesh_viewer_Intera*)(iter1->second->evolution);
        mi->compute_state(mi);
        if(mi->scroll_callback!=0)
        {
        
            mi->scroll_callback(mi,x,y);
        }
        if(mi->state>=0)
        {
            break;
        } 
    }
    free_node_value(id);
    free_node(id);
    return;
}
void mesh_viewer_set_callback(GLFWwindow* window)
{
    glfwSetMouseButtonCallback(window,mesh_viewer_mouse_button_callback);
    glfwSetCursorPosCallback(window,mesh_viewer_cursor_position_callback);
    glfwSetKeyCallback(window,mesh_viewer_key_callback); 
    glfwSetFramebufferSizeCallback(window,mesh_viewer_framebuffer_size_callback);
    glfwSetScrollCallback(window,mesh_viewer_scroll_callback);
}
