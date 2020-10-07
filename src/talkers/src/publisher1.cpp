#include "ros/ros.h" //базовые функции, команды, классы ROS
#include "geometry_msgs/Twist.h"//подключен класс в котором описан класс с типом того сообщения, которе мы будем публиковать

int main (int argc, char **argv)
{
	ros::init(argc, argv, "publisher");//инициализирует основные процессы ROS.
						//Имя по умолчанию, если оно не задается при вызове ноды с __name:=<name node>
	ros::NodeHandle n; //объект с помощью которого управляем нодой, подписываемся, отправляем сообщения в топики
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);//привязываемся к топику
											//1000-это буфер топика, т.е. сколько сообщений будет в нем держать
	ros::Rate loop_rate(1);// т.к сообщения далее отправляются в цикле, этот экземпляр устанавливает скорость подачи сообщений в топик. 1 - одно смс в сек
	for (int t=0; t<20; t++)
	{
		geometry_msgs::Twist pos;         
          	pos.linear.x=1.5;         
          	pos.angular.z=std::abs(2*sin(0.5*t));
		//макрос вывод на экран. Кроссплатформенный         
          	ROS_INFO("Move to position:\n"             
                         "1) pos.linear: x= %f y=%f z=%f\n"
                         "2) pos.angular: x= %f y=%f z=%f\n",
                       	pos.linear.x, pos.linear.y, pos.linear.z,
                        pos.angular.x, pos.angular.y, pos.angular.z);
          	pub.publish(pos);//отправка        
          	loop_rate.sleep();//подождать чтобы сохранить заданную скорость
	}

	ros::spinOnce();//ожидать выполнение всех процессов(публикацию)
	return 0;
	
	
}
