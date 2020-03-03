#include<Mesh_Viewer_World_Manager/Mesh_viewer_manager.h>
//以算子的思想做回退功能
//glDeleteVertexArrays;
//glDeleteBuffers
/*void Mesh_viewer_world_registe1(Mesh_viewer_world*m,char**c,int size)
{
	for(int i=0;i<size;i++)
	{
		int species_id=m->species_id++;
		int le=strlen(c[i]);
		char *cp=(char*)malloc(sizeof(char)*(le+1));
		cp[le]='\0';
		strcpy(cp,c[i]);
		m->something_id[species_id]=0;
		m->species_name_registe[species_id]=cp;
		m->species[species_id]=NULL;
	}

}*/
//返回registe id
Node* Mesh_viewer_world_registe(Mesh_viewer_world*m,char*c)
{
	if(c==0)
	{return 0;}
	if(c[0]=='\0')
	{return 0;}
	Node* re=0;
	int i=0,j=0;
	while(c[i]!='\0')
	{

		while(c[j]!=','&&c[j]!='\0')
		{
			//printf("%d ",j);
			j++;

		}
		char* temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		temp_c[j-i]='\0';
		for(int k=0;k<j-i;k++)
		{
			temp_c[k]=c[i+k];

		}
		Node* id=Mesh_viewer_world_find_species(m,temp_c);
		if(id==0)
		{break;}
		else if(*((int*)(id->value))!=-1)
		{
			free(temp_c);
			re=node_overlying(re,id->value);
		}
		else
		{
			int species_id=m->species_id++;
			m->something_id[species_id]=0;
			m->species_name_registe[species_id]=temp_c;
            std::map<int,Mesh_viewer_something*> *s_map=new std::map<int,Mesh_viewer_something*>;
			m->species2somethings[species_id]=s_map;
			int *temp_id=(int*)malloc(sizeof(int));
			*temp_id=species_id;
			re=node_overlying(re,(void*)temp_id);
			free(id->value);
		}
		free_node(id);
		if(c[j]=='\0')
		{
			break;
		}
		i=j+1;
		j=j+1;
	}
    //Mesh_viewer_world_printself(m);

	return node_reverse(re);
}
void Mesh_viewer_world_init(Mesh_viewer_world*m)
{
	//m->things_id=0;
	//char str[]="points,edges,faces";
	m->species_id=0;
	char str[]="points,edges,faces,Intera,Camera";
	Node* node=Mesh_viewer_world_registe(m,str);
    m->g_info=(Interactor_GlobalInfo*)malloc(sizeof(Interactor_GlobalInfo));
    GlobalInfo_init(m->g_info);
    m->prop=0;
    m->prop1=0;
    node=node_reverse(node);
    free_node_value(node);
    free_node(node);
    m->create_something=Mesh_viewer_world_create_something;
    m->remove_something=Mesh_viewer_world_remove_something;
    m->print_self=Mesh_viewer_world_printself;
    m->find_species=Mesh_viewer_world_find_species;
    m->registe=Mesh_viewer_world_registe;

}
void Mesh_viewer_world_printself(Mesh_viewer_world*mw)
{
   for(auto iter=mw->species2somethings.begin();iter!=mw->species2somethings.end();iter++)
   {
       printf("name_id:%d\n",iter->first);
       std::map<int,Mesh_viewer_something*>* temp=iter->second;
       for(auto iter1=temp->begin();iter1!=temp->end();iter1++)
       {
            printf("name:%s,id: %d,create_time:%u\n",iter1->second->name,iter1->second->id,iter1->second->create_date);
       }
   
   }


}
//返回寻找的id -1是没找到
Node* Mesh_viewer_world_find_species(Mesh_viewer_world*mw,char* c)
{
	if(c==0)
	{
		return 0;
	}
	if(c[0]=='\0')
	{return 0;}
	//int num=0;
	Node * re=0;
	int i=0,j=0;
	while(c[i]!='\0')
	{

		while(c[j]!=','&&c[j]!='\0')
		{
			//printf("%d ",j);
			j++;

		}
		char *temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		//char* temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		temp_c[j-i]='\0';
		for(int k=0;k<j-i;k++)
		{
			temp_c[k]=c[i+k];

		}
		int* id=(int *)malloc(sizeof(int));
		*id=-1;
		for(auto it=mw->species_name_registe.begin();it!=mw->species_name_registe.end();it++)
		{
			if(strcmp(temp_c,it->second)==0)
			{
				*id=it->first;
				break;

			}
		}
		re=node_overlying(re,(void*)id);
		
        free(temp_c);
		if(c[j]=='\0')
		{
			break;
		}
		i=j+1;
		j=j+1;
	}
	
	return node_reverse(re);
}

