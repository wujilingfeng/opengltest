#include "include/Arcroll.h" 
void Mesh_viewer_Arcroll_init(Mesh_viewer_Arcroll*ma)
{
    ma->old_mouse_coord=(float*)malloc(sizeof(float)*2);

}
void Mesh_viewer_Arcroll_cursor_position_callback(Mesh_viewer_Intera* mi)
{
    Interactor_GlobalInfo* g_info=mi->g_info;
    Mesh_viewer_Arcroll* ma=(Mesh_viewer_Arcroll*)(mi->representation);

    Mesh_viewer_camera* mc=(Mesh_viewer_camera*)(mi->prop);
    if(g_info->button==MESH_VIEWER_MOUSE_BUTTON_LEFT&&g_info->mouse_action==MESH_VIEWER_PRESS)
    {
        float tempx=g_info->mouse_coord[0]-ma->old_mouse_coord[0];
        float tempy=g_info->mouse_coord[1]-ma->old_mouse_coord[1];
        tempx=-tempx*0.005;tempy=tempy*0.005;
        Matrix4x4 *temp_m=(Matrix4x4*)malloc(sizeof(Matrix4x4));
        Matrix4x4_init_float(temp_m);
        Matrix4x4 *MV=(Matrix4x4*)malloc(sizeof(Matrix4x4));
        Matrix4x4_init_float(MV);
        float* data=(float*)(MV->data);
        data[2*4+3]=mc->focal_distance;
        Matrix4x4 *MV_inverse=MV->inverse(MV);
        data=(float*)(temp_m->data);
        data[0*4+0]=cos(tempx);data[0*4+1]=-sin(tempx)*sin(tempy);
        data[0*4+2]=sin(tempx)*cos(tempy);
        data[1*4+1]=cos(tempy);
        data[1*4+2]=sin(tempy);
        data[2*4+0]=-sin(tempx);
        data[2*4+1]=-cos(tempx)*sin(tempy);
        data[2*4+2]=cos(tempx)*cos(tempy);
        MV->mult(MV,temp_m);
        MV->mult(MV,MV_inverse);
        MV->mult(MV,mc->matrix_inverse);
        mc->matrix_inverse->copy_data(mc->matrix_inverse,MV);
        Matrix4x4_free(mc->matrix);
        mc->matrix=mc->matrix_inverse->inverse(mc->matrix_inverse);
        Matrix4x4_free(temp_m);
        Matrix4x4_free(MV);
        Matrix4x4_free(MV_inverse);
    }
    ma->old_mouse_coord[0]=g_info->mouse_coord[0];
    ma->old_mouse_coord[1]=g_info->mouse_coord[1];


}
void Mesh_viewer_Arcroll_scroll_callback(Mesh_viewer_Intera*mi,double x,double y)
{
    Interactor_GlobalInfo* g_info=mi->g_info;

    Mesh_viewer_camera* mc=(Mesh_viewer_camera*)(mi->prop);

    //printf("scroll key_mods:%d ,key_action:%d\n",g_info->key_mods,g_info->key_action);
    if((g_info->key==MESH_VIEWER_KEY_CONTROL&&g_info->key_action==1))
    {
         mc->focal_distance+=(float)y*0.05;

    }
    else
    {
        float *data=(float*)(mc->matrix_inverse->data);
        data[2*4+3]+=(float)y*0.05;

    }
}
