#ifndef Mesh_viewer_math
#define Mesh_viewer_math
#define factorial Mesh_viewer_fac
#define SIGN(x) ((x>0)?1:((x<0)?-1:0))
#define M_PI 3.1415926
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#ifdef __cplusplus
extern "C" {
#endif
int factorial(int);
int * pailie_map_i_to_reverse_order(int);
int* map_reverse_order_to_pailie(int*,int);
int* compute_combination(int,int);
double* out_product(double*,double *);
#ifdef __cplusplus
}
#endif
#endif
