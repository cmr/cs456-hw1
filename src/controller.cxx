#include <cstdlib>
#include <cassert>
#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv) {
	ros::init(argc, argv, "controller");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<std_msgs::String>("control_messages", 1000);
    ros::Rate loop_rate(1 / 8.0);
    while (ros::ok()) {
        std::string data;
        switch (rand() % 3) {
            case 0:
                data = "start";
                break;
            case 1:
                data = "stop";
                break;
            case 2:
                data = "pause";
                break;
            default:
                data = "nope";
                break;
        }

        ROS_INFO("Sending command %s", data.c_str());
        std_msgs::String msg;
        msg.data = data;
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
	return 0;
}

