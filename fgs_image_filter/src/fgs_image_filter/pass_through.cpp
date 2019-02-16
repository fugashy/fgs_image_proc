#include "fgs_image_filter/reconfiguable_filters.hpp"


namespace fgs {
namespace image_filter {

PassThrough::PassThrough(ros::NodeHandle& nh) {}

void PassThrough::Through(const cv::Mat& in, cv::Mat& out) {
  out = in;
}

}
}
