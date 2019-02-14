#ifndef FGS_IMAGE_FILTER_CHAIN_HPP_
#define FGS_IMAGE_FILTER_CHAIN_HPP_
#include <memory>

#include <fgs_image_filter/ChangeChainNum.h>
#include <nodelet/loader.h>
#include <ros/ros.h>

namespace fgs {
namespace image_filter {

class Chain {
 public:
  typedef std::shared_ptr<Chain> Ptr;
  explicit Chain(ros::NodeHandle& nh);

 private:
  bool ChangeChainNum(fgs_image_filter::ChangeChainNum::Request& req,
                      fgs_image_filter::ChangeChainNum::Response& res);

  std::shared_ptr<nodelet::Loader> manager_;
  ros::ServiceServer server_;
};

}
}
#endif
