#include<Mesh_Viewer_World_Manager/Mesh_viewer_base_species.h>
void Mesh_viewer_texture_init(Mesh_viewer_texture*mt)
{

	mt->image_file=0;
	mt->width=0;
	mt->height=0;
	mt->n=0;
	mt->data=0;
	mt->each_face_texture_coord=0;
	mt->prop=0;

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
  
    mf->Data_rows=0;
    mf->texture=(Mesh_viewer_texture*)malloc(sizeof(Mesh_viewer_texture));
    Mesh_viewer_texture_init(mf->texture);

}

void Mesh_viewer_camera_init(Mesh_viewer_camera*mc)
{
    mc->matrix=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(mc->matrix); 
    mc->matrix_inverse=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(mc->matrix_inverse);
    mc->prop=0;
    mc->is_using=0;
    mc->focal_distance=1;

}
void Mesh_viewer_points_init(struct Mesh_viewer_points* mp)
{
    mp->Data=0;mp->color=0;
    mp->Data_index=0;
    mp->VAO=0;
    mp->Buffers=0;
    mp->prop=0;
    mp->evolution=0;
    mp->Data_index_rows=0;
    mp->Data_rows=0;

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

}


