#include <Viewer_Interpreter/glfw_callback.h>

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
        	g_info->mouse_button=GLFW_MOUSE_BUTTON_LEFT;
        	g_info->mouse_action=mouse_action;
    
    }
}
void viewer_cursor_position_callback(GLFWwindow* window,double x,double y)
{
    //
    Viewer_World* mw=(Viewer_World*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    g_info->mouse_coord[0]=(float)x;
    g_info->mouse_coord[1]=(float)y;
    char intera[]="Intera";
    Node* id=mw->find_species(mw,intera);
	RB_int rbt;
	rbt.key=*((int*)(id->value));
    RB_int *rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree* tree=NULL;
    RB_Trav* iter1=NULL;
    if(rbt1!=NULL)
    {
	    tree=(RB_Tree*)(rbt1->value);
        iter1=tree->rbegin(tree);
        for(;iter1->it!=NULL;iter1->prev(iter1))
        {
	        Viewer_Something* vs=((Viewer_Something*)(iter1->second(iter1)));
            Viewer_Intera* mi=(Viewer_Intera*)(vs->evolution);
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
	    free(iter1);
    }
    free_node_value(id);
    free_node(id);
    
    return;

}
static void viewer_decode_pickupinfo(Viewer_World* mw,Interactor_GlobalInfo* g_info)
{
    if(g_info->key==VIEWER_KEY_CONTROL&&g_info->key_action==1)
    {
        g_info->pick_something=NULL;
        int background_color[4]={(int)round(mw->background_color[0]*255),(int)round(mw->background_color[1]*255),(int)round(mw->background_color[2]*255),(int)round(mw->background_color[3]*255)};
        //is background color
        if(g_info->readpixelcolor[0]==background_color[0]&&g_info->readpixelcolor[1]==background_color[1]&&g_info->readpixelcolor[2]==background_color[2]&&g_info->readpixelcolor[3]==background_color[3])
        {
            printf("shi background:pick nothing\n");
            return;
        }
        //printf("%d %d\n",(int)round(mw->background_color[1]*255),g_info->readpixelcolor[1] );
	 int sum=0,temp_sum=0;
        int id=g_info->readpixelcolor[0]*255*255+g_info->readpixelcolor[1]*255+g_info->readpixelcolor[2];
      //  printf("pick num:%d\n",id);
	char points[]="Points";
	Node* names_id=mw->find_species(mw,points);
	RB_int rbt,*rbt1=NULL;
	rbt.key=*((int*)(names_id->value));
  	free(names_id->value);
    free_node(names_id);

	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree* tree=NULL;
	RB_Trav* iter1=NULL;
	if(rbt1!=NULL)
	{
		tree=((RB_Tree*)(rbt1->value));
	        iter1=tree->begin(tree);
            	for(;iter1->it!=NULL;iter1->next(iter1))
            	{
		        Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
			
                	temp_sum=((Viewer_Points*)(vs->evolution))->Data_rows;
                	if(id-sum<temp_sum)
                	{
                    		g_info->pick_something=(void*)(vs);
				vs->marked_element=id-sum;
                            printf("pick point pick_something id:%d element_id:%d\n",vs->id,id-sum); 
		//		printf("pick element id:%d\n",id-sum);
                    		return;
                	}
			sum+=temp_sum;
            	}
	        free(iter1);
	}
	char edges[]="Edges";
	names_id=mw->find_species(mw,edges);
	rbt.key=*((int*)(names_id->value));
  	free(names_id->value);
        free_node(names_id);
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
	if(rbt1!=NULL)
	{
		tree=((RB_Tree*)(rbt1->value));
	        iter1=tree->begin(tree);
            	for(;iter1->it!=NULL;iter1->next(iter1))
            	{
		        Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
			
                	temp_sum=((Viewer_Edges*)(vs->evolution))->Data_index_rows;
                   // printf("tempsum:%d\n",temp_sum);
                	if(id-sum<temp_sum)
                	{
                    		g_info->pick_something=(void*)(vs);
				vs->marked_element=id-sum;
                            printf("pick edges pick_something id:%d element_id:%d\n",vs->id,id-sum); 
			//	printf("pick element id:%d\n",id-sum);
                    		return;
                	}
			sum+=temp_sum;
            	}
	        free(iter1);
	}
        char faces[]="Faces";

        names_id=mw->find_species(mw,faces);
	rbt.key=*((int*)(names_id->value));
	free(names_id->value);
        free_node(names_id);
	rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);
        
        if(rbt1!=NULL)
        {
            tree=((RB_Tree*)(rbt1->value));
	    iter1=tree->begin(tree);
            for(;iter1->it!=NULL;iter1->next(iter1))
            {
		Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
                temp_sum=((Viewer_Faces*)(vs->evolution))->Data_index_rows;
                if(id-sum<temp_sum)
                {
                  
                    g_info->pick_something=(void*)(vs);
	                vs->marked_element=id-sum;
                    int readpixelcolor[3]={g_info->readpixelcolor[8*4+0],g_info->readpixelcolor[8*4+1],g_info->readpixelcolor[8*4+2]};
                    Viewer_Faces* vf=(Viewer_Faces*)(vs->evolution);
                    vf->triangle_coordinate[0]=readpixelcolor[0]/255.0;
                    vf->triangle_coordinate[1]=readpixelcolor[1]/255.0;
                    vf->triangle_coordinate[2]=readpixelcolor[2]/255.0;
                    int tt_sum=0;
                    for(int i=0;i<vs->marked_element;i++)
                    {
                        tt_sum+=(vf->Data_index[tt_sum]+1);
                    }
                   
                printf("pick faces and pick_something id:%d element_id:%d face_index_marked:%lf %lf %lf   ",vs->id,id-sum,readpixelcolor[0]/255.0,readpixelcolor[1]/255.0,readpixelcolor[2]/255.0);
			//printf("pick element id:%d\n",id-sum);
                    for(int i=0;i<vf->Data_index[tt_sum];i++)
                    {
                        printf("vid :%d ",vf->Data_index[tt_sum+i+1]);
                    }
                    printf("\n");
                    return ;
                }
		sum+=temp_sum;
            }

	        free(iter1);
        }

    }
}

void viewer_mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{
    
    Viewer_World* mw=(Viewer_World*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    glReadPixels(g_info->mouse_coord[0],g_info->resolution[1]-g_info->mouse_coord[1],3,3,GL_RGBA,GL_UNSIGNED_BYTE,g_info->readpixelcolor);
 //   printf("%d\n",g_info->mouse_button);
    if(action==VIEWER_PRESS&&button==VIEWER_MOUSE_BUTTON_LEFT)
    {
        /*for(int i=0;i<9;i++)
        {
            for(int j=0;j<4;j++)
            {
                printf("%d ",g_info->readpixelcolor[i*4+j]);
            }
            printf("\n");
        }*/
        //printf("%d %d %d %lf %lf %lf\n",g_info->readpixelcolor[0*4+0],g_info->readpixelcolor[0*4+1],g_info->readpixelcolor[0*4+2],g_info->readpixelcolor[8*4+0]/255.0,g_info->readpixelcolor[8*4+1]/255.0,g_info->readpixelcolor[8*4+2]/255.0);
        viewer_decode_pickupinfo(mw,g_info);  
    }
    
    g_info->mouse_button=button;
    g_info->mouse_action=action;
	g_info->mouse_mods=mods;

    char intera[]="Intera";
    Node* id=mw->find_species(mw,intera);
    RB_int rbt,*rbt1;
	rbt.key=*((int*)(id->value));
	rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree *tree=NULL;
    RB_Trav* iter1=NULL;
    if(rbt1!=NULL)
    {
        tree=(RB_Tree*)(rbt1->value);
        iter1=tree->rbegin(tree);
        for(;iter1->it!=NULL;iter1->prev(iter1))
        {
	        Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Intera* mi=(Viewer_Intera*)(vs->evolution);
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
	    free(iter1);
    }
    free_node_value(id);
    free_node(id);
    return;
}
void viewer_framebuffer_size_callback(GLFWwindow* window,int w,int h)
{
    //w,h以像素为单位
    Viewer_World* mw=(Viewer_World*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    
    g_info->resolution[0]=w;
    g_info->resolution[1]=h;
    glViewport(0.0,0.0,w,h);
    char intera[]="Intera";
    Node* id=mw->find_species(mw,intera);
    RB_int rbt,*rbt1;
	rbt.key=*((int*)(id->value));
	rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree* tree=(RB_Tree*)(rbt1->value);
  	RB_Trav* iter1=tree->rbegin(tree);
    for(;iter1->it!=NULL;iter1->prev(iter1))
    {
		Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
        Viewer_Intera* mi=(Viewer_Intera*)(vs->evolution);
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
	free(iter1);
    free_node_value(id);
    free_node(id);


    return;
}
void viewer_key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    Viewer_World* mw=(Viewer_World*)(glfwGetWindowUserPointer(window));
    //printf("%d\n",action);
    Interactor_GlobalInfo* g_info=mw->g_info;
    
    g_info->key=key;
    g_info->key_action=action;
//    printf("key action:%d\n",action);
    g_info->key_mods=mods;

    //printf("key:%d key_action:%d\n",key,action);    
    char intera[]="Intera";
    Node* id=mw->find_species(mw,intera);
    RB_int rbt,*rbt1;
	rbt.key=*((int*)(id->value));
	
	rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree* tree=(RB_Tree*)(rbt1->value);
	RB_Trav* iter1=tree->rbegin(tree);

    for(;iter1->it!=NULL;iter1->prev(iter1))
    {
		Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
        Viewer_Intera* mi=(Viewer_Intera*)(vs->evolution);
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
	free(iter1);
    free_node_value(id);
    free_node(id);
    


    return;
}
void viewer_scroll_callback(GLFWwindow* window,double x,double y)
{
    Viewer_World* mw=(Viewer_World*)(glfwGetWindowUserPointer(window));
    //Interactor_GlobalInfo* g_info=mw->g_info;

    char intera[]="Intera";
    Node* id=mw->find_species(mw,intera);
     RB_int rbt,*rbt1;
	rbt.key=*((int*)(id->value));
	
	rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree* tree=(RB_Tree*)(rbt1->value);
	RB_Trav* iter1=tree->rbegin(tree);
    for(;iter1->it!=NULL;iter1->prev(iter1))
    {
		Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
        Viewer_Intera* mi=(Viewer_Intera*)(vs->evolution);
        mi->compute_state(mi);
        if(mi->scroll_callback!=NULL)
        {
            mi->scroll_callback(mi,x,y);
        }
        if(mi->state>=0)
        {
            break;
        } 
    }
	free(iter1);
    free_node_value(id);
    free_node(id);
    return;
}
void viewer_drop_callback(GLFWwindow* window,int count,const char** paths)
{
    /*for(int i=0;i<count;i++)
    {
        printf("path:%s\n",paths[i]);
    }*/
    Viewer_World* mw=(Viewer_World*)(glfwGetWindowUserPointer(window));
    Interactor_GlobalInfo* g_info=mw->g_info;
    //printf("count:%d\n",g_info->drop_count);
    for(int i=0;i<g_info->drop_count;i++)
    {
        free(g_info->paths[i]);
    } 
    if(g_info->paths!=NULL)
    {
//        printf("dsfsd\n");
        free(g_info->paths);
        g_info->paths=NULL;
    }
    g_info->drop_count=count;
    g_info->paths=(char**)malloc(sizeof(char*)*count);
    for(int i=0;i<g_info->drop_count;i++)
    {
        g_info->paths[i]=(char*)malloc(sizeof(char)*200);
        strcpy(g_info->paths[i],paths[i]);

      //  printf("%s\n",g_info->paths[i] );
    }
    char intera[]="Intera";
    Node* id=mw->find_species(mw,intera);
     RB_int rbt,*rbt1;
    rbt.key=*((int*)(id->value));
    
    rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);
    RB_Tree* tree=(RB_Tree*)(rbt1->value);
    RB_Trav* iter1=tree->rbegin(tree);
    for(;iter1->it!=NULL;iter1->prev(iter1))
    {
        Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
        Viewer_Intera* mi=(Viewer_Intera*)(vs->evolution);
        mi->compute_state(mi);
        if(mi->drop_callback!=NULL)
        {       
            mi->drop_callback(mi);
        }
        if(mi->state>=0)
        {
            break;
        } 
    }
    free(iter1);
    free_node_value(id);
    free_node(id);
    return;
}
void viewer_set_callback(GLFWwindow* window)
{
    glfwSetMouseButtonCallback(window,viewer_mouse_button_callback);
    glfwSetCursorPosCallback(window,viewer_cursor_position_callback);
    glfwSetKeyCallback(window,viewer_key_callback); 
    glfwSetFramebufferSizeCallback(window,viewer_framebuffer_size_callback);
    glfwSetScrollCallback(window,viewer_scroll_callback);
    glfwSetDropCallback(window,viewer_drop_callback);
}
