#include<Math/Mesh_viewer_math.h>
int factorial(int n)
{
    int re=1;
    for(int i=2;i<=n;i++)
    {
        re*=i;
    
    }
    return re;

}
int *pailie_map_i_to_reverse_order(int n)
{

    int num=factorial(n);
    int *re=(int*)malloc(sizeof(int)*n*num);
    int chu,yu;

    for(int i=0;i<num;i++)
    {
        chu=i;
        for(int j=0;j<n;j++)
        {
            yu=chu%(j+1);
            chu=chu/(j+1);
            re[i*n+n-1-j]=yu;
        }
    
    }
    return re;
}
int * map_reverse_order_to_pailie(int* r,int n)
{
    int num=factorial(n);
    int *re=(int*)malloc(sizeof(int)*n*num);
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<n;j++)
        {
        
            re[i*n+j]=j;
        }
    
    }
    int ix,iy,temp;
    for(int i=0;i<num;i++)
    {

        for(int j=0;j<n;j++)
        {
            ix=i*n+j;
            iy=i*n+j+r[i*n+j];
            for(int l=iy;l>ix;l--)
            { 
                temp=re[l-1];
                re[l-1]=re[l];
                re[l]=temp;
            }
            
        }
    
    }

    return re;

}
#undef factorial
