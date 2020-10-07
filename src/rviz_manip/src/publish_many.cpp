#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>

int main (int argc, char **argv)
{
    ros::init(argc, argv, "point_publisher");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<visualization_msgs::Marker>("pt_topic", 10, true);//ЭТО В RViz надобудет писать Marker_topic
    ros::Rate r(30);
    double offset=0;
    while(ros::ok())
    {
        visualization_msgs::Marker mrk;
        mrk.header.frame_id="/point_on_map";//ЭТО В RViz надобудет писать  в fix_frame
        mrk.header.stamp = ros::Time::now();
        mrk.ns="there_is_point";//namespace маркеров. В одном пространстве может быть несколько маркеров, но все с разными id
        mrk.id = 0;
        mrk.action=visualization_msgs::Marker::ADD;
        mrk.pose.position.x=5;//глобальные координаты. Т.е. относительно них будут отсчитывать остальные
        mrk.pose.position.y=-100;
        
        mrk.type=visualization_msgs::Marker::POINTS;
        mrk.scale.x=0.5;
        mrk.scale.y=0.5;
        mrk.color.r=0.0;
        mrk.color.g=1.0;
        mrk.color.b=0.0;
        mrk.color.a=1.0;
        
        for(int x=-20;x<=20;x++)
        {
            geometry_msgs::Point p;
            p.x=x;
            p.y = 2*sin(x+offset);
            p.z = 2*cos(x+offset);
            mrk.points.push_back(p);
  
        }
        pub.publish(mrk);
        offset+=0.4;
        r.sleep();
    }
    
     return 0;
     
     
     
}
