#include "fgs_image_filter/chain.hpp"

#include <sstream>
#include <iomanip>

namespace {
const char* const kTopicOfInput = "/camera/image_raw";
const char* const kTopicOfFiltered = "/image_filtered";
const char* const kNameOfNodelet = "fgs_image_filter/Nodelet";
const int kMinChainNum = 1;
const int kMaxChainNum = 8;
}

namespace fgs {
namespace image_filter {

Chain::Chain(ros::NodeHandle& nh) {
  server_ = nh.advertiseService(
      "change_chain_num", &Chain::ChangeChainNum, this);
  manager_.reset(new nodelet::Loader());

  int chain_num;
  nh.param<int>("default_chain_num", chain_num, 3);
  if (chain_num < kMinChainNum || kMaxChainNum < chain_num) {
    throw std::runtime_error("Number of chain should be in range of 1 to 8");
  }
  std::string input_topic;
  nh.param<std::string>("input_topic", input_topic, kTopicOfInput);
  if (input_topic == std::string()) {
    throw std::runtime_error("Name of input topic is empty.");
  }

  for (int i = 0; i < chain_num; ++i) {
    nodelet::M_string remap;
    if (i == 0) {
      remap[kTopicOfInput] = input_topic;
    } else {
      const std::string last_nodelet_name = manager_->listLoadedNodelets().back();
      remap[kTopicOfInput] = last_nodelet_name + kTopicOfFiltered;
    }

    // Generate nodelet name
    std::ostringstream sout;
    sout << "filter_" << std::setfill('0') << std::setw(3) << i;

    nodelet::V_string argv;
    if (!manager_->load(sout.str(), kNameOfNodelet, remap, argv)) {
      const std::string error_msg = std::string("Failed to load ") + sout.str();
      throw std::runtime_error(error_msg);
    }
  }

  ROS_INFO("Ready to filtering");
}

bool Chain::ChangeChainNum(fgs_image_filter::ChangeChainNum::Request& req,
                           fgs_image_filter::ChangeChainNum::Response& res) {
  ROS_WARN("This service is unstable...");
  if (req.num < kMinChainNum || kMaxChainNum < req.num) {
    throw std::runtime_error("Number of chain should be in range of 1 to 8");
  }
  const int current_chain_num = manager_->listLoadedNodelets().size();
  const int diff = req.num - current_chain_num;
  if (diff == 0) {
    ROS_WARN("Requested chain num is same as current chain num. We ignore this request.");
    return false;
  }

  if (diff > 0) {
    // Load nodelets
    for (int i = current_chain_num, iend = req.num; i < iend; ++i) {
      nodelet::M_string remap;
      const std::string last_nodelet_name = manager_->listLoadedNodelets().back();
      remap[kTopicOfInput] = last_nodelet_name + kTopicOfFiltered;
      nodelet::V_string argv;
      std::ostringstream sout;
      sout << "filter_" << std::setfill('0') << std::setw(3) << i;
      if (!manager_->load(sout.str(), kNameOfNodelet, remap, argv)) {
        ROS_WARN("Failed to load %s", sout.str().c_str());
        return false;
      }
    }
  } else {
    // Unload unnecessary nodelets
    const auto nodelet_list = manager_->listLoadedNodelets();
    for (int i = req.num, iend = current_chain_num; i < iend; ++i) {
      manager_->unload(nodelet_list[i]);
    }
  }

  return true;
}

}
}
