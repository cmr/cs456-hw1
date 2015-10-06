#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <vector>
#include <utility>

bool going = false;
int count = 0;

ros::Publisher pub;
std::vector<std::string> msgs;

void chatterCallback(const std_msgs::String::ConstPtr msg) {
    msgs.emplace_back(std::move(msg->data));
    ROS_INFO("Added a message: %s (sz: %d)", msg->data.c_str(), msgs.size());
    if (msgs.size() == 5) {
        std::stringstream ss;
        for (auto it = msgs.begin(); it < msgs.end(); it++) {
            ss << *it << " ";
        }
        std_msgs::String msg;
        msg.data = ss.str();
        ROS_INFO("Spewing out %s", msg.data.c_str());
        pub.publish(msg);
        msgs.clear();
    }
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "buffer");
	ros::NodeHandle n;
	pub = n.advertise<std_msgs::String>("chatter_buffer", 1000);
    ros::Subscriber sub = n.subscribe<std_msgs::String>("chatter", 1000, chatterCallback);
    ros::spin();
	return 0;
}
