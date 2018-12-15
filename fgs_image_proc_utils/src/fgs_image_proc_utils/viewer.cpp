#include "fgs_image_proc_utils/viewer.hpp"

#include <opencv2/highgui/highgui.hpp>

namespace fgs {
namespace image_proc_utils {

Viewer::Viewer(const std::string& window_name)
  : window_name_(window_name) {
  cv::namedWindow(window_name.c_str());
}

Viewer::~Viewer() {
  cv::destroyWindow(window_name_.c_str());
}

void Viewer::Update(const cv::Mat& image) {
  cv::imshow(window_name_.c_str(), image);
  cv::waitKey(1);
}

}
}
