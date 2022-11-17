#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <ros/console.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_datatypes.h>
#include <time.h>
#include <termios.h>
#include <chrono>
#include <unistd.h>
#include <cmath>
#include <map>
// Message publication
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64.h>
#include <sstream>
#include <math.h>


using std::placeholders::_1;

clock_t start;
clock_t end;

float thetha;

    // publisher declaration

ros::Publisher R_arm1_joint_position_controller;
ros::Publisher R_arm2_joint_position_controller;
ros::Publisher R_arm3_joint_position_controller;
ros::Publisher L_arm1_joint_position_controller;
ros::Publisher L_arm2_joint_position_controller;
ros::Publisher L_arm3_joint_position_controller;

int getch(void)
 {
   int ch;
   struct termios oldt;
   struct termios newt;
 
   // Store old settings, and copy to new settings
   tcgetattr(STDIN_FILENO, &oldt);
   newt = oldt;
 
   // Make required changes and apply the settings
   newt.c_lflag &= ~(ICANON | ECHO);
   newt.c_iflag |= IGNBRK;
   newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
   newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
   newt.c_cc[VMIN] = 1;
   newt.c_cc[VTIME] = 0;
   tcsetattr(fileno(stdin), TCSANOW, &newt);
 
   // Get the current character
   ch = getchar();
 
   // Reapply old settings
   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
 
   return ch;
 }
int main(int argc, char** argv)
{
    ros::init(argc, argv, "arm_rotate");
    ros::NodeHandle nh;

    // publisher declaration

    R_arm1_joint_position_controller = nh.advertise<std_msgs::Float64>("/jumpbot/R_arm1_joint_position_controller/command", 1);
    R_arm2_joint_position_controller = nh.advertise<std_msgs::Float64>("/jumpbot/R_arm2_joint_position_controller/command", 1);
    R_arm3_joint_position_controller = nh.advertise<std_msgs::Float64>("/jumpbot/R_arm3_joint_position_controller/command", 1);
    L_arm1_joint_position_controller = nh.advertise<std_msgs::Float64>("/jumpbot/L_arm1_joint_position_controller/command", 1);
    L_arm2_joint_position_controller = nh.advertise<std_msgs::Float64>("/jumpbot/L_arm2_joint_position_controller/command", 1);
    L_arm3_joint_position_controller = nh.advertise<std_msgs::Float64>("/jumpbot/L_arm3_joint_position_controller/command", 1);
    ros::Rate rate(50.0); // frequency of operation


    
    std_msgs::Float64 R_arm1_joint;
        std_msgs::Float64 R_arm2_joint;
        std_msgs::Float64 R_arm3_joint;
        std_msgs::Float64 L_arm1_joint;
        std_msgs::Float64 L_arm2_joint;
        std_msgs::Float64 L_arm3_joint;

        R_arm1_joint.data = 0.0;
        R_arm2_joint.data = 0.0;
        R_arm3_joint.data = 0.0;
        L_arm1_joint.data = 0.0;
        L_arm2_joint.data = 0.0;
        L_arm3_joint.data = 0.0;

    while (ros::ok())
    {
        int c=getch();

        switch (c)
        {
          case 97:// keyboard input==a 
            R_arm1_joint.data = 0.0;
            R_arm2_joint.data = 0.0;
            R_arm3_joint.data = 0.0;
            L_arm1_joint.data = 0.0;
            L_arm2_joint.data = 0.0;
            L_arm3_joint.data = 0.0;

            R_arm1_joint_position_controller.publish(R_arm1_joint);
            R_arm2_joint_position_controller.publish(R_arm2_joint);
            R_arm3_joint_position_controller.publish(R_arm3_joint);
            L_arm1_joint_position_controller.publish(L_arm1_joint);
            L_arm2_joint_position_controller.publish(L_arm2_joint);
            L_arm3_joint_position_controller.publish(L_arm3_joint);
            break;

          case 98:
          // cam spin stop(b)
            R_arm1_joint.data = 0;
            R_arm2_joint.data = -1.5707;
            R_arm3_joint.data = 1.5707;
            L_arm1_joint.data = 0;
            L_arm2_joint.data = -1.5707;
            L_arm3_joint.data = 1.5707;

            R_arm1_joint_position_controller.publish(R_arm1_joint);
            R_arm2_joint_position_controller.publish(R_arm2_joint);
            R_arm3_joint_position_controller.publish(R_arm3_joint);
            L_arm1_joint_position_controller.publish(L_arm1_joint);
            L_arm2_joint_position_controller.publish(L_arm2_joint);
            L_arm3_joint_position_controller.publish(L_arm3_joint);

            break;  

          case 99:
          // node down (c)
            R_arm1_joint.data = 0.5;
            R_arm2_joint.data = -1.5707;
            R_arm3_joint.data = 1.0;
            L_arm1_joint.data = 0.5;
            L_arm2_joint.data = -0.9;
            L_arm3_joint.data = 1.0;

            R_arm1_joint_position_controller.publish(R_arm1_joint);
            R_arm2_joint_position_controller.publish(R_arm2_joint);
            R_arm3_joint_position_controller.publish(R_arm3_joint);
            L_arm1_joint_position_controller.publish(L_arm1_joint);
            L_arm2_joint_position_controller.publish(L_arm2_joint);
            L_arm3_joint_position_controller.publish(L_arm3_joint);
            break;

          case 100:
          // disired angle - (d)
            R_arm1_joint.data = 1.0;
            R_arm2_joint.data = -1.5707;
            R_arm3_joint.data = 1.0;
            L_arm1_joint.data = 1.0;
            L_arm2_joint.data = -1.5707;
            L_arm3_joint.data = 1.0;

            R_arm1_joint_position_controller.publish(R_arm1_joint);
            R_arm2_joint_position_controller.publish(R_arm2_joint);
            R_arm3_joint_position_controller.publish(R_arm3_joint);
            L_arm1_joint_position_controller.publish(L_arm1_joint);
            L_arm2_joint_position_controller.publish(L_arm2_joint);
            L_arm3_joint_position_controller.publish(L_arm3_joint);
            break; 

          case 101:
          // disired angle + (e)
            ros::shutdown();
           break;   

        }

    }
    return 0;

}
