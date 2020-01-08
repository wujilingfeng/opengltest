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
//compute the statioin pick m elements from n elements
#define Node Mesh_viewer_node_for_combination

typedef struct Mesh_viewer_node_for_combination
{
    struct Mesh_viewer_node_for_combination* Prev;

    struct Mesh_viewer_node_for_combination* Next;
    int *value;
}Mesh_viewer_node_for_combination;
static void my_Node_init(Node*n)
{
    n->Prev=0;
    n->Next=0;
    n->value=0;
}
static int compare_to_combination(int *a,int*b,int m)
{
    for(int i=m-1;i>=0;i--)
    {
        if(a[i]>b[i])
        {
            return 1;
        }
        else if(b[i]>a[i])
        {
            return -1;
        }
    
    }

    return 0;
}
static Node* increase_a_step_for_combination(int m,int n,int* temp_array)
{
    Node* re=0;
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
            
            int* temp_mu=(int*)malloc(sizeof(int)*m);
            memmove(temp_mu, mu_array,sizeof(int)*m);
            temp_mu[i]=temp_i;
            mu_array=temp_mu;
            break;

        }
        else
        {
            return re;
        }
	}
    printf("end one\n");
    for(int i=0;i<m;i++)
    {
        printf("%d  ",mu_array[i]);
    }
    printf("\n");
    while(compare_to_combination(mu_array,temp_array,m)==1)
    {
        Node* temp_n=(Node*)malloc(sizeof(Node));
        my_Node_init(temp_n);
        temp_n->value=mu_array;
        temp_n->Prev=re;
        if(re!=0)
        {
            re->Next=temp_n;
        }
        re=temp_n;


        for(int i=0;i<m;i++)
        {
            temp_i=mu_array[i]-1;
            if(temp_i>=0)
            {
                if((i-1)>=0)
                {
                    if(temp_i<=mu_array[i-1])
                    {
                        continue;
                    }
                
                }
                int* temp_mu=(int*)malloc(sizeof(int)*m);
                memmove(temp_mu, mu_array,sizeof(int)*m);
                temp_mu[i]=temp_i;
                mu_array=temp_mu;
                break;
            }
            else{
                continue;
            }
    
        }
    }
    return re;


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
	re=(int*)malloc(sizeof(int)*len);
    int temp_array[3]={2,3,4};
    for(int i=0;i<3;i++)
    {
        printf("temp: %d ",temp_array[i]);
    }
    Node* iter=increase_a_step_for_combination(3,7,temp_array);
    while(iter!=0)
    {
        for(int i=0;i<m;i++)
        {
            printf("%d  ",iter->value[i]);
        }
        printf("\n");
        iter=iter->Prev;
    
    }
	return re;
}
#undef Node
double *out_product(double *a,double *b)
{
	double* re=0;





	return re;
}
#undef factorial
