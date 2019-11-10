#include<iostream>
#include<Mesh_view/Mesh_viewer.h>
int main()
{
    Eigen::MatrixXf V(8,3);
    Eigen::MatrixXi F(12,3);
    Eigen::MatrixXi E;
    V<<-0.5,-0.5,0.5,
    	0.5,-0.5,0.5,
    	-0.500000,0.500000 ,0.500000, 
0.500000, 0.500000 ,0.500000, 
-0.500000, 0.500000, -0.500000 ,
0.500000 ,0.500000 ,-0.500000 ,
-0.500000, -0.500000, -0.500000, 
0.500000, -0.500000 ,-0.500000;
F<<2 ,3 ,1,
2, 1, 0,
4 ,5 ,3,
4 ,3 ,2,
6, 7, 5,
6, 5 ,4,
0, 1, 7,
0, 7 ,6,
3 ,5, 7,
3, 7, 1,
4, 2 ,0,
4, 0 ,6;
std::cout<<V<<std::endl;
std::cout<<F<<std::endl;
m_v_data.F_V=node_overlying(m_v_data.F_V,(void*)(&V));
    m_v_data.F_F=node_overlying(m_v_data.F_F,(void*)(&F));
    m_v_data.E_V=node_overlying(m_v_data.E_V,(void*)(&V));
    m_v_data.E_E=node_overlying(m_v_data.E_E,(void*)(&E));
    show();

    printf("dfsd\n");
    return 0;
}