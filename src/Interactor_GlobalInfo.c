#include<Mesh_view/Interactor_GlobalInfo.h>

void GlobalInfo_init(Interactor_GlobalInfo *ginf)
{
	ginf->prop=0;
	ginf->window=0;
	ginf->mouse_coord=(float*)malloc(sizeof(float)*2);
	ginf->resolution=(int*)malloc(sizeof(int)*2); 
	ginf->readpixelcolor=(unsigned char*)malloc(sizeof(unsigned char)*36);
	for(int i=0;i<36;i++)
	{
		ginf->readpixelcolor[i]=0;
	}


}
void Mesh_viewer_Intera_init(Mesh_viewer_Intera* m_v_i)
{
	m_v_i->state=-1;
	m_v_i->prop=0;
	m_v_i->representation=0;
	m_v_i->g_info=0;
	m_v_i->compute_state=Mesh_viewer_Intera_default_compute_state;
	m_v_i->cursor_position_callback=0;
	m_v_i->mouse_button_callback=0;
	m_v_i->framebuffer_size_callback=0;
	m_v_i->key_callback=0;
	m_v_i->scroll_callback=0;
	m_v_i->animation=0;
}
int Mesh_viewer_Intera_default_compute_state(Mesh_viewer_Intera* mi)
{


	mi->state=-1;
	return mi->state;
}
