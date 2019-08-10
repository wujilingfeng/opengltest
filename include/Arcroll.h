
//#include "Dense"
#include<OpenglAlg.h>
//#include<OpenglAlg.h>
void Arcroll_init(struct Arcroll*);
void Arcroll_L_init(struct Arcroll*);
void Arcroll_R_init(struct Arcroll*);
float* Arcroll_data(struct Arcroll*);
void Arcroll_L_Move(struct Arcroll*);
void Arcroll_M_Move(struct Arcroll*,double);
void Arcroll_R_Move(struct Arcroll*);

typedef struct Arcroll{
GlobalInfo * ginfo;
float* t_mouse_coord;
void (*init)(struct Arcroll*)=Arcroll_init;
void (*L_init)(struct Arcroll*)=Arcroll_L_init;
void (*R_init)(struct Arcroll*)=Arcroll_R_init;
float* (*get_data)(struct Arcroll*)=Arcroll_data;
void (*L_move)(struct Arcroll*)=Arcroll_L_Move;
void (*M_move)(struct Arcroll*,double)=Arcroll_M_Move;
void (*R_move)(struct Arcroll*)=Arcroll_R_Move;
Eigen::MatrixXf TR;
Eigen::MatrixXf MV,MV_INVERSE;
float * data;
}Arcroll;

