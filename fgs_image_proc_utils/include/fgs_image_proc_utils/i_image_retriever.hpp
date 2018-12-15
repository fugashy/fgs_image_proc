#ifndef FGS_IMAGE_PROC_UTILS_RETRIEVER_HPP_
#define FGS_IMAGE_PROC_UTILS_RETRIEVER_HPP_
#include <opencv2/core/core.hpp>

namespace fgs {
namespace image_proc_utils {

class Retriever {
 public:
  virtual cv::Mat GetImage() = 0;
};
}
}
#endif
