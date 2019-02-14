#ifndef FGS_IMAGE_FILTER_CHAIN_HPP_
#define FGS_IMAGE_FILTER_CHAIN_HPP_
#include <memory>

#include <dynamic_reconfigure/server.h>
#include <fgs_image_filter/ChainConfig.h>
#include <nodelet/loader.h>

using fgs_image_filter::ChainConfig;

namespace fgs {
namespace image_filter {

class Chain {
 private:
  explicit Chain(ros::NodeHandle& nh);

 private:
  void ReconfigureCallback(ChainConfig& config, uint32_t level);

  std::shared_ptr<nodelet::Loader> manager_;
  std::shared_ptr<dynamic_reconfigure::Server<ChainConfig>> server_;
};

}
}
#endif
