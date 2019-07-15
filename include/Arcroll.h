
//#include "Dense"
#include<OpenglAlg.h>
//#include<OpenglAlg.h>
void Arcroll_init(struct Arcroll*);
void Arcroll_L_init(struct Arcroll*);
float* Arcroll_data(struct Arcroll*);

typedef struct Arcroll{
GlobalInfo * ginfo;
float* t_mouse_coord;
void (*init)(struct Arcroll*)=Arcroll_init;
void (*L_init)(struct Arcroll*)=Arcroll_L_init;
float* (*get_data)(struct Arcroll*)=Arcroll_data;
Eigen::MatrixXf TR;
Eigen::VectorXf MV;
float * data;
}Arcroll;

