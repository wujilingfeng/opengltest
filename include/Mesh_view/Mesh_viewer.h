
#ifndef MESH_VIEWER
#define MESH_VIEWER
#include "Mesh_viewer_interpreter.h"


#ifdef __cplusplus
extern "C" {
#endif
void prepare_rendering_data(Mesh_viewer_world*);

void prepare_rendering_data(Mesh_viewer_world*mw)
{
    test_add_array_to_shader(mw);

}

#ifdef __cplusplus
}
#endif
#endif
