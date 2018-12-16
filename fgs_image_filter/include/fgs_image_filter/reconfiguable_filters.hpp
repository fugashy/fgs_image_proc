#include "fgs_image_filter/i_filter.hpp"

#include <mutex>

#include <ros/ros.h>

#include <fgs_image_filter/GaussianConfig.h>

using fgs_image_filter::GaussianConfig;

namespace fgs {
namespace image_filter {

class Gaussian : public Interface {
 public:
  explicit Gaussian(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);

 private:
  void ReconfigureCallback(GaussianConfig&, uint32_t level);

  std::shared_ptr<dynamic_reconfigure::Server<GaussianConfig>> server_;
  GaussianConfig config_;
  std::mutex mutex_;
};

}
}
