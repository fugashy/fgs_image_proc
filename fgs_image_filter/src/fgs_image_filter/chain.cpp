#include "fgs_image_filter/chain.hpp"

#include <sstream>
#include <iomanip>

namespace fgs {
namespace image_filter {

Chain::Chain(ros::NodeHandle& nh) {
  server_ = nh.advertiseService(
      "change_chain_num", &Chain::ChangeChainNum, this);
  manager_.reset(new nodelet::Loader());

  int chain_num;
  nh.param<int>("default_chain_num", chain_num, 3);
  if (chain_num <= 0) {
    throw std::runtime_error("Number of chain should be larger than 0.");
  }
  std::string input_topic;
  nh.param<std::string>("input_topic", input_topic, "/camera/image_raw");
  if (input_topic == std::string()) {
    throw std::runtime_error("Name of input topic is empty.");
  }

  for (int i = 0; i < chain_num; ++i) {
    nodelet::M_string remap;
    if (i == 0) {
      remap["/camera/image_raw"] = input_topic;
    } else {
      const std::string last_nodelet_name = manager_->listLoadedNodelets().back();
      remap["/camera/image_raw"] = last_nodelet_name + "/image_filtered";
    }

    // Generate nodelet name
    std::ostringstream sout;
    sout << "filter_" << std::setfill('0') << std::setw(3) << i;

    nodelet::V_string argv;
    if (!manager_->load(sout.str(), "fgs_image_filter/Nodelet", remap, argv)) {
      const std::string error_msg = std::string("Failed to load ") + sout.str();
      throw std::runtime_error(error_msg);
    }
  }

  const auto nodelet_list = manager_->listLoadedNodelets();
  for (int i = 0, iend = nodelet_list.size(); i < iend; ++i) {
    ROS_INFO("Loaded node[%d]: %s", i, nodelet_list[i].c_str());
  }
  ROS_INFO("Ready to filtering");
}

bool Chain::ChangeChainNum(fgs_image_filter::ChangeChainNum::Request& req,
                           fgs_image_filter::ChangeChainNum::Response& res) {
  const int current_chain_num = manager_->listLoadedNodelets().size();
  ROS_INFO("current_chain_num : %d", current_chain_num);
  const int diff = req.num - current_chain_num;
  ROS_INFO("diff : %d", diff);
  if (req.num <= 0) {
    ROS_WARN("Number of chain should be larger than 0.");
    return false;
  } else if (diff == 0) {
    ROS_WARN("Requested chain num is same as current chain num. We ignore this request.");
    return false;
  } else if (req.num >= 5) {
    ROS_WARN("Number of chain should be less than 5.(Limited by number of worker thread)");
    return false;
  }

  if (diff > 0) {
    // Load nodelets
    for (int i = current_chain_num, iend = req.num; i < iend; ++i) {
      nodelet::M_string remap;
      ROS_INFO("Trying to load nodelet");
      const std::string last_nodelet_name = manager_->listLoadedNodelets().back();
      ROS_INFO("Name of last nodelet : %s", last_nodelet_name.c_str());
      remap["/camera/image_raw"] = last_nodelet_name + "/image_filtered";
      nodelet::V_string argv;
      std::ostringstream sout;
      sout << "filter_" << std::setfill('0') << std::setw(3) << i;
      if (!manager_->load(sout.str(), "fgs_image_filter/Nodelet", remap, argv)) {
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
