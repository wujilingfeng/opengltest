#include<Mesh_view/Arcroll.h>
void Arcroll_init(struct Arcroll* own)
{
    GlobalInfo_init(own->ginfo);
    own->t_mouse_coord=(float*)malloc(sizeof(float)*2);
    own->TR.resize(4,4);
    own->TR.setIdentity();
    own->MV.resize(4,4);
    own->MV.setIdentity();
    own->MV.coeffRef(2,3)=-4.0;
    own->MV_INVERSE=own->MV.inverse();
    
    //own->INIT_TR.resize(4,4);
    //own->INIT_TR.setIdentity();
    //own->INIT_TR.coeffRef(2,3)=-1.0;
    

//own->TR.coeffRef(0,3)=0.1;
//own->TR.coeffRef(1,3)=0.2;
//own->TR.coeffRef(2,3)=0.2;
//own->TR.coeffRef(0,0)=0.707;
//own->TR.coeffRef(0,1)=-0.707;
//own->TR.coeffRef(1,0)=0.707;
//own->TR.coeffRef(1,1)=0.707;
//own->MV.coeffRef(0)=0.2;
//own->MV.coeffRef(1)=0.5;
//own->MV.coeffRef(2)=-0.0;
    own->data=(float*)malloc(sizeof(float)*16);
    
}

void Arcroll_L_init(struct Arcroll * own)
{
own->t_mouse_coord[0]=own->ginfo->mouse_coord[0];
own->t_mouse_coord[1]=own->ginfo->mouse_coord[1];
//printf("l_init");
//printf("mouse_coord 0:%lf",own->t_mouse_coord[0]);
}
void Arcroll_R_init(struct Arcroll* own)
{
own->t_mouse_coord[0]=own->ginfo->mouse_coord[0];
own->t_mouse_coord[1]=own->ginfo->mouse_coord[1];
}
void Arcroll_L_Move(struct Arcroll *own)
{

float tempx=own->ginfo->mouse_coord[0]-own->t_mouse_coord[0],tempy=own->ginfo->mouse_coord[1]-own->t_mouse_coord[1];
Eigen::Matrix4f temp_tr;
temp_tr.setIdentity();
tempx=tempx*0.005;tempy=-tempy*0.005;
temp_tr.coeffRef(0,0)=cos(tempx);temp_tr.coeffRef(0,1)=-sin(tempx)*sin(tempy);temp_tr.coeffRef(0,2)=sin(tempx)*cos(tempy);
temp_tr.coeffRef(1,1)=cos(tempy);
temp_tr.coeffRef(1,2)=sin(tempy);
temp_tr.coeffRef(2,0)=-sin(tempx);
temp_tr.coeffRef(2,1)=-cos(tempx)*sin(tempy);
temp_tr.coeffRef(2,2)=cos(tempx)*cos(tempy);
//temp_tr.coeffRef(0,3)=0.5;
own->TR=temp_tr*own->TR;
own->t_mouse_coord[0]=own->ginfo->mouse_coord[0];own->t_mouse_coord[1]=own->ginfo->mouse_coord[1];

}
void Arcroll_R_Move(struct Arcroll* own)
{
float tempx=own->ginfo->mouse_coord[0]-own->t_mouse_coord[0],tempy=own->ginfo->mouse_coord[1]-own->t_mouse_coord[1];

own->TR.coeffRef(0,3)+=tempx*0.005;
own->TR.coeffRef(1,3)-=tempy*0.005;
own->t_mouse_coord[0]=own->ginfo->mouse_coord[0];own->t_mouse_coord[1]=own->ginfo->mouse_coord[1];
}
float* Arcroll_data(struct Arcroll* own)
{
/*for(int i=0;i<3;i++)
{
for(int j=0;j<4;j++)
{
if(j<3)
{
own->data[i*4+j]=own->TR.coeff(i,j);
}
else
{
own->data[i*4+j]=own->MV.coeff(i);

}
}

}
for(int i=0;i<3;i++)
{
own->data[3*4+i]=0.0f;

}
own->data[15]=1.0f;*/
Eigen::Matrix4f temp_tr=own->MV_INVERSE*own->TR*own->MV;
for(int i=0;i<4;i++)
{
for(int j=0;j<4;j++)
{
own->data[i*4+j]=temp_tr.coeff(i,j);

}
}
return own->data;
}
void Arcroll_M_Move(struct Arcroll*own,double y)
{
    own->TR.coeffRef(2,3)+=(float)y*0.05;
//    printf("%lf\n",y);

}
