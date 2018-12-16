#include "fgs_image_filter/reconfiguable_filters.hpp"

#include <opencv2/imgproc.hpp>

namespace fgs {
namespace image_filter {

Bilateral::Bilateral(ros::NodeHandle& nh) {
  server_.reset(new dynamic_reconfigure::Server<BilateralConfig>(
        ros::NodeHandle(nh, "bilateral")));
  dynamic_reconfigure::Server<BilateralConfig>::CallbackType f = boost::bind(
      &Bilateral::ReconfigureCallback, this, _1, _2);
  server_->setCallback(f);
}

void Bilateral::Through(const cv::Mat& in, cv::Mat& out) {
  std::lock_guard<std::mutex> lock(mutex_);
  cv::bilateralFilter(in, out, config_.sigma_color, config_.sigma_space, config_.border_type);
}

void Bilateral::ReconfigureCallback(BilateralConfig& config, uint32_t level) {
  std::lock_guard<std::mutex> lock(mutex_);
  config_ = config;
}

}
}
