#ifndef Viewer_Matrix4x4_H
#define Viewer_Matrix4x4_H
#define Matrix4x4 Viewer_Matrix4x4_
#include<Math/LB_Math.h>
#include<stdio.h>
#include<stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct Matrix4x4{
    struct Matrix4x4 * (*mult)(struct Matrix4x4 *,struct Matrix4x4 *);
    void (*transpose)(struct Matrix4x4 *);
    struct Matrix4x4 *(*inverse)(struct Matrix4x4 *); 
    void (*identity)(struct Matrix4x4 *);
    void (*zero)(struct Matrix4x4*);
    void (*print_self)(struct Matrix4x4 *);
    void *(*det)(struct Matrix4x4 *);
//copy 2 to 1 
    void (*copy_data)(struct Matrix4x4*,struct Matrix4x4*);
    void *data;
    void *prop;
}Matrix4x4;
void Matrix4x4_free(Matrix4x4 *);

#define viewer_Matrix4x4_func_declare(typevalue) Matrix4x4 *Matrix4x4_mult_##typevalue(Matrix4x4 *,Matrix4x4 *);\
Matrix4x4 *Matrix4x4_get_transpose_##typevalue(Matrix4x4* );\
void Matrix4x4_transpose_##typevalue(Matrix4x4 *);\
Matrix4x4 *Matrix4x4_inverse_##typevalue(Matrix4x4 *);\
void Matrix4x4_identity_##typevalue(Matrix4x4 *);\
void Matrix4X4_zero_##typevalue(Matrix4x4 *);\
void Matrix4x4_printf_##typevalue(Matrix4x4 *);\
void Matrix4x4_init_##typevalue(Matrix4x4 *);\
void* Matrix4x4_det_##typevalue(Matrix4x4 *);\
void  Matrix4x4_copy_data_##typevalue(Matrix4x4 *,Matrix4x4 *);\

