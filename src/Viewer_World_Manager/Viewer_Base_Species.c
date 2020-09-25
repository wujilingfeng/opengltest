#include<Viewer_World_Manager/Viewer_Base_Species.h>
#include<time.h>
#define Matrix4x4 Viewer_Matrix4x4_

#define out_product LB_three_out_product
static void Viewer_set_v_one_color(float *v,unsigned int rows,float *c)
{

	for(unsigned int i=0;i<rows;i++)
	{
		for(int j=0;j<4;j++)
		{
			v[i*4+j]=c[j];
		}
	}
}
void Viewer_Something_init(Viewer_Something*ms)
{
	//gldeletevertexarray
	//gldeletebuffer
	time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); //取得当地时间
  //  printf ("%d%d%d ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
 //   printf("%d:%d:%d\n", p->tm_hour, p->tm_min, p->tm_sec);
    ms->create_date=p->tm_sec+p->tm_min*100+p->tm_hour*10000+p->tm_mday*1000000+(1+p->tm_mon)*100000000;
   // printf("create_date:%d\n",ms->create_date);
	ms->name=0;
	ms->name_id=-1;
	ms->id=-1;
	//ms->create_date=-1;
	ms->disappear=0;
	memset(ms->viewport,0,sizeof(int)*4);
	ms->marked_element=-1;
	ms->mesh=NULL;
	//ms->history_avatar=NULL;
	ms->evolution=0;
	ms->prop=NULL;
}

void Viewer_Texture_init(Viewer_Texture*mt)
{

	mt->image_file=NULL;
	mt->width=0;
	mt->height=0;
	mt->n=0;
	mt->data=NULL;
	mt->each_face_texture_coord=0;
	mt->tex=0;
	mt->prop=NULL;

}
void Viewer_Faces_set_color(Viewer_Faces*mf,float*c)
{

	if(mf->color!=NULL)
	{free(mf->color);
	}
	mf->color=0;
	if(mf->color_rows>0)
	{
		mf->color=(float*)malloc(sizeof(float)*4*mf->color_rows);
	}
	Viewer_set_v_one_color(mf->color,mf->color_rows,c);

}
void Viewer_Faces_random_color(Viewer_Faces*mf)
{
  
    if(mf->color_rows<=NULL)
    {
        return;
    }
    if(mf->color!=0)
    {
        free(mf->color);mf->color=0;
    }
    mf->color=(float*)malloc(sizeof(float)*4*mf->color_rows);
    srand((unsigned)time(NULL));
    for(unsigned int i=0;i<mf->color_rows*4;i++)
    {
        mf->color[i]=(rand()%100)/100.0;
    }

}
static void Viewer_Edges_random_color(Viewer_Edges*me)
{
	if(me->color_rows<=0)
	{
		return ;
	}	
	if(me->color!=NULL)
	{
		free(me->color);me->color=NULL;
	}
	me->color=(float*)malloc(sizeof(float)*4*me->color_rows);
	srand((unsigned)time(NULL));
	for(unsigned int i=0;i<me->color_rows*4;i++)
	{
		me->color[i]=(rand()%100)/100.0;	
	}	
}
void Viewer_Faces_compute_normal(Viewer_Faces*mf)
{
	if(mf->normal_rows<=0)
	{
		return;
	}
	if(mf->normal!=0)
	{free(mf->normal);mf->normal=0;}
	if(mf->normal_rows==mf->Data_index_rows)
	{
		
		double *re=0;double a[3],b[3];
		mf->normal=(float*)malloc(sizeof(float)*3*mf->Data_index_rows);
        memset(mf->normal,0,sizeof(float)*3*mf->Data_index_rows);
		int temp_i=0,v_size=0;
		for(unsigned int i=0;i<mf->Data_index_rows;i++)
		{
			int i1=mf->Data_index[temp_i+1];
			int i2=mf->Data_index[temp_i+2];
			int i3=mf->Data_index[temp_i+3];
			for(int j=0;j<3;j++)
			{
                a[j]=mf->Data[i3*3+j]-mf->Data[i1*3+j];
                b[j]=mf->Data[i2*3+j]-mf->Data[i1*3+j];
			}
            re=out_product(b,a);
            for(int j=0;j<3;j++)
            {
                mf->normal[v_size*3+j]=re[j];
               
            }
			temp_i+=(mf->Data_index[temp_i]+1);
            v_size++;
            free(re);
            re=0;
		}
		
		
	}
	else if(mf->normal_rows==mf->Data_rows)
	{
		mf->normal=(float*)malloc(sizeof(float)*3*mf->normal_rows);
        memset(mf->normal,0,sizeof(float)*3*mf->normal_rows);

    	double *re=0;double a[3],b[3];
		int temp_i=0;
		for(unsigned int i=0;i<mf->Data_index_rows;i++)
		{
			int i1=mf->Data_index[temp_i+1];
			int i2=mf->Data_index[temp_i+2];
			int i3=mf->Data_index[temp_i+3];
			for(int j=0;j<3;j++)
			{
                a[j]=mf->Data[i3*3+j]-mf->Data[i1*3+j];
                b[j]=mf->Data[i2*3+j]-mf->Data[i1*3+j];
			}
            re=out_product(b,a);

		for(int l=0;l<mf->Data_index[temp_i];l++)
		{
			for(int j=0;j<3;j++)
            		{
                		mf->normal[mf->Data_index[temp_i+1+l]*3+j]+=re[j];
            		}
			
		}
            
			temp_i+=(mf->Data_index[temp_i]+1);
            free(re);
            re=0;
		}
		
		
	}


}
void Viewer_Faces_init(Viewer_Faces* mf)
{
    mf->Data=0;mf->color=0;
    mf->Data_index=0;
    mf->normal=0;
    mf->VAO=0;mf->Buffers=0;
    mf->marked_faces_index=0;
   
    mf->evolution=0;
    mf->Data_index_rows=0;
  	mf->color_rows=0;
	mf->normal_rows=0;
    mf->Data_rows=0;
	mf->compute_normal=Viewer_Faces_compute_normal;
    mf->random_color=Viewer_Faces_random_color;
	mf->set_color=Viewer_Faces_set_color;
	mf->texture=0;
	mf->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
	Matrix4x4_init_float(mf->mat);
	mf->is_reversal_normal=0;
	mf->is_transparent=0;
 	mf->prop=NULL;
   // mf->texture=(Mesh_viewer_texture*)malloc(sizeof(Mesh_viewer_texture));
   // Mesh_viewer_texture_init(mf->texture);

}

