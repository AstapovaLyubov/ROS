#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node");//инициализирует основные процессы рос
  ros::NodeHandle n;//объект для управления нодой
  ros::Publisher pub=n.advertise <std_msgs::Int32>("/topic",1000);//отправка сообений в топике
  ros::Rate loop_rate(1);
  //ros::Duration(5).sleep();
  int a;
  while(cin >> a)
  {
      std_msgs::Int32 dat;//создаем экземпляр для сообщения
      dat.data = a;
      pub.publish(dat);
      loop_rate.sleep();   
  }
ros::spinOnce();                                                                                                           
return 0;   
}

