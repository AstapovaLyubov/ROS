#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

void receive(const geometry_msgs::Twist& movement)// всегда обработчик принимает константную ссылку на сообщение из топика
{
	ROS_INFO("Got:\n"
	"1) pos.linear: x= %f y= %f z= %f\n"
	"2) pos.angular x= %f y= %f z= %f\n",
	movement.linear.x, movement.linear.y, movement.linear.z,
	movement.angular.x, movement.angular.y, movement.angular.z);
	return;
}

 

int main(int argc, char **argv)

{
	ros::init(argc, argv, "subscriber");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/turtle1/cmd_vel", 1000, receive);
	ros::spin();//заканчиваются все процессы но не отдает управление ноде дальше, как spinOnes(там ноды может переходит к выполнению следующий инструкции).
//а тут выполнение может прерваться параллельным потоком rosshutdown или ctrl+C
	return 0;

}
