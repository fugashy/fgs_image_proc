#include "fgs_image_filter/i_filter.hpp"

#include <mutex>

#include <ros/ros.h>

#include <fgs_image_filter/GaussianConfig.h>
#include <fgs_image_filter/BilateralConfig.h>

using fgs_image_filter::GaussianConfig;
using fgs_image_filter::BilateralConfig;

namespace fgs {
namespace image_filter {

class Gaussian : public Interface {
 public:
  explicit Gaussian(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);

 private:
  void ReconfigureCallback(GaussianConfig& config, uint32_t level);

  std::shared_ptr<dynamic_reconfigure::Server<GaussianConfig>> server_;
  GaussianConfig config_;
  std::mutex mutex_;
};

class Bilateral : public Interface {
 public:
  explicit Bilateral(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);

 private:
  void ReconfigureCallback(BilateralConfig& config, uint32_t level);

  std::shared_ptr<dynamic_reconfigure::Server<BilateralConfig>> server_;
  BilateralConfig config_;
  std::mutex mutex_;
};

}
}
