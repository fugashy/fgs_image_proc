#include "fgs_image_filter/chain.hpp"

#include <sstream>
#include <iomanip>

namespace fgs {
namespace image_filter {

Chain::Chain(ros::NodeHandle& nh) {
  server_.reset(new dynamic_reconfigure::Server<ChainConfig>(
        ros::NodeHandle(nh, "chain")));
  dynamic_reconfigure::Server<ChainConfig>::CallbackType f = boost::bind(
      &Chain::ReconfigureCallback, this, _1, _2);
  server_->setCallback(f);
}

void Chain::ReconfigureCallback(ChainConfig& config, uint32_t level) {
  if (config.num <= 0) {
    ROS_WARN("Number of chain should be larger than 0.");
    return;
  }
  manager_.reset();

  for (int i = 0, iend = config.num; i < iend; ++i) {
    nodelet::M_string remap;
    nodelet::V_string argv;
    std::ostringstream sout;
    sout << "filter_" << std::setfill('0') << i;
    manager_->load(sout.str(), "fgs_image_filter/Nodelet", remap, argv);
  }
}

}
}
