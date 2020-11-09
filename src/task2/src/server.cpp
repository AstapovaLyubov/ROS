#include <ros/ros.h>
#include <task2/GetDeterminant.h>
#include <cstdlib>
#include <iostream>

#include <Eigen/Eigen>


bool get_determinant(task2::GetDeterminant::Request &req,task2::GetDeterminant::Response &resp);


int main(int argc, char **argv)
{
    ros::init(argc, argv, "get_determinant_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("get_determinant", get_determinant);
    ROS_INFO("Ready to calculate the determinant of the matrix.");
    ros::spin();
    
    return 0;
}

bool get_determinant(task2::GetDeterminant::Request &req,
                      task2::GetDeterminant::Response &resp)
{
    Eigen::Matrix<float, 3, 3> X;
    for (int i = 0; i<X.rows(); i++)
    {
        for (int j = 0; j<X.cols(); j++)
        {
            X(i,j) = req.input_matrix[i*X.cols()+j];
        }
        
    }

    resp.det = X.determinant();
    ROS_INFO_STREAM("Matrix: \n" << X);
    ROS_INFO_STREAM("Determinant = " << resp.det);

    return true;
}
