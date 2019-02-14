#include "fgs_image_filter/chain.hpp"

#include <sstream>
#include <iomanip>

namespace fgs {
namespace image_filter {

Chain::Chain(ros::NodeHandle& nh) {
  server_ = nh.advertiseService(
      "change_chain_num", &Chain::ChangeChainNum, this);
  manager_.reset(new nodelet::Loader());

  nodelet::M_string remap;
  nodelet::V_string argv;
  std::ostringstream sout;
  sout << "filter_" << std::setfill('0') << 0;
  manager_->load(sout.str(), "fgs_image_filter/Nodelet", remap, argv);
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
