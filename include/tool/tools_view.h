#include<Dense>
#include<Mesh/Mesh.h>
void set_MatrixV_F(template_m* mesh,Eigen::MatrixXf *V,Eigen::MatrixXi *F)
{
    int F_rows=0;
    if(mesh->simplex==1)
    {
        F_rows=mesh->num_c(mesh); 
    }
    else
    {
    
        for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
        {
        
            F_rows+=(cit->second->vertices_size-2); 
            
        }
    
    }
    if(F_rows==0)
    {return;}
    F->resize(F_rows,3);
    V->resize(mesh->num_v(mesh),3);
    int i=0;
    for(auto vit=mesh->vertices.begin();vit!=mesh->vertices.end();vit++)
    {
        for(int j=0;j<3;j++)
        {    
            V->coeffRef(i,j)=vit->second->point[j];
        
        } 
        i++;
    }
    i=0;
    
    for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
    {
        //printf("cit v size : %d\n",cit->second->vertices_size); 
        for(int j=1;j<cit->second->vertices_size-1;j++)
        {   
            F->coeffRef(i,0)=((template_v*)(cit->second->vertices[0]))->id;
            F->coeffRef(i,1)=((template_v*)(cit->second->vertices[j]))->id;
            F->coeffRef(i,2)=((template_v*)(cit->second->vertices[j+1]))->id;

            i++;
        }
    }
}
void set_MatrixE(template_m* mesh,Eigen::MatrixXi *E)
{
    mesh->external_cell_init_(mesh);
    int i=0,len=node_size(mesh->external_cell.halffaces);
    if(len==0)
    {
        return;
    
    }
    E->resize(node_size(mesh->external_cell.halffaces),2);
    for(Node hfit=*mesh->external_cell.halffaces;*hfit!=NULL;hfit++)
    {
        E->coeffRef(i,0)=((template_v*)((template_hf*)(*hfit))->vertices[0])->id;
        E->coeffRef(i,1)=((template_v*)((template_hf*)(*hfit))->vertices[1])->id;
        i++;
    }

}

