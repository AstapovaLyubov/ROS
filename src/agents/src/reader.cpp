#include <ros/ros.h>
#include <my_message/Message1.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

int stop_value = 0;

void reader(const my_message::Message1 & message)
{
	static std::string text;
	static my_message::Message1::_number_type maxNum=0;
	my_message::Message1::_number_type number=message.number;
	ROS_INFO("Received a message with text %s.\n", message.text.c_str());
	if (number>maxNum)
	{
		maxNum=number;
		text=message.text;
	}
	if (message.number==stop_value)
	{
		ROS_INFO("The biggest number is %d. Text is %s.\n", maxNum,text.c_str());
		ros::shutdown();//чтобы выйти из spin()
	}
}


int main (int argc, char **argv)
{
	ros::init(argc, argv, "reader");
	ROS_INFO_STREAM("Reader is ready.\n");
	ros::NodeHandle n; //объект с помощью которого управляем нодой, подписываемся, отправляем сообщения в топики
	ros::param::param<int>("~stop_value",stop_value,-1);//для подхватывающего параметра
	ros::Subscriber sub = n.subscribe("message", 10,reader);//привязываемся к топику
	ros::spin();
        return 0;
}
