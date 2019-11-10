#ifndef LIB_CELL_ALGORITHM
#define LIB_CELL_ALGORITHM
#include<Dense>
#include<math.h>
#include<Mesh/_Func_.h>
double fact(int);
double area_simplex(double **,int ,int);
double ori_area_simplex(double**,int,int);
Eigen::MatrixXd orthogonal_complementation(Eigen::MatrixXd);
void set_cell_normal(template_m*);
#ifdef SIMPLEX_REQUIRE
#ifdef MANIFOLD_REQUIRE
void increasing_convex_hull(template_m *,template_v* v);
void from_v_createconvex(template_m*,double**,int,int);
#endif
#endif
#endif
