#include "ros/ros.h"                                                                                                        
#include <iostream>                                                                                                        
using namespace std;                                                                                                        
#include "std_msgs/Int32.h"

void rec(const std_msgs::Int32& a)
{
   std::cout << "/subscriber: data: " << a.data << endl; 
    return;
}    

int main (int argc, char **argv)                                                                                            
{
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle n;                                                                                                        
    ros::Subscriber sub = n.subscribe("/topic", 1000, rec);   
    ros::spin();                                                                                                           
    return 0;  
}
