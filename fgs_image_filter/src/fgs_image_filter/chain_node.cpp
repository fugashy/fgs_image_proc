#include "fgs_image_filter/chain.hpp"

#include <ros/ros.h>

using fgs::image_filter::Chain;

int main(int argc, char* argv[]) {
  ros::init(argc, argv, "filter_chain_node");
  ros::NodeHandle private_nh("~");
  Chain::Ptr chain;

  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << std::endl;
  }
  nodelet::M_string remappings = ros::names::getRemappings();
  for (auto it = remappings.begin(); it != remappings.end(); ++it) {
    std::cout << it->first << " : " << it->second << std::endl;
  }

  try {
    chain.reset(new Chain(private_nh));
    ros::spin();
  } catch (const std::exception& e) {
    ROS_FATAL("%s", e.what());
    return -1;
  }
}
