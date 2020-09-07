#include<Viewer_World_Manager/Interactor_GlobalInfo.h>

void GlobalInfo_init(Interactor_GlobalInfo *ginf)
{
	ginf->prop=NULL;
	ginf->window=NULL;
	ginf->pick_something=NULL;
	ginf->mouse_coord=(float*)malloc(sizeof(float)*2);
	ginf->resolution=(int*)malloc(sizeof(int)*2); 
	ginf->resolution[0]=800;
	ginf->resolution[1]=600;
	ginf->readpixelcolor=(unsigned char*)malloc(sizeof(unsigned char)*36);
	for(int i=0;i<36;i++)
	{
		ginf->readpixelcolor[i]=0;
	}
	ginf->key_action=0;
	ginf->mouse_action=0;
	ginf->drop_count=0;
	ginf->paths=NULL;
}
void Viewer_Intera_init(Viewer_Intera* m_v_i)
{
	m_v_i->state=-1;
	m_v_i->prop=NULL;
	m_v_i->representation=NULL;
	m_v_i->g_info=NULL;
	m_v_i->compute_state=Viewer_Intera_default_compute_state;
	m_v_i->cursor_position_callback=NULL;
	m_v_i->mouse_button_callback=NULL;
	m_v_i->framebuffer_size_callback=NULL;
	m_v_i->key_callback=NULL;
	m_v_i->scroll_callback=NULL;
	m_v_i->animation=NULL;
	m_v_i->drop_callback=NULL;
}
int Viewer_Intera_default_compute_state(Viewer_Intera* mi)
{
	mi->state=-1;
	return mi->state;
}
