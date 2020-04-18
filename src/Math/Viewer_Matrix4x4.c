#include<Math/Viewer_Matrix4x4.h>
#define Matrix4x4 Viewer_Matrix4x4_
void Matrix4x4_free(Matrix4x4 *m)
{
	if(m==0)
	{return;}	
	if(m->data!=0)
	{
		free(m->data);
	}
	free(m);
}
viewer_Matrix4x4_func(double)
viewer_Matrix4x4_func(float)
Matrix4x4 *Projection(float FOV,float aspect,float zNear,float zFar)
{
    Matrix4x4 *p=(Matrix4x4*)malloc(sizeof(Matrix4x4));
    Matrix4x4_init_float(p);
	p->zero(p);
    float zRange=zNear-zFar;
    float tanHalfFOV=tan((FOV/2.0f));
	float* data=(float*)(p->data);
    data[0*4+0]=1.0f/(tanHalfFOV*aspect);
    data[1*4+1]=1.0f/tanHalfFOV;
    data[2*4+2]=-(zNear+zFar)/zRange;
    data[2*4+3]=2.0f*zFar*zNear/zRange;
    data[3*4+2]=1.0f;

	return p;
}
#undef Matrix4x4
