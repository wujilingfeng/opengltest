#include <Viewer_Interpreter/Viewer_OpenGL_Interpreter.h>
#define Viewer_oisp Viewer_Opengl_Interpreter_Shader_Program
#define Matrix4x4 Viewer_Matrix4x4_

static struct Viewer_oisp* Viewer_create_shader_program(Viewer_Opengl_Interpreter* voi,char*s1,char*s2,void(*load_data)(struct Viewer_oisp*),void(*render)(struct Viewer_oisp*))
{
	Viewer_oisp* voisp=(Viewer_oisp*)malloc(sizeof(Viewer_oisp));
	
	Viewer_Opengl_Interpreter_Shader_Program_init(voisp);
	char* p_v=(char*)malloc(sizeof(char)*60);
    	memset(p_v,0,sizeof(char)*60);
    	strcat(p_v,s1);
   	char* p_f=(char*)malloc(sizeof(char)*60);
    	memset(p_f,0,sizeof(char)*60);
    	strcat(p_f,s2);
    	voisp->shaders[0].type=GL_VERTEX_SHADER;
    	voisp->shaders[0].filename=p_v;
    	voisp->shaders[1].type=GL_FRAGMENT_SHADER;
    	voisp->shaders[1].filename=p_f;
    	voisp->shaders[2].type=GL_NONE;
    	voisp->shaders[2].filename=NULL;
    	voisp->load_data=load_data;
    	voisp->render=render;
	voisp->voi=voi;
	voi->user_shader_program=node_overlying(voi->user_shader_program,voisp);
	
