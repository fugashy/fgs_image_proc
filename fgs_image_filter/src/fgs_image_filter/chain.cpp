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
      std::string last_nodelet_name = manager_->listLoadedNodelets().back();
      remap["/camera/image_raw"] = last_nodelet_name + "/image_filtered";
    }

    // Generate nodelet name
    std::ostringstream sout;
    sout << "filter_" << std::setfill('0') << std::setw(3) << i;

    nodelet::V_string argv;
    manager_->load(sout.str(), "fgs_image_filter/Nodelet", remap, argv);
  }

  auto nodelet_list = manager_->listLoadedNodelets();
  for (int i = 0, iend = nodelet_list.size(); i < iend; ++i) {
    ROS_INFO("Loaded node[%d]: %s", i, nodelet_list[i].c_str());
  }
  ROS_INFO("Ready to filtering");
}

bool Chain::ChangeChainNum(fgs_image_filter::ChangeChainNum::Request& req,
                           fgs_image_filter::ChangeChainNum::Response& res) {
  if (req.num <= 0) {
    ROS_WARN("Number of chain should be larger than 0.");
    return false;
  }
  manager_.reset();

  for (int i = 0, iend = req.num; i < iend; ++i) {
    nodelet::M_string remap;
    nodelet::V_string argv;
    std::ostringstream sout;
    sout << "filter_" << std::setfill('0') << i;
    manager_->load(sout.str(), "fgs_image_filter/Nodelet", remap, argv);
  }

  return true;
}

}
}
