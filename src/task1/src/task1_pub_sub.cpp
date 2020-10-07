#include <ros/ros.h>
#include "std_msgs/String.h"            // Для отправки символа
#include "std_msgs/Int8.h"              // Для приёма кода символа
#include <sstream>
#include <string>


// Объявляем издетеля и подписчика
ros::Publisher symbol_publisher;
ros::Subscriber symbol_code_subscriber;

int smbl_code = -1;       // Код символа
bool get_new_symbol_code = false;  // Флаг для публикации цитаты
const double frecuency = 10.0;  // Частота работы узла в Гц

// Функция установки кода символа
void symbol_code_callback(const std_msgs::Int8::ConstPtr& msg)
{
    smbl_code = msg->data;
    ROS_INFO("symbol code: %i", smbl_code);
    //Проверка существования кода символа из кодировки ACSII
    if (smbl_code>=33 && smbl_code<=127)
    {
        ROS_INFO("Yeah, there is such character in ASCII encoding!");
        get_new_symbol_code = true;  
    }
    else 
    {
        ROS_INFO("Ups, there is no such character in ASCII encoding:(((");
        get_new_symbol_code=false;
    }
    return;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "task1_pub_sub");
    ros::NodeHandle n;
    ROS_INFO("Starting task1...");
    
    symbol_publisher = n.advertise<std_msgs::String>("/symbol", 1);                    // Определение издателя
    symbol_code_subscriber = n.subscribe("/symbol_code", 1, &symbol_code_callback);    // Определение подписчика
    ros::Rate loop_rate(frecuency);
    
     // Основной цикл работы
    while (ros::ok())
    {
        if (get_new_symbol_code == true)
        {
            std_msgs::String sbl;
            sbl.data=(char)smbl_code;
            symbol_publisher.publish(sbl);
            get_new_symbol_code = false;
        }
            ros::spinOnce();
            loop_rate.sleep();
    }
}