Node* Mesh_viewer_world_create_something(struct Mesh_viewer_world*mw,char *c)
{
	Node* id_list=Mesh_viewer_world_registe(mw,c),*re=0;
	Node* iter_n=id_list;
	if(id_list==0)
	{return 0;}
	int i=0,j=0;
	while(c[i]!='\0')
	{

		while(c[j]!=','&&c[j]!='\0')
		{
			//printf("%d ",j);
			j++;

		}
		char* temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		temp_c[j-i]='\0';
		for(int k=0;k<j-i;k++)
		{
			temp_c[k]=c[i+k];

		}
		Mesh_viewer_something* ms=(Mesh_viewer_something*)malloc(sizeof(Mesh_viewer_something));
		Mesh_viewer_something_init(ms);
		ms->name=temp_c;
		ms->name_id=*((int*)iter_n->value);
		free(iter_n->value);
		ms->id=mw->something_id[ms->name_id]++;
        (*(mw->species2somethings[ms->name_id]))[ms->id]=ms;
		re=node_overlying(re,(void*)ms);
		if(c[j]=='\0')
		{
			break;
		}
		iter_n=(Node*)iter_n->Prev;
		
		i=j+1;
		j=j+1;
	}

    id_list=node_reverse(id_list);
	free_node(id_list);
    re=node_reverse(re);
	Node* temp_node=Mesh_viewer_from_something_evolute(re,mw);
	free_node(node_reverse(temp_node));
	return re;

}
//
Node* Mesh_viewer_from_something_evolute(Node*lis,struct Mesh_viewer_world* mw)
{
	Node* re=0;
	if(lis==0)
	{
		return re;
	}
	if(lis->value==0)
	{
		return re;
	}
	Node* iter=lis;
	while(iter!=0)
	{
		Mesh_viewer_something* ms=(Mesh_viewer_something*)iter->value;
		void *value=0;
		if(strcmp(ms->name,"points")==0)
		{
			Mesh_viewer_points* temp_e=(Mesh_viewer_points*)malloc(sizeof(Mesh_viewer_points));
            Mesh_viewer_points_init(temp_e);
			value=(void*)temp_e;
		}
		else if(strcmp(ms->name,"edges")==0)
		{
			Mesh_viewer_edges* temp_e=(Mesh_viewer_edges*)malloc(sizeof(Mesh_viewer_edges));
            Mesh_viewer_edges_init(temp_e);
			value=(void*)temp_e;

		}
		else if(strcmp(ms->name,"faces")==0)
		{

			Mesh_viewer_faces* temp_e=(Mesh_viewer_faces*)malloc(sizeof(Mesh_viewer_faces));
            Mesh_viewer_faces_init(temp_e);
			value=(void*)temp_e;
		}
        else if(strcmp(ms->name,"Intera")==0)
        {  Mesh_viewer_Intera* temp_e=(Mesh_viewer_Intera*)malloc(sizeof(Mesh_viewer_Intera)); 
            Mesh_viewer_Intera_init(temp_e);
            if(mw!=0)
            {
                temp_e->g_info=mw->g_info;
            }
            value=(void*)temp_e;

        }
        else if(strcmp(ms->name,"Camera")==0)
        {
            Mesh_viewer_camera* temp_e=(Mesh_viewer_camera*)malloc(sizeof(Mesh_viewer_camera));
            Mesh_viewer_camera_init(temp_e);
            value=(void*)temp_e;
        
        }
        else if(strcmp(ms->name,"Texture")==0)
        {
            Mesh_viewer_texture*temp_e=(Mesh_viewer_texture*)malloc(sizeof(Mesh_viewer_texture));
            Mesh_viewer_texture_init(temp_e);
            value=(void*)temp_e;
        }
		ms->evolution=value;
		re=node_overlying(re,value);
		iter=(Node*)iter->Prev;
	}
	return node_reverse(re);
}
void Mesh_viewer_world_remove_something(struct Mesh_viewer_world* mw,Mesh_viewer_something* ms)
{
    std::map<int,std::map<int,Mesh_viewer_something*>*>::iterator iter=mw->species2somethings.find(ms->name_id);
    if(iter!=mw->species2somethings.end())
    {
        auto iter1=(iter->second)->find(ms->id);
        if(iter1!=(iter->second)->end())
        {
            iter->second->erase(iter1);
        }
    }


}
/*void Mesh_viewer_add_face_data(Mesh_viewer_faces*mf,float* v,int v_cols,int v_rows,int *index,int i_cols,int i_rows,float *color )
{   if(v!=0&&index!=0)
    {
        mf->Data=(float*)malloc(sizeof(float)*3*i_cols*i_rows);
        mf->Data_index=(unsigned int*)malloc(sizeof(unsigned int)*i_cols*i_rows);
        mf->Data_index_rows=i_rows;
        for(int i=0;i<i_rows;i++)
        {
            for(int j=0;j<i_cols;j++)
            {
                mf->Data_index[i*i_cols+j]=index[i*i_cols+j];
                int temp_i=index[i*i_cols+j];
                for(int k=0;k<3;k++)
                {
                    if(k<v_cols)
                    {
                        Data[(i*i_cols+j)*3+k]=v[temp_i*v_cols+k];
                    }
                        Data[(i*i_cols+j)*3+k]=0;
                
                }
                
            }
        }
    
    }
    if(color!=0)
    {
        mf->color=(float*)malloc(sizeof(float)*3*i_cols*i_rows);

    
    
    }
    
}
*/

