#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

bool going = false;
int count = 0;

void controlCallback(const std_msgs::String::ConstPtr msg) {
    if (msg->data == "start") {
        going = true;
    } else if (msg->data == "stop") {
        going = false;
        count = 0;
    } else if (msg->data == "pause") {
        going = false;
    } else {
        ROS_WARN("Unknown control message: %s", msg->data.c_str());
    }
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "talker");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Subscriber sub = n.subscribe<std_msgs::String>("control_messages", 1000, controlCallback);
	ros::Rate loop_rate(1);
	while (ros::ok()) {
        if (going) {
            std_msgs::String msg;
            std::stringstream ss;
            ss << "hello world " << count;
            msg.data = ss.str();
            ROS_INFO("%s", msg.data.c_str());
            chatter_pub.publish(msg);
            ++count;
        }
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
