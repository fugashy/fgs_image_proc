#include "fgs_image_filter/chain.hpp"

#include <ros/ros.h>

using fgs::image_filter::Chain;

int main(int argc, char* argv[]) {
  ros::init(argc, argv, "filter_chain_node");
  ros::NodeHandle private_nh("~");
  Chain::Ptr chain;

  try {
    chain.reset(new Chain(private_nh));
    ros::spin();
  } catch (const std::exception& e) {
    ROS_FATAL("%s", e.what());
    return -1;
  }
}
