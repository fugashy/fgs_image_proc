#ifndef FGS_IMAGE_FILTER_I_FILTER_HPP_
#define FGS_IMAGE_FILTER_I_FILTER_HPP_
#include <dynamic_reconfigure/server.h>
#include <opencv2/core/core.hpp>

namespace fgs {
namespace image_filter {

class Interface {
 public:
  virtual void Through(const cv::Mat& in, cv::Mat& out) = 0;
};
}
}
#endif

