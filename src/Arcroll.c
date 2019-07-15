#include<Arcroll.h>
void Arcroll_init(struct Arcroll* own)
{
    GlobalInfo_init(own->ginfo);
    own->t_mouse_coord=(float*)malloc(sizeof(float)*2);
    own->TR.resize(3,3);
    own->TR.setIdentity();
own->MV.resize(3,1);
own->MV.setZero();
    own->data=(float*)malloc(sizeof(float)*16);
    
}

void Arcroll_L_init(struct Arcroll * own)
{
own->t_mouse_coord[0]=own->ginfo->mouse_coord[0];
own->t_mouse_coord[1]=own->ginfo->mouse_coord[1];
printf("mouse_coord 0:%lf",own->t_mouse_coord[0]);
}
float* Arcroll_data(struct Arcroll* own)
{
for(int i=0;i<3;i++)
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
own->data[15]=1.0f;
return own->data;
}
