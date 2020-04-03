#include<Mesh_Viewer_World_Manager/Mesh_viewer_base_species.h>
#include<time.h>
static void Viewer_set_v_one_color(float *v,unsigned int rows,float *c)
{

	for(unsigned int i=0;i<rows;i++)
	{
		for(int j=0;j<3;j++)
		{
			v[i*3+j]=c[j];
		}
	}
}
void Mesh_viewer_something_init(Mesh_viewer_something*ms)
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
	ms->prop=0;
	ms->mesh=0;
	ms->history_avatar=0;
	ms->evolution=0;
}

void Mesh_viewer_texture_init(Mesh_viewer_texture*mt)
{

	mt->image_file=0;
	mt->width=0;
	mt->height=0;
	mt->n=0;
	mt->data=0;
	mt->each_face_texture_coord=0;
	mt->tex=0;
	mt->prop=0;

}
void Viewer_faces_set_color(Mesh_viewer_faces*mf,float*c)
{

	if(mf->color!=0)
	{free(mf->color);
	}
	mf->color=0;
	if(mf->color_rows>0)
	{
		mf->color=(float*)malloc(sizeof(float)*3*mf->color_rows);
	}
	Viewer_set_v_one_color(mf->color,mf->color_rows,c);

}
void Mesh_viewer_faces_random_color(Mesh_viewer_faces*mf)
{
  
    if(mf->color_rows<=0)
    {
        return;
    }
    if(mf->color!=0)
    {
        free(mf->color);mf->color=0;
    }
    mf->color=(float*)malloc(sizeof(float)*3*mf->color_rows);
    srand((unsigned)time(NULL));
    for(unsigned int i=0;i<mf->color_rows*3;i++)
    {
        mf->color[i]=(rand()%100)/100.0;
    
    }

}
void Mesh_viewer_faces_compute_normal(Mesh_viewer_faces*mf)
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
            for(int j=0;j<3;j++)
            {
                mf->normal[i1*3+j]+=re[j];
                mf->normal[i2*3+j]+=re[j];
                mf->normal[i3*3+j]+=re[j];
            }
			temp_i+=(mf->Data_index[temp_i]+1);
            free(re);
            re=0;
		}
		
		
	}


}
void Mesh_viewer_faces_init(Mesh_viewer_faces* mf)
{
    mf->Data=0;mf->color=0;
    mf->Data_index=0;
    mf->normal=0;
    mf->VAO=0;mf->Buffers=0;
    mf->marked_faces_index=0;
    mf->prop=0;
    mf->evolution=0;
    mf->Data_index_rows=0;
  	mf->color_rows=0;
	mf->normal_rows=0;
    mf->Data_rows=0;
	mf->compute_normal=Mesh_viewer_faces_compute_normal;
    mf->random_color=Mesh_viewer_faces_random_color;
	mf->set_color=Viewer_faces_set_color;
	mf->texture=0;
	mf->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
	Matrix4x4_init_float(mf->mat);
	mf->is_reversal_normal=0;
   // mf->texture=(Mesh_viewer_texture*)malloc(sizeof(Mesh_viewer_texture));
   // Mesh_viewer_texture_init(mf->texture);

}

void Mesh_viewer_camera_init(Mesh_viewer_camera*mc)
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
void Mesh_viewer_points_init(struct Mesh_viewer_points* mp)
{
    mp->Data=0;mp->color=0;
    
    mp->VAO=0;
    mp->Buffers=0;
    mp->prop=0;
    mp->evolution=0;
    
    mp->Data_rows=0;
	mp->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
Matrix4x4_init_float(mp->mat);
	mp->pointsize=3.0;
	
}
void Mesh_viewer_edges_init(struct Mesh_viewer_edges* me)
{
    me->Data=0;me->color=0;
    me->Data_index=0;
    me->VAO=0;
    me->Buffers=0;
    me->prop=0;
    me->evolution=0;
    me->Data_index_rows=0;
    me->Data_rows=0;
	me->color_rows=0;
	me->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
	me->set_color=Viewer_edges_set_color;
Matrix4x4_init_float(me->mat);
	me->edgesize=2.0;
}
void Viewer_edges_set_color(Mesh_viewer_edges*me,float*v)
{
	if(me->color!=0)
	{free(me->color);
	}
	me->color=0;
	if(me->color_rows>0)
	{
		me->color=(float*)malloc(sizeof(float)*3*me->color_rows);
	}
	Viewer_set_v_one_color(me->color,me->color_rows,v);


}

