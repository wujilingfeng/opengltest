#include<Python.h>
//#include "Dense"
#include<myopengl.h>

int main()
{
    Eigen::MatrixXd b(2,2);
    b.coeffRef(0,0)=11111;
    b.coeffRef(0,1)=23;
    b.coeffRef(1,0)=22222;
    b.coeffRef(1,1)=33333;
    double *p=b.data();
//float a=M_PI;
printf("%lf",p[3]);
//b=eyem();
    mydraw();
printf("d");
return 0;
}
