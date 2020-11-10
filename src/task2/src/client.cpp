#include <ros/ros.h>
#include <task2/GetDeterminant.h>
#include <cstdlib>
#include <iostream>
#include <Eigen/Eigen>
#include <boost/numeric/ublas/matrix.hpp>


boost::array<float,9> CreateRandomMatrix();


int main(int argc, char **argv)
{
    ros::init(argc, argv, "add_floats_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<task2::GetDeterminant>("get_determinant");
    task2::GetDeterminant srv;
    ros::Rate loop_rate(1);// 1 - одно смс в сек
    
    while (ros::ok())
    {
        ROS_INFO_STREAM("Generating a matrix..");
        boost::array<float,9> input_matrix = CreateRandomMatrix();
        
        for (int i=0;i<boost::size(input_matrix);i++)
            srv.request.input_matrix[i] = input_matrix[i];

        if (client.call(srv))
            ROS_INFO_STREAM("Determinant = " << srv.response.det);
        else
            ROS_ERROR_STREAM("Failed to get determinant");
        
        loop_rate.sleep();//подождать чтобы сохранить заданную скорость
    }
}


boost::array<float,9> CreateRandomMatrix()
{
    boost::array<float,9> m;
    for (std::size_t i=0; i<boost::size(m); i++)
        m[i] = static_cast<float>(((std::rand()%2001-1000))/10.0);
    return m;
}