#define viewer_Matrix4x4_func(typevalue) Matrix4x4 * Matrix4x4_mult_##typevalue (Matrix4x4 *a,Matrix4x4 *b)\
{ \
    Matrix4x4 *re=(Matrix4x4*)malloc(sizeof(Matrix4x4));\
    Matrix4x4_init_##typevalue(re);\
    typevalue *data=(typevalue*)(re->data);\
    typevalue *data_a=(typevalue*)(a->data),*data_b=(typevalue*)(b->data);\
    for(int i=0;i<4;i++)\
    {\
        for(int j=0;j<4;j++)\
        {\
            typevalue temp_s=0;\
            for(int k=0;k<4;k++)\
            {\
                temp_s+=data_a[4*i+k]*data_b[k*4+j];\
            }\
            data[i*4+j]=temp_s;\
        }\
    }\
	a->copy_data(a,re);\
	Matrix4x4_free(re);\
\
    return a;\
}\
Matrix4x4 *Matrix4x4_get_transpose_##typevalue(Matrix4x4* a)\
{\
    Matrix4x4 * re=(Matrix4x4*)malloc(sizeof(Matrix4x4));\
    Matrix4x4_init_##typevalue(re);\
    typevalue *data=(typevalue*)(re->data);\
    typevalue *data_a=(typevalue*)(a->data);\
    for(int i=0;i<4;i++)\
    {\
        for(int j=0;j<4;j++)\
        {\
            data[i*4+j]=data_a[j*4+i];\
        }\
    }\
    return re;\
}\
void Matrix4x4_transpose_##typevalue(Matrix4x4 *a)\
{\
	Matrix4x4* b=Matrix4x4_get_transpose_##typevalue(a);\
	a->copy_data(a,b);\
	Matrix4x4_free(b);\
}\
Matrix4x4 *Matrix4x4_inverse_##typevalue(Matrix4x4 *a)\
{\
    Matrix4x4 *re=(Matrix4x4 *)malloc(sizeof(Matrix4x4));\
    Matrix4x4_init_##typevalue(re);\
    typevalue data[4][4],data_b[4][4],*data_a=(typevalue*)(a->data);\
    for(int i=0;i<4;i++)\
    {\
        for(int j=0;j<4;j++)\
        {\
            data[i][j]=data_a[4*i+j];\
            data_b[i][j]=0;\
        }\
        data_b[i][i]=1;\
    }\
    for(int i=0;i<4;i++)\
    {\
        int k=i;\
        for(int j=i;j<4;j++)\
        {\
            if(SIGN(data[i][j])*data[i][j]>SIGN(data[i][k])*data[i][k])\
            {\
                k=j;\
            }\
        }\
        for(int l=0;l<4;l++)\
        {\
            typevalue temp=data[l][i],temp1=data_b[l][i];\
            data[l][i]=data[l][k];data_b[l][i]=data_b[l][k];\
            data[l][k]=temp;data_b[l][k]=temp1;\
        }\
        typevalue temp=data[i][i];\
        if(temp*(SIGN(temp))<=10e-10)\
        {\
		printf("inverse terminate:%lf\n",temp);\
            Matrix4x4_free(re);\
            return 0;\
        }\
        for(int j=0;j<4;j++)\
        {\
            data[j][i]=data[j][i]/temp;\
            data_b[j][i]=data_b[j][i]/temp;\
        }\
        for(int j=i+1;j<4;j++)\
        {\
            typevalue temp1=data[i][j];\
            for(int l=0;l<4;l++)\
            {\
                data[l][j]-=temp1*data[l][i];\
                data_b[l][j]-=temp1*data_b[l][i];\
            }\
            \
        }\
    }\
    for(int i=0;i<4;i++)\
    {\
        int l=3-i;\
        for(int j=0;j<l;j++)\
        {\
            typevalue temp=data[l][j];\
            for(int k=0;k<4;k++)\
            {\
                data[k][j]-=temp*data[k][l];\
                data_b[k][j]-=temp*data_b[k][l];\
            }\
        }\
    }\
    typevalue *data_c=(typevalue *)(re->data);\
    for(int i=0;i<4;i++)\
    {\
        for(int j=0;j<4;j++)\
        {\
            data_c[i*4+j]=data_b[i][j];\
        }\
    }\
    return re;\
}\
void Matrix4x4_identity_##typevalue(Matrix4x4 *a)\
{\
    typevalue *data=(typevalue *)(a->data);\
    for(int i=0;i<4;i++)\
    {\
        for(int j=0;j<4;j++)\
        {\
            data[i*4+j]=0;\
        }\
        data[i*4+i]=1;\
    }\
}\
void Matrix4x4_zero_##typevalue(Matrix4x4 *a)\
{\
	typevalue *data=(typevalue *)(a->data);\
	for(int i=0;i<4;i++)\
	{\
		for(int j=0;j<4;j++)\
		{\
			data[i*4+j]=0;\
		}\
	}\
}\
void Matrix4x4_printf_##typevalue(Matrix4x4 *a)\
{\
    printf("********\n");\
    typevalue *data=(typevalue *)(a->data);\
    for(int i=0;i<4;i++)\
    {\
        for(int j=0;j<4;j++)\
        {\
            printf(" %lf  ",data[4*i+j]);\
        }\
        printf("\n");\
    }\
    printf("**********\n");\
\
}\
void * Matrix4x4_det_##typevalue(Matrix4x4 *a)\
{\
    int *index=pailie_map_i_to_reverse_order(4);\
    int *index1=map_reverse_order_to_pailie(index,4);\
    typevalue *re=(typevalue *)malloc(sizeof(typevalue));\
    typevalue *data=(typevalue *)a->data;\
    typevalue temp=1;\
    int temp_sum=0;\
    *re=0;\
    for(int l=0;l<24;l++)\
    {\
        temp=1;\
        temp_sum=0;\
        for(int i=0;i<4;i++)\
        {\
           temp_sum+=index[l*4+i];\
            temp*=data[i*4+index1[l*4+i]];\
        }\
        if(temp_sum%2==1){\
        temp=-temp;\
        }\
        *re=(*re)+temp;\
    }\
    \
    free(index);\
    free(index1);\
    return (void*)re;\
}\
void Matrix4x4_copy_data_##typevalue(Matrix4x4 *a,Matrix4x4 *b)\
{\
	typevalue *data_a=(typevalue*)(a->data);\
	typevalue *data_b=(typevalue*)(b->data);\
	for(int i=0;i<4;i++)\
	{\
		for(int j=0;j<4;j++)\
		{\
			data_a[i*4+j]=data_b[i*4+j];\
		}\
	}\
	\
}\
void Matrix4x4_init_##typevalue(Matrix4x4 *a)\
{\
    a->mult=Matrix4x4_mult_##typevalue;\
    a->transpose=Matrix4x4_transpose_##typevalue;\
    a->inverse=Matrix4x4_inverse_##typevalue;\
    a->identity=Matrix4x4_identity_##typevalue;\
    a->print_self=Matrix4x4_printf_##typevalue;\
    a->det=Matrix4x4_det_##typevalue;    \
    a->data=malloc(sizeof(typevalue)*16);\
    a->zero=Matrix4x4_zero_##typevalue;\
	a->copy_data=Matrix4x4_copy_data_##typevalue;\
    Matrix4x4_identity_##typevalue(a);\
	a->prop=0;\
}\

viewer_Matrix4x4_func_declare(double)
viewer_Matrix4x4_func_declare(float)
Matrix4x4* Projection(float,float,float,float);
#ifdef __cplusplus
}
#endif
#undef Matrix4x4
#endif