void Viewer_Camera_init(Viewer_Camera*mc)
{
    mc->matrix=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(mc->matrix); 
    mc->matrix_inverse=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(mc->matrix_inverse);
	mc->Proj=(Matrix4x4*)malloc(sizeof(Matrix4x4));
	Matrix4x4_init_float(mc->Proj);
    mc->prop=0;
    mc->is_using=0;
    mc->focal_distance=1;

}
static void Viewer_Points_random_color(struct Viewer_Points* mp)
{
    if(mp->color_rows<=0)
    {
        return ;
    }   
    if(mp->color!=NULL)
    {
        free(mp->color);mp->color=NULL;
    }
    mp->color=(float*)malloc(sizeof(float)*4*mp->color_rows);
    srand((unsigned)time(NULL));
    for(unsigned int i=0;i<mp->color_rows*4;i++)
    {
        mp->color[i]=(rand()%100)/100.0;    
    }   
}
/*static void Viewer_Points_mset_color(struct Viewer_Points*mp,float*c)
{
    if(mp->color!=NULL)
    {free(mp->color);mp->color=NULL;
    }
    if(mp->color_rows>0)
    {
        mp->color=(float*)malloc(sizeof(float)*4*mp->color_rows);
    }
    Viewer_set_v_one_color(mp->color,mp->color_rows,c);
}*/
static void Viewer_Points_set_color(Viewer_Points*vp,float*c)
{

    if(vp->color!=0)
    {free(vp->color);
    }
    vp->color=NULL;
    if(vp->color_rows>0)
    {
        vp->color=(float*)malloc(sizeof(float)*4*vp->color_rows);
    }
    Viewer_set_v_one_color(vp->color,vp->color_rows,c);

}
void Viewer_Points_init(struct Viewer_Points* mp)
{
    mp->Data=0;mp->color=NULL;
    
    mp->VAO=0;
    mp->Buffers=NULL;
    mp->prop=NULL;
    mp->evolution=NULL;
    mp->set_color=Viewer_Points_set_color;
    mp->random_color=Viewer_Points_random_color;
    mp->Data_rows=0; mp->color_rows=0;
	mp->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(mp->mat);
	mp->pointsize=3.0;
	
}

void Viewer_Edges_init(struct Viewer_Edges* me)
{
    me->Data=NULL;me->color=0;
    me->Data_index=0;
    me->VAO=0;
    me->Buffers=0;
    me->prop=0;
    me->evolution=0;
    me->Data_index_rows=0;
    me->Data_rows=0;
	me->color_rows=0;
	me->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
	me->set_color=Viewer_Edges_set_color;
	me->random_color=Viewer_Edges_random_color;
Matrix4x4_init_float(me->mat);
	me->edgesize=2.0;
}
void Viewer_Edges_set_color(Viewer_Edges*me,float*v)
{
	if(me->color!=0)
	{free(me->color);
	}
	me->color=0;
	if(me->color_rows>0)
	{
		me->color=(float*)malloc(sizeof(float)*4*me->color_rows);
	}
	Viewer_set_v_one_color(me->color,me->color_rows,v);
}
#undef out_product
#undef Matrix4x4
