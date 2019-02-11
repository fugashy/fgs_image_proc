#ifndef FGS_IMAGE_PROC_DYNAMIC_CHANGABLE_FILTER_HPP_
#define FGS_IMAGE_PROC_DYNAMIC_CHANGABLE_FILTER_HPP_
#include <ros/ros.h>
#include <fgs_image_filter/FilterType.h>

#include "fgs_image_filter/i_filter.hpp"

namespace fgs {
namespace image_filter {

class DynamicChangableFilter {
 public:
  typedef std::shared_ptr<DynamicChangableFilter> Ptr;
  explicit DynamicChangableFilter(ros::NodeHandle& nh);
  void Through(const cv::Mat& in, cv::Mat& out);

 private:
  bool ChangeFilterType(fgs_image_filter::FilterType::Request& req,
                        fgs_image_filter::FilterType::Response& res);

  ros::NodeHandle nh_;
  Interface::Ptr filter_;
  ros::ServiceServer server_;
};
}
}
#endif
