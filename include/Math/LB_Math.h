#ifndef LB_Math_H
#define LB_Math_H
#define factorial LB_factorial
#define out_product LB_three_out_product
#define SIGN(x) ((x>0)?1:((x<0)?-1:0))
#ifndef SAFE_SQRT
#define SAFE_SQRT(x) x>=0?sqrt(x):sqrt(-x)
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(x) if(x!=NULL){free(x);}
#endif
#ifndef M_PI
#define M_PI 3.141592653589
#endif
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
#undef factorial
#undef out_product
