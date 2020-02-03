#ifndef INTERACTOR_GLOBALINFO
#define INTERACTOR_GLOBALINFO
#include <tool/tools_node.h>
#define MESH_VIEWER_MOUSE_BUTTON_LEFT 0
#define MESH_VIEWER_MOUSE_BUTTON_RIGHT 1
#define MESH_VIEWER_MOUSE_BUTTON_MIDDLE 2
#define MESH_VIEWER_PRESS 1
#define MESH_VIEWER_RELEASE 0
#define MESH_VIEWER_REPEAT 2
#define MESH_VIEWER_MOD_SHIFT 1
#define MESH_VIEWER_MOD_CONTROL 2
#define MESH_VIEWER_MOD_ALT 4
#define MESH_VIEWER_MOD_SUPER 8
#define MESH_VIEWER_KEY_CONTROL 341
#define MESH_VIEWER_KEY_ALT 342

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Interactor_GlobalInfo{
	float run_time;
	float *mouse_coord;
	int *resolution;
	int button;
	int mouse_action;
	int key;
	int key_action;
	int key_mods;
	int mouse_mods;
	unsigned char *readpixelcolor;
	void* window;
	void* pick_something;
	void *prop;
	
	
}Interactor_GlobalInfo;
void GlobalInfo_init(Interactor_GlobalInfo* ginf);
typedef struct Mesh_viewer_Intera
{
	int state;
	Interactor_GlobalInfo* g_info;
	int (*compute_state)(struct Mesh_viewer_Intera* );
	void(*cursor_position_callback)(struct Mesh_viewer_Intera*);
	void(*mouse_button_callback)(struct Mesh_viewer_Intera*);
	void(*framebuffer_size_callback)(struct Mesh_viewer_Intera*);
	void(*key_callback)(struct Mesh_viewer_Intera*);
	void(*scroll_callback)(struct Mesh_viewer_Intera*,double,double);
	void (*animation)(struct Mesh_viewer_Intera*);
	void *prop;
	void *representation;
}Mesh_viewer_Intera;
int Mesh_viewer_Intera_default_compute_state(Mesh_viewer_Intera*);
void Mesh_viewer_Intera_init(Mesh_viewer_Intera*);

#ifdef __cplusplus
}
#endif
#endif
