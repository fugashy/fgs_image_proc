#ifndef IMAGE_PROCESS_FILTER_GAUSSIAN_HPP_
#define IMAGE_PROCESS_FILTER_GAUSSIAN_HPP_
#include "fgs_image_filter/reconfiguable_filters.hpp"

#include <opencv2/imgproc.hpp>

namespace fgs {
namespace image_filter {

Gaussian::Gaussian(ros::NodeHandle& nh) {
  config_.kernel_x = 10;
  config_.kernel_y = 10;
  config_.sigma_x = 1.0;
  config_.sigma_y = 1.0;
  config_.border_type = cv::BORDER_DEFAULT;
}

void Gaussian::Through(const cv::Mat& input, cv::Mat& output) {
  std::lock_guard<std::mutex> lock(mutex_);
  const cv::Size kernel(config_.kernel_x, config_.kernel_y);
  cv::GaussianBlur(
      input, output, kernel, config_.sigma_x, config_.sigma_y, config_.border_type);
}

void Gaussian::ReconfigureCallback(GaussianConfig& config, uint32_t level) {
  std::lock_guard<std::mutex> lock(mutex_);
  config_ = config;
}

}
}
#endif
