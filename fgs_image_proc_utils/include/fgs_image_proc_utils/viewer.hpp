#ifndef FGS_IMAGE_PROC_UTILS_VIEWER_HPP_
#define FGS_IMAGE_PROC_UTILS_VIEWER_HPP_
#include <opencv2/core/core.hpp>

namespace fgs {
namespace image_proc_utils {
class Viewer {
 public:
  explicit Viewer(const std::string& window_name);
  ~Viewer();
  void Update(const cv::Mat& image);

 private:
  std::string window_name_;
};
}
}
#endif
