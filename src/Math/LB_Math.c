#include<Math/LB_Math.h>
#define factorial LB_factorial
#define out_product LB_three_out_product
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
//compute the station pick m elements from n elements

static int increase_a_step_for_combination(int m,int n,int* temp_array)
{
    
	int temp_i;
    int *mu_array=temp_array;
	for(int i=0;i<m;i++)
	{
		temp_i=mu_array[i]+1;
        	if(temp_i<n)
        	{
            		if((i+1)<m)
            		{
                		if(temp_i>=mu_array[i+1])
                		{
                    			continue;
                		}
            		}
            
            		int* temp_mu=&(mu_array[m]);
            		memmove(temp_mu, mu_array,sizeof(int)*m);
            		temp_mu[i]=temp_i;
            		mu_array=temp_mu;
            		for(int j=0;j<i;j++)
            		{
                		mu_array[j]=j;
            		}
            		return 1;

        	}
        	else
        	{
            		return 0;
        	}
	}
    return 0;
    
}
int * compute_combination(int m,int n)
{
    printf("beginCompute\n");
	int * re=0;
	if(m>n)
	{return re;}
	int len=1;
	for(int i=0;i<m;i++)
	{
		len*=(n-i);		

	}
	len=len/factorial(m);
	printf("%d\n",len);
	re=(int*)malloc(sizeof(int)*len*m);
    
    for(int i=0;i<m;i++)
    {
        re[i]=i;
    }
    //int flag=1;
  //  int sum=0;
    for(int i=0;i<len-1;i++)
    {
    
        increase_a_step_for_combination(m,n,&(re[i*m]));
    }
	return re;
}
double *out_product(double *a,double *b)
{
	double* re=(double*)malloc(sizeof(double)*3);
    
    re[0]=a[1]*b[2]-a[2]*b[1];
    re[1]=-a[0]*b[2]+a[2]*b[0];
    re[2]=a[0]*b[1]-a[1]*b[0];
	return re;
}
#undef factorial
#undef out_product
