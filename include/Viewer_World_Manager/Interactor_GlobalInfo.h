#ifndef INTERACTOR_GLOBALINFO_H
#define INTERACTOR_GLOBALINFO_H
#include <tools_node.h>
#define VIEWER_ARROW_CURSOR 0x00036001
#define VIEWER_IBEAM_CURSOR   0x00036002
#define VIEWER_CROSSHAIR_CURSOR   0x00036003
#define VIEWER_HAND_CURSOR   0x00036004
#define VIEWER_HRESIZE_CURSOR   0x00036005
#define VIEWER_VRESIZE_CURSOR   0x00036006

#define VIEWER_MOUSE_BUTTON_LEFT 0
#define VIEWER_MOUSE_BUTTON_RIGHT 1
#define VIEWER_MOUSE_BUTTON_MIDDLE 2
#define VIEWER_PRESS 1
#define VIEWER_RELEASE 0
#define VIEWER_REPEAT 2
#define VIEWER_MOD_SHIFT 1
#define VIEWER_MOD_CONTROL 2
#define VIEWER_MOD_ALT 4
#define VIEWER_MOD_SUPER 8
#define VIEWER_KEY_CONTROL 341
#define VIEWER_KEY_ALT 342
#define VIEWER_KEY_0 48
#define VIEWER_KEY_9 57
#define VIEWER_KEY_A 65
#define VIEWER_KEY_B 66
#define VIEWER_KEY_Z 90

#ifdef __cplusplus
extern "C" {
#endif
typedef struct Interactor_GlobalInfo{
	float run_time;
	float *mouse_coord;
	int *resolution;
	int mouse_button;
	int mouse_action;
	int key;
	int key_action;
	int key_mods;
	int mouse_mods;
	unsigned char *readpixelcolor;
	void* pick_something;
	int drop_count;
	char** paths;
	void *prop;
	void* window;//为glfw的window提供
}Interactor_GlobalInfo;
void GlobalInfo_init(Interactor_GlobalInfo* ginf);
typedef struct Viewer_Intera
{
//state可以用来覆盖信号，当信号是负的时候这个交互器不会覆盖别的交互器
	int state;
	Interactor_GlobalInfo* g_info;
	int (*compute_state)(struct Viewer_Intera* );
	void(*cursor_position_callback)(struct Viewer_Intera*);
	void(*mouse_button_callback)(struct Viewer_Intera*);
	void(*framebuffer_size_callback)(struct Viewer_Intera*);
	void(*key_callback)(struct Viewer_Intera*);
	void(*scroll_callback)(struct Viewer_Intera*,double,double);
	void (*drop_callback)(struct Viewer_Intera*);
	void (*animation)(struct Viewer_Intera*);
	void *representation;
	void *prop;//一般上面的representation就足够提供扩展了
	
}Viewer_Intera;
int Viewer_Intera_default_compute_state(Viewer_Intera*);
void Viewer_Intera_init(Viewer_Intera*);

#ifdef __cplusplus
}
#endif
#endif
