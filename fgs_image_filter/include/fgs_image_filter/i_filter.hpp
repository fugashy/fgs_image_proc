#ifndef FGS_IMAGE_FILTER_I_FILTER_HPP_
#define FGS_IMAGE_FILTER_I_FILTER_HPP_
#include <memory>

#include <opencv2/core/core.hpp>
#include <ros/ros.h>

namespace fgs {
namespace image_filter {

class Interface {
 public:
  typedef std::shared_ptr<Interface> Ptr;
  virtual void Through(const cv::Mat& in, cv::Mat& out) = 0;
};
}
}
#endif

