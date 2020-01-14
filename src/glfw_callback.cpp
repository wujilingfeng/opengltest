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
    glReadPixels(g_info->mouse_coord[0],g_info->resolution[1]-g_info->mouse_coord[1],3,3,GL_RGBA,GL_UNSIGNED_BYTE,g_info->readpixelcolor);
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
void mesh_viewer_mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{
    
    Mesh_viewer_world* mw=(Mesh_viewer_world*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<4;j++)
        {

            printf("%d ",g_info->readpixelcolor[i*4+j]);
        }
        printf("\n");
    }

    g_info->button=button;
    g_info->mouse_action=action;
	g_info->mouse_mods=mods;
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
    g_info->key_mods=mods;

    printf("key:%d key_action:%d\n",key,action);    
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
