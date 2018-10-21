#include "ros/ros.h"
#include "std_msgs/Int16MultiArray.h"
#include "std_msgs/Int16.h"
#include <sensor_msgs/LaserScan.h>
#include <math.h>
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 https://answers.ros.org/question/198843/need-explanation-on-sensor_msgslaserscanmsg/
 */

 class SubscribeAndPublish
 {
 public:
   SubscribeAndPublish()
   {
     //Topic you want to publish
     pub_ = n_.advertise<sensor_msgs::LaserScan>("/ir_scan", 10);
     //Topic you want to subscribe
     sub_ = n_.subscribe("ir_sens", 1, &SubscribeAndPublish::callback, this);

     _num_readings = 5;

     //Populate the LaserScan message_generation
     scan_.header.frame_id = "irScan_frame";
     scan_.angle_min = 30 * ( M_PI / 180 );
     scan_.angle_max = 150 * ( M_PI /180 );
     scan_.angle_increment = 30 * ( M_PI /180 );
     scan_.time_increment = 0.010;
     scan_.range_min = 0.0;
     scan_.range_max = 300.0;
     scan_.ranges.resize(_num_readings);
   }

   void callback(const std_msgs::Int16MultiArray::ConstPtr& irArray)
   {
     ros::Time scan_time = ros::Time::now();
     //Populate the LaserScan message_generation
     scan_.header.stamp = scan_time;
     int i = 0;
     for( auto it = irArray->data.begin(); it != irArray->data.end(); ++it, ++i)
     {
       scan_.ranges[i] = *it;
     }

     pub_.publish(scan_);
   }



 private:
   ros::NodeHandle n_;
   ros::Publisher pub_;
   ros::Subscriber sub_;
   sensor_msgs::LaserScan scan_;

   unsigned int _num_readings;


 };//End of class SubscribeAndPublish


int main(int argc, char **argv)
{

  ros::init(argc, argv, "irSensorScan");
  SubscribeAndPublish SAPObject;
  ros::spin();

  return 0;
}