	return voisp;
	
}
static void Viewer_default_init_uniform(Viewer_oisp*voisp)
{

    GLuint program=voisp->program;
	glUseProgram(program);
    Viewer_World* mw=voisp->voi->world;
    Interactor_GlobalInfo* g_info=mw->g_info;
    Viewer_Camera* mc=0;
    char camera[]="Camera";
    Node*id=mw->find_species(mw,camera); 
	RB_int rbt,*rbt1;
	rbt.key=*((int*)(id->value));
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree* tree;
	RB_Trav* iter1;
    if(rbt1!=NULL)
    {
        tree=(RB_Tree*)(rbt1->value);
	    iter1=tree->begin(tree);

        for(;iter1->it!=NULL;iter1->next(iter1))
        {
	        Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
            mc=(Viewer_Camera*)(vs->evolution);
            if(vs->disappear==0&&mc->is_using==1)
            {
                break;
            }
            else
            {
                mc=0;
            }
        }
	    free(iter1);
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
    glUniform2fv(glGetUniformLocation(program,"iResolution"),1,a);
//把像素着色器的纹理绑定纹理单元GL_TEXURE0（也就是纹理位置）
    glUniform1i(glGetUniformLocation(program,"Faces_Vertices"),0);
    glUniform1i(glGetUniformLocation(program,"Faces_Index"),1);
    glUniform1i(glGetUniformLocation(program,"ourTexture"),3);
      //glUniform1f(glGetUniformLocation(program,"is_draw_vertices"),0.0);
    glUniform1f(glGetUniformLocation(program,"p_intera.is_pick"),0);

}
static void Viewer_default_set_uniform(Viewer_oisp*voisp)
{
    GLuint program=voisp->program;
	glUseProgram(program);
    Viewer_World* mw=voisp->voi->world;
    Interactor_GlobalInfo* g_info=mw->g_info;

    glUniform2f(glGetUniformLocation(program,"iMouse"),(float)g_info->mouse_coord[0],(float)g_info->mouse_coord[1]);
    //printf("iMouse:%lf %lf\n",(float)g_info->mouse_coord[0],(float)g_info->mouse_coord[1]);
    glUniform2f(glGetUniformLocation(program,"iResolution"),(float)g_info->resolution[0],(float)g_info->resolution[1]);
    glUniform1f(glGetUniformLocation(program,"iTime"),g_info->run_time);
    if(g_info->key==VIEWER_KEY_CONTROL&&g_info->key_action==1)
    {
        glUniform1f(glGetUniformLocation(program,"p_intera.is_pick"),1);

    }
    else
    {
        glUniform1f(glGetUniformLocation(program,"p_intera.is_pick"),0);

    }
    Viewer_Camera* mc=0;
    char camera[]="Camera";
    Node*id=mw->find_species(mw,camera);
	RB_int rbt,*rbt1;
	rbt.key=*((int*)(id->value));
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
    RB_Tree* tree;
    RB_Trav* iter1;
    if(rbt1!=NULL)
    {
 	    tree=(RB_Tree*)(rbt1->value);
	    iter1=tree->begin(tree);
        for(;iter1->it!=NULL;iter1->next(iter1))
        {
	        Viewer_Something* vs=(Viewer_Something*)(iter1->second(iter1));
            mc=(Viewer_Camera*)(vs->evolution);
            if(vs->disappear==0&&mc->is_using==1)
            {
                break;
            }
            else
            {
                mc=0;
            }
        }
        free(iter1);
    }
    if(mc!=0)
    {
        float* data=(float*)(mc->matrix_inverse->data);    
        glUniformMatrix4fv(glGetUniformLocation(program,"Camera_Matrix"),1,GL_TRUE,data);

    }
    free_node_value(id);
    free_node(id);

}
GLuint* test_add_array_to_shader(Viewer_oisp* voisp)
{
    Viewer_World* mw=voisp->voi->world;

    char names[]="Faces";
    GLfloat* vertices=0,*index=0;
    int len_rows=0,len_index_rows=0,len_index=0;
    Node* names_id=mw->find_species(mw,names);
	RB_int rbt,*rbt1;
	rbt.key=*((int*)(names_id->value));
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
	RB_Tree* tree;
	RB_Trav* iter1;

    if(rbt1!=NULL)
    {
	    tree=(RB_Tree*)(rbt1->value);
	    iter1=tree->begin(tree);

        for(;iter1->it!=NULL;iter1->next(iter1))
        {
            Viewer_Something *ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Faces *mf=(Viewer_Faces*)(ms->evolution);
            len_rows+=mf->Data_rows;
            len_index_rows+=mf->Data_index_rows;
            int temp_i=0,j=0;
            for(unsigned int i=0;i<mf->Data_index_rows;i++)
            {
                j=mf->Data_index[temp_i];
                temp_i+=(j+1);
                
            }
            len_index+=temp_i;
        }
        free(iter1);
    
    }
    if(len_index==0)
    {
        free_node_value(names_id);
        free_node(names_id);
        return 0;
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
    if(rbt1!=NULL)
    { 
        tree=(RB_Tree*)(rbt1->value);
	    iter1=tree->begin(tree);

        for(;iter1->it!=NULL;iter1->next(iter1))
        {
            Viewer_Something *ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Faces *mf=(Viewer_Faces*)(ms->evolution);
            temp_i=0;
            for(unsigned int i=0;i<mf->Data_index_rows;i++)
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
            for(unsigned int i=0;i<mf->Data_rows;i++)
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
    	
	
	//moi->faces_len=len_index;
	//moi->faces_vertices_len=len_rows;
    GLuint program=voisp->program;
    glUseProgram(program);
    glUniform1f(glGetUniformLocation(program,"Faces_len"),(float)(len_index));
    glUniform1f(glGetUniformLocation(program,"Faces_Vertices_rows"),(float)(len_rows));

    GLuint* textures=(GLuint*)malloc(sizeof(GLuint)*2);
    glGenTextures(2,textures);
    _Texture_Array_GL_FLOAT(&image,textures[0]);
    _Texture_Array_GL_FLOAT(&image1,textures[1]);
    free(vertices);
    free(index);
    free_node_value(names_id);
    free_node(names_id);
    return textures;
}
static void Viewer_default_render(Viewer_oisp* voisp)
{
    Viewer_default_set_uniform(voisp);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//以下两个语句成对使用
   // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//glClear(GL_COLOR_BUFFER_BIT);
//上面两个语句等同以下两个语句
//	static const float black[]={0.2f,0.5f,1.0f,1.0f};
 //   glClearBufferfv(GL_COLOR,0,black);
   
//	glClear(GL_DEPTH_BUFFER_BIT);
    Viewer_World* mw=voisp->voi->world;
    Interactor_GlobalInfo*g_info=mw->g_info;

    glViewport(0.0,0.0,g_info->resolution[0],g_info->resolution[1]);
    char points[]="Points";
    Node* names_id=mw->find_species(mw,points);
    RB_int rbt,*rbt1;
    rbt.key=*((int*)(names_id->value));
    rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);
    RB_Tree* tree=NULL;
    RB_Trav* iter1=NULL;
    if(rbt1!=NULL)
    {
        tree=(RB_Tree*)(rbt1->value);
        iter1=tree->begin(tree);
        for(;iter1->it!=NULL;iter1->next(iter1))
        {
            Viewer_Something *ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Points *mp=(Viewer_Points*)(ms->evolution);
            
            if(ms->disappear==1||mp->Data==0)
            {continue;}
            if(ms->viewport[2]!=0&&ms->viewport[3]!=0)
            {
                glViewport(ms->viewport[0],ms->viewport[1],ms->viewport[2],ms->viewport[3]); 
            }
            else
            {
                 glViewport(0.0,0.0,g_info->resolution[0],g_info->resolution[1]); 

            }
	

            //printf("lyou\n");
            glPointSize(mp->pointsize);
            int v_size=mp->Data_rows;
            float *data=(float*)(mp->mat->data);
            glUniformMatrix4fv(glGetUniformLocation(voisp->program,"Object_Matrix"),1,GL_TRUE,data);
            //glUniform1f(glGetUniformLocation(moi->program,"is_draw_vertices"),1.0);
            glBindVertexArray(mp->VAO);
            //printf("vao:%u",mp->VAO);
            glDrawArrays(GL_POINTS,0,v_size); 

        }
        free(iter1);
    
    }
    free_node_value(names_id);
    free_node(names_id);

    //glUniform1f(glGetUniformLocation(moi->program,"is_draw_vertices"),0.0);
    glDisable(GL_BLEND);
    char edges[]="Edges";
    names_id=mw->find_species(mw,edges);
    rbt.key=*((int*)(names_id->value));
    rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);

    if(rbt1!=NULL)
    {
        tree=(RB_Tree*)(rbt1->value);
        iter1=tree->begin(tree);
        for(;iter1->it!=NULL;iter1->next(iter1))
        {
            Viewer_Something *ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Edges *me=(Viewer_Edges*)(ms->evolution);
            if(ms->disappear==1||me->Data==0||me->Data_index==0)
            {continue;}
            if(ms->viewport[2]!=0&&ms->viewport[3]!=0)
            {
                glViewport(ms->viewport[0],ms->viewport[1],ms->viewport[2],ms->viewport[3]); 
            }
            else
            {
                 glViewport(0.0,0.0,g_info->resolution[0],g_info->resolution[1]); 

            }

            glLineWidth(me->edgesize); 
            int v_size=me->Data_index_rows*2;
            float *data=(float*)(me->mat->data);
            glUniformMatrix4fv(glGetUniformLocation(voisp->program,"Object_Matrix"),1,GL_TRUE,data);
            glBindVertexArray(me->VAO); 
            glDrawArrays(GL_LINES,0,v_size); 
       
        }
        free(iter1);
    }
    free_node_value(names_id);
    free_node(names_id);

    char names[]="Faces";
    names_id=mw->find_species(mw,names);
    rbt.key=*((int*)(names_id->value));
    rbt1=mw->species2somethings->find(mw->species2somethings,&rbt);

    if(rbt1!=NULL)
    {
        tree=(RB_Tree*)(rbt1->value);
        iter1=tree->begin(tree);
        for(;iter1->it!=NULL;iter1->next(iter1))
        { 
            Viewer_Something *ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Faces *mf=(Viewer_Faces*)(ms->evolution);
            if(ms->disappear==1||mf->Data_index_rows==0||mf->VAO==0||mf->Buffers==0||mf->Data==NULL)
            {continue;}
            if(ms->viewport[2]!=0&&ms->viewport[3]!=0)
            {
                glViewport(ms->viewport[0],ms->viewport[1],ms->viewport[2],ms->viewport[3]); 
            }
            else
            {
                 glViewport(0.0,0.0,g_info->resolution[0],g_info->resolution[1]); 
            }

            if(mf->is_transparent==1)
            {
	            glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                 
            }
            else if(mf->is_transparent==0)
            {
                glDisable(GL_BLEND);
            }

            int v_size=0,temp_i=0;
            for(unsigned int i=0;i<mf->Data_index_rows;i++)
            {

                int j=mf->Data_index[temp_i];
                v_size+=(j-2)*3;
                temp_i+=(j+1);
            }
            float *data=(float*)(mf->mat->data);
            glUniformMatrix4fv(glGetUniformLocation(voisp->program,"Object_Matrix"),1,GL_TRUE,data);
            if(mf->texture!=NULL)
            {
                
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D,((Viewer_Texture*)(mf->texture->evolution))->tex); 
            }
            glBindVertexArray(mf->VAO);
            glDrawArrays(GL_TRIANGLES,0,v_size); 
        }
        free(iter1);
 
    }
    free_node_value(names_id);
    free_node(names_id);

}


static void Viewer_default_load_data(Viewer_oisp* voisp)
{
    if(voisp->program==0)
    { 
        _Shader_(voisp->shaders);
        voisp->program=_Program_(voisp->shaders); 
    }
    if(voisp->voi->world==NULL)
    {
        return;
    }
	int elements_id=0;
	
    Viewer_World* mw=voisp->voi->world;
    //Interactor_GlobalInfo* g_info=mw->g_info;
	char texture[]="Texture";
	Node* names_id=mw->find_species(mw,texture);
	RB_int rbt,*rbt1=NULL;
	rbt.key=*((int*)(names_id->value));
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
    RB_Tree* tree=NULL;
    RB_Trav*iter1=NULL;
	if(rbt1!=NULL)
	{
		tree=(RB_Tree*)(rbt1->value);		
		iter1=tree->begin(tree);
 		for(;iter1->it!=NULL;iter1->next(iter1))
        {
            Viewer_Something*ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Texture* mt=(Viewer_Texture*)(ms->evolution);
            if(ms->disappear==1||mt->image_file==0)
            {continue;}
            glDeleteTextures(1,&(mt->tex));
			glGenTextures(1,&(mt->tex));
			ImageInfo*imi=_ReadImageFile_(mt->image_file);
			_Texture_(imi,mt->tex);
			ImageInfo_free(imi);
            		//add_texture_to_shader(&(mt->tex),mt->image_file);
        }
		free(iter1);
    
	}
	free_node_value(names_id);
	free_node(names_id);

    elements_id=0;
	char points[]="Points";
	names_id=mw->find_species(mw,points);
	rbt.key=*((int*)(names_id->value));
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
	if(rbt1!=NULL)
	{
		tree=(RB_Tree*)(rbt1->value);
		iter1=tree->begin(tree);
		for(;iter1->it!=NULL;iter1->next(iter1))
		{
			Viewer_Something*ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Points *mp=(Viewer_Points*)(ms->evolution);
			if(ms->disappear==1||mp->Data==0)
			{
				continue;
			}
			if(mp->Buffers==NULL)
            {
                mp->Buffers=(GLuint*)malloc(sizeof(GLuint)*3);
            }
		    int v_size=mp->Data_rows;
            GLfloat*vertices=(GLfloat*)malloc(sizeof(GLfloat)*v_size*3);
            memset(vertices,0,sizeof(GLfloat)*v_size*3);

            GLfloat* e_id=(GLfloat*)malloc(sizeof(GLfloat)*v_size);
            memset(e_id,0,sizeof(GLfloat)*v_size);
            GLfloat* colors=(GLfloat*)malloc(sizeof(GLfloat)*v_size*4);
            memset(colors,0,sizeof(GLfloat)*v_size*4);
            //color
            if(mp->color==NULL&&mp->color_rows==mp->Data_rows)
            {
                mp->random_color(mp); 
            }
            for(int i=0;i<v_size*4;i++)
            {
                colors[i]=mp->color[i];
            } 
             
            for(int i=0;i<v_size;i++)
            {
                for(int j=0;j<3;j++)
                {
                    vertices[i*3+j]=(float)(mp->Data[i*3+j]); 
                }
                e_id[i]=elements_id++; 
            }

            glDeleteBuffers(1,mp->Buffers);
            glDeleteVertexArrays(1,&(mp->VAO));

            glGenVertexArrays(1,&(mp->VAO));
            glBindVertexArray(mp->VAO);
            glCreateBuffers(3,mp->Buffers);
            glBindBuffer(GL_ARRAY_BUFFER,mp->Buffers[0]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*3,vertices,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mp->Buffers[1]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size,e_id,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mp->Buffers[2]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*4,colors,GL_STATIC_DRAW);


            glBindBuffer(GL_ARRAY_BUFFER,mp->Buffers[0]);
            glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
            glEnableVertexAttribArray( 0 );

            glBindBuffer(GL_ARRAY_BUFFER,mp->Buffers[1]);
            glVertexAttribPointer(4,1,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray( 4 );
    
            glBindBuffer(GL_ARRAY_BUFFER,mp->Buffers[2]);
            glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray( 1 );

            glBindVertexArray(0);
            free(vertices);
            free(e_id);
		}
        free(iter1);
	}
    free_node_value(names_id);
    free_node(names_id);
    char edges[]="Edges";
    names_id=mw->find_species(mw,edges);
	rbt.key=*((int*)(names_id->value));
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);
    if(rbt1!=NULL)
    {
    	tree=(RB_Tree*)(rbt1->value);
		iter1=tree->begin(tree);
        for(;iter1->it!=NULL;iter1->next(iter1))
        {
            Viewer_Something*ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Edges *me=(Viewer_Edges*)(ms->evolution);
            if(ms->disappear==1||me->Data==0||me->Data_index==0)
            {continue;}
            if(me->Buffers==0)
            {
                me->Buffers=(GLuint*)malloc(sizeof(GLuint)*3);
            }
            int v_size=me->Data_index_rows*2;
            GLfloat* vertices=(GLfloat*)malloc(sizeof(GLfloat)*v_size*3); 
            memset(vertices,0,sizeof(GLfloat)*v_size*3);
            GLfloat* colors=(GLfloat*)malloc(sizeof(GLfloat)*v_size*4);
            memset(colors,0,sizeof(GLfloat)*v_size*4);
            GLfloat* e_id=(GLfloat*)malloc(sizeof(GLfloat)*v_size);
            memset(e_id,0,sizeof(GLfloat)*v_size);
            for(unsigned int i=0;i<me->Data_index_rows;i++)
            {
                int k=i*2+0;
                for(int j=0;j<3;j++)
                {
                    vertices[(i*2+0)*3+j]=me->Data[(me->Data_index[k])*3+j];
                }
                k=i*2+1;
                for(int j=0;j<3;j++)
                {
                    vertices[(i*2+1)*3+j]=me->Data[(me->Data_index[k])*3+j];
                
                }
                e_id[i*2+0]=elements_id;
                e_id[i*2+1]=elements_id;
                elements_id++;
            }
            //color
            if(me->color==NULL&&me->color_rows>0)
            {
                me->random_color(me); 
            } 
            if(me->color_rows==me->Data_index_rows)
            {
                //printf("here\n");
                for(unsigned int i=0;i<me->Data_index_rows;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        colors[(i*2+0)*4+j]=me->color[i*4+j];
                        colors[(i*2+1)*4+j]=me->color[i*4+j];
                    }   
                }
              ///  printf("rere\n");

            }
            else if(me->color_rows==me->Data_rows)
            {
                for(unsigned int i=0;i<me->Data_index_rows;i++)
                {
                    int k=i*2+0;
                    for(int j=0;j<4;j++)
                    {
                        colors[k*4+j]=me->color[me->Data_index[k]*4+j];
                    }
                    k=i*2+1;
                    for(int j=0;j<4;j++)
                    {
                        colors[k*4+j]=me->color[me->Data_index[k]*4+j];
                    }
                
                }
            }
            glDeleteBuffers(3,me->Buffers);
            glDeleteVertexArrays(1,&(me->VAO));
            glGenVertexArrays(1,&(me->VAO));
            glBindVertexArray(me->VAO);
            glCreateBuffers(3,me->Buffers);
            glBindBuffer(GL_ARRAY_BUFFER,me->Buffers[0]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*3,vertices,GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER,me->Buffers[1]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*4,colors,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,me->Buffers[2]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size,e_id,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,me->Buffers[0]);
            glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
            glEnableVertexAttribArray( 0 );
            glBindBuffer(GL_ARRAY_BUFFER,me->Buffers[1]);
            glVertexAttribPointer( 1, 4, GL_FLOAT,GL_FALSE, 0, 0 ); 
            glEnableVertexAttribArray( 1 );
            glBindBuffer(GL_ARRAY_BUFFER,me->Buffers[2]);
            glVertexAttribPointer(4,1,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(4);
            glBindVertexArray(0);
            free(colors);
            free(vertices);
            free(e_id);

        
        }
        free(iter1); 
    
    }
    free_node_value(names_id);
    free_node(names_id);
    char names[]="Faces";
   // elements_id=0;
    names_id=mw->find_species(mw,names);
    rbt.key=*((int*)(names_id->value));
	rbt1=(RB_int*)mw->species2somethings->find(mw->species2somethings,&rbt);

    if(rbt1!=NULL)
    {
  	    tree=(RB_Tree*)(rbt1->value);
		iter1=tree->begin(tree);
        for(;iter1->it!=NULL;iter1->next(iter1))
        {
            Viewer_Something *ms=(Viewer_Something*)(iter1->second(iter1));
            Viewer_Faces *mf=(Viewer_Faces*)(ms->evolution);
		
            if(ms->disappear==1||mf->Data_index_rows==0||mf->Data==NULL||mf->Data_rows==0)
            {continue;}

            if(mf->Buffers==NULL)
            {
                mf->Buffers=(GLuint*)malloc(sizeof(GLuint)*6);
            }
            if(mf->normal_rows>0&&mf->normal==0)
            {
                mf->compute_normal(mf);
            }

                        //vertex array
            int v_size=0,temp_i=0;
            for(unsigned int i=0;i<mf->Data_index_rows;i++)
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
            GLfloat* colors=(GLfloat*)malloc(sizeof(GLfloat)*v_size*4);
            GLfloat* normal=(GLfloat*)malloc(sizeof(GLfloat)*v_size*3);
            GLfloat* texcoords=(GLfloat*)malloc(sizeof(GLfloat)*v_size*2);
            GLfloat* e_id=(GLfloat*)malloc(sizeof(GLfloat)*v_size);
            GLfloat* face_index_marked=(GLfloat*)malloc(sizeof(GLfloat)*v_size);
            memset(texcoords,0,sizeof(GLfloat)*v_size*2);
            memset(colors,0,sizeof(GLfloat)*v_size*4);
            memset(normal,0,sizeof(GLfloat)*v_size*3);
            memset(e_id,0,sizeof(GLfloat)*v_size);
            memset(face_index_marked,0,sizeof(GLfloat)*v_size);
            temp_i=0;v_size=0;
            for(unsigned int i=0;i<mf->Data_index_rows;i++)
            {
                int j=mf->Data_index[temp_i];
                for(int l=0;l<(j-2);l++)
                {
                    int k;
                    k=mf->Data_index[temp_i+1];
                    e_id[v_size]=elements_id;face_index_marked[v_size]=0;
                    vertices[v_size*3+0]=mf->Data[k*3+0];vertices[v_size*3+1]=mf->Data[k*3+1];vertices[v_size*3+2]=mf->Data[k*3+2];
                    v_size++;

                    k=mf->Data_index[temp_i+1+l+1];
                    e_id[v_size]=elements_id;face_index_marked[v_size]=1;
                    vertices[v_size*3+0]=mf->Data[k*3+0];vertices[v_size*3+1]=mf->Data[k*3+1];vertices[v_size*3+2]=mf->Data[k*3+2];
                    v_size++;

                    k=mf->Data_index[temp_i+1+l+2];
                    e_id[v_size]=elements_id;face_index_marked[v_size]=2;
                    vertices[v_size*3+0]=mf->Data[k*3+0];vertices[v_size*3+1]=mf->Data[k*3+1];vertices[v_size*3+2]=mf->Data[k*3+2];
                    v_size++; 

                }
                temp_i+=(j+1);            
                elements_id++;
            }

            //color
            if(mf->color!=0)
            {
                temp_i=0;v_size=0;
                if(mf->color_rows==mf->Data_index_rows)
                {
                    for(unsigned int i=0;i<mf->Data_index_rows;i++)
                    {
                        int j=mf->Data_index[temp_i];
                        for(int l=0;l<(j-2)*3;l++)
                        {
                    
                            for(int k=0;k<4;k++)
                            {
                    
                                colors[v_size*4+k]=mf->color[i*4+k];
                            }
                            v_size++;
                        }
                        temp_i+=(j+1);                   
                    } 
   
                }
                else if(mf->color_rows==mf->Data_rows)
                {
                    for(unsigned int i=0;i<mf->Data_index_rows;i++)
                    {
                        int j=mf->Data_index[temp_i];
                        for(int l=0;l<(j-2);l++)
                        {
                    
                            int temp_in=mf->Data_index[temp_i+1];
                            for(int k=0;k<4;k++)
                            {
                                colors[v_size*4+k]=mf->color[temp_in*4+k];
                            }
                            v_size++;
                            temp_in=mf->Data_index[temp_i+1+l+1];
                            for(int k=0;k<4;k++)
                            {
                                colors[v_size*4+k]=mf->color[temp_in*4+k];
                            }

                            v_size++;
                            temp_in=mf->Data_index[temp_i+1+l+2];
                            for(int k=0;k<4;k++)
                            {
                                colors[v_size*4+k]=mf->color[temp_in*4+k];
                            }

                            v_size++;
                        }
                        temp_i+=(j+1);                   
                    } 
 
                }
            }

            //texture
            if(mf->texture!=NULL)
            {

                //add_texture_to_shader(value_t,mf->texture->image_file); 
                //moi->node=node_overlying(moi->node,(void*)value_t);
                Viewer_Texture* mt=(Viewer_Texture*)(mf->texture->evolution);
                if(mt->each_face_texture_coord!=0)
                {
                    temp_i=0;v_size=0;

                    for(unsigned int i=0;i<mf->Data_index_rows;i++)
                    {
                        int j=mt->each_face_texture_coord[temp_i];
                        for(int l=0;l<(j-2);l++)
                        {
                            texcoords[v_size*2+0]=mt->each_face_texture_coord[temp_i+1+0];
                            texcoords[v_size*2+1]=mt->each_face_texture_coord[temp_i+1+1];
                        
                            v_size++;
                            texcoords[v_size*2+0]=mt->each_face_texture_coord[temp_i+1+2*(l+1)+0];
                            texcoords[v_size*2+1]=mt->each_face_texture_coord[temp_i+1+2*(l+1)+1];
                            v_size++;
                            texcoords[v_size*2+0]=mt->each_face_texture_coord[temp_i+1+2*(l+2)+0];
                            texcoords[v_size*2+1]=mt->each_face_texture_coord[temp_i+1+2*(l+2)+1];
                            v_size++;
                        } 
                        temp_i+=(j*2+1);                   
                    }
                }

            }
            //normal
            if(mf->normal!=0)
            {
                temp_i=0;v_size=0;
                if(mf->normal_rows==mf->Data_index_rows)
                {
                    for(unsigned int i=0;i<mf->Data_index_rows;i++)
                    {
                        int j=mf->Data_index[temp_i];
                        for(int l=0;l<(j-2)*3;l++)
                        {
                    
                            for(int k=0;k<3;k++)
                            {
                    		    if(mf->is_reversal_normal==1)
				                {normal[v_size*3+k]=-mf->normal[i*3+k];
				                }
				                else
				                {normal[v_size*3+k]=mf->normal[i*3+k];}
                                
                            }
                            v_size++;
                        }
                        temp_i+=(j+1);                   
                    }  
                }
                else if(mf->normal_rows==mf->Data_rows)
                {
                    for(unsigned int i=0;i<mf->Data_index_rows;i++)
                    {
                        int j=mf->Data_index[temp_i];
                        for(int l=0;l<(j-2);l++)
                        {
                    
                            int temp_in=mf->Data_index[temp_i+1];
                            for(int k=0;k<3;k++)
                            {
				                if(mf->is_reversal_normal==1)
				                { normal[v_size*3+k]=-mf->normal[temp_in*3+k];}
				                else{ normal[v_size*3+k]=mf->normal[temp_in*3+k];}
                               
                            }
                            v_size++;
                            temp_in=mf->Data_index[temp_i+1+l+1];
                            for(int k=0;k<3;k++)
                            {
				                if(mf->is_reversal_normal==1){normal[v_size*3+k]=-mf->normal[temp_in*3+k];}
				                else{normal[v_size*3+k]=mf->normal[temp_in*3+k];}
                                
                            }

                            v_size++;
                            temp_in=mf->Data_index[temp_i+1+l+2];
                            for(int k=0;k<3;k++)
                            {
				                if(mf->is_reversal_normal==1){normal[v_size*3+k]=-mf->normal[temp_in*3+k];}
				                else{normal[v_size*3+k]=mf->normal[temp_in*3+k];}
                                
                            }

                            v_size++;
                        }
                        temp_i+=(j+1);                   
                    } 
 
                } 
            }

            glDeleteBuffers(1,mf->Buffers);
            glDeleteVertexArrays(1,&(mf->VAO));
            glGenVertexArrays(1,&(mf->VAO));
            glBindVertexArray(mf->VAO);
            glCreateBuffers(6,mf->Buffers);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[0]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*3,vertices,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[1]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*4,colors,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[2]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*2,texcoords,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[3]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size*3,normal,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[4]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size,e_id,GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[5]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*v_size,face_index_marked,GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[0]);
            glVertexAttribPointer( 0, 3, GL_FLOAT,GL_FALSE, 0, 0 );
            
            glEnableVertexAttribArray( 0 );
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[1]);
            glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[2]);
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[3]);
            glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[4]);
            glVertexAttribPointer(4,1,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(4);

            glBindBuffer(GL_ARRAY_BUFFER,mf->Buffers[5]);
            glVertexAttribPointer(5,1,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(5);

            glBindVertexArray(0);
 
            free(vertices);
            free(colors);
            free(normal);
            free(texcoords);
            free(e_id);
            free(face_index_marked);
        
        }
        free(iter1);   
    }
    free_node_value(names_id);
    free_node(names_id);

   // printf("elements_id:%d\n",elements_id);
	Viewer_default_init_uniform(voisp);


}

static void Viewer_Interpreter_update_data(Viewer_Opengl_Interpreter* voi)
{
    for(Node* it=voi->user_shader_program;it!=NULL;it=(Node*)(it->Next))
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
    char* p_v=(char*)malloc(sizeof(char)*60);
    memset(p_v,0,sizeof(char)*60);
    strcat(strcat(p_v,MESH_VIEWER_PATH),"/mesh.vert");
    char* p_f=(char*)malloc(sizeof(char)*60);
    memset(p_f,0,sizeof(char)*60);
    strcat(strcat(p_f,MESH_VIEWER_PATH),"/mesh.frag");
    moi->create_shader_program(moi,p_v,p_f,Viewer_default_load_data,Viewer_default_render);
    free(p_v);free(p_f);
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
	voisp->voi=NULL;
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
    GLFWwindow* window=glfwCreateWindow(800,600,"Viewer1.0",NULL,NULL);
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
		glClearColor(mw->background_color[0],mw->background_color[1],mw->background_color[2],mw->background_color[3]);
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
