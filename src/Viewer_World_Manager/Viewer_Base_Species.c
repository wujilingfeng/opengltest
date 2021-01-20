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
    p = localtime(&timep); 
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
  
    if(mf->color_rows<=0)
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

    mf->triangle_coordinate[0]=1;mf->triangle_coordinate[1]=0;mf->triangle_coordinate[2]=0;   
 	mf->prop=NULL;

    //
    mf->VAO=0;mf->Buffers=NULL;
   // mf->texture=(Mesh_viewer_texture*)malloc(sizeof(Mesh_viewer_texture));
   // Mesh_viewer_texture_init(mf->texture);

}

void Viewer_Camera_init(Viewer_Camera*mc)
{
    mc->matrix=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(mc->matrix); 
    //mc->matrix_inverse=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    //Matrix4x4_init_float(mc->matrix_inverse);
	mc->Proj=(Matrix4x4*)malloc(sizeof(Matrix4x4));
	Matrix4x4_init_float(mc->Proj);
    mc->prop=0;
    mc->is_using=0;
    mc->focal_distance=1;
    float* data=(float*)(mc->matrix->data);
    data[2*4+3]=-5;
    mc->matrix_inverse=mc->matrix->inverse(mc->matrix);


}
static void Viewer_Points_random_color(struct Viewer_Points* mp)
{
    if(mp->Data_rows<=0)
    {
        return ;
    }   
    if(mp->color!=NULL)
    {
        free(mp->color);mp->color=NULL;
    }
    mp->color=(float*)malloc(sizeof(float)*4*mp->Data_rows);
    srand((unsigned)time(NULL));
    for(unsigned int i=0;i<mp->Data_rows*4;i++)
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
    if(vp->Data_rows<=0)
    {
        return ;
    }   
    if(vp->color!=NULL)
    {
        free(vp->color);
        vp->color=NULL;
    }
    if(vp->Data_rows>0)
    {
        vp->color=(float*)malloc(sizeof(float)*4*vp->Data_rows);
    }
    Viewer_set_v_one_color(vp->color,vp->Data_rows,c);

}
void Viewer_Points_init(struct Viewer_Points* mp)
{
    mp->Data=0;mp->color=NULL;
    
   
    mp->prop=NULL;
    mp->evolution=NULL;
    mp->set_color=Viewer_Points_set_color;
    mp->random_color=Viewer_Points_random_color;
    mp->Data_rows=0; 

 //   mp->color_rows=0;
//
	mp->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(mp->mat);
	mp->pointsize=3.0;

    ///
    mp->VAO=0;mp->Buffers=NULL;
	
}

void Viewer_Edges_init(struct Viewer_Edges* me)
{
    me->Data=NULL;me->color=0;
    me->Data_index=0;
   
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
//
     me->VAO=0;  me->Buffers=NULL;
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
void Viewer_Cursor_Shape_init(struct Viewer_Cursor_Shape* vcs)
{
    vcs->shape_name=NULL;
    vcs->image_path=NULL;
    vcs->is_using=0;
    vcs->obj=NULL;
    vcs->prop=NULL;  
}
void Viewer_Texts_init(struct Viewer_Texts*vtext )
{
    vtext->str=NULL;
    vtext->xy[0]=0;vtext->xy[1]=0;
    vtext->scale=1;
   // vtext->color[0]=0;vtext->color[1]=0;vtext->color[2]=0,vtext->color[3]=1;
    vtext->font_path=NULL;
    vtext->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(vtext->mat);
    vtext->Proj=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(vtext->Proj);

    vtext->VAO=0;vtext->VBO[0]=0;vtext->VBO[1]=0;vtext->VBO[2]=0;
    vtext->prop=NULL; 
}
/*特殊的初始化函数*/
void Viewer_Texts_initn(struct Viewer_Texts* vtext,char const *str,float x,float y,float s,float* c,char const *font_path)
{
    //Viewer_Texts_init(vtext);
    int len=strlen(str);
    if(vtext->str!=NULL)
    {
        free(vtext->str);
        vtext->str=NULL;
    }
    if(vtext->font_path!=NULL)
    {
        free(vtext->font_path);
        vtext->font_path=NULL;
    }
    if(vtext->mat==NULL)
    {
        vtext->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
        Matrix4x4_init_float(vtext->mat); 
    }
    if(vtext->Proj==NULL)
    {
        vtext->Proj=(Matrix4x4*)malloc(sizeof(Matrix4x4));
        Matrix4x4_init_float(vtext->Proj); 
    }
    vtext->str=(char*)malloc(sizeof(char)*(len+1));
    memset(vtext->str,0,sizeof(char)*(len+1));
    strcpy(vtext->str,str);
    vtext->xy[0]=x;vtext->xy[1]=y;
    vtext->scale=s;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {

            vtext->colors[i*4+j]=c[j];
        }
    }
    //vtext->color[0]=c[0];vtext->color[1]=c[1];vtext->color[2]=c[2];vtext->color[3]=c[3];
    
    if(font_path!=NULL)
    {
        len=strlen(font_path);
        vtext->font_path=(char*)malloc(sizeof(char)*(len+1));
        memset(vtext->font_path,0,sizeof(char)*(len+1));
        strcpy(vtext->font_path,font_path);
    }
    else
    {
        vtext->font_path=NULL;
    } 
}
void Viewer_UI_Mesh_init(Viewer_UI_Mesh* vum)
{
    vum->Data=0;vum->color=0;
    vum->Data_index=0;

    vum->marked_faces_index=0;
   
    vum->evolution=0;
    vum->Data_index_rows=0;
    vum->color_rows=0;
    vum->Data_rows=0;

    vum->set_color=Viewer_Faces_set_color;
    vum->mat=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(vum->mat);
    vum->Proj=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(vum->Proj);
    vum->prop=NULL;

    vum->texture=NULL;
    vum->VAO=0;vum->Buffers=NULL;
    /*mf->compute_normal=Viewer_Faces_compute_normal;
    mf->random_color=Viewer_Faces_random_color;
    
    mf->is_reversal_normal=0;
    mf->is_transparent=0;

    mf->triangle_coordinate[0]=1;mf->triangle_coordinate[1]=0;mf->triangle_coordinate[2]=0;   
    //
*/
}



#undef out_product
#undef Matrix4x4
