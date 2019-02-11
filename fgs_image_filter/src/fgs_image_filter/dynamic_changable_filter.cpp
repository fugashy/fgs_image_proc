#include "fgs_image_filter/dynamic_changable_filter.hpp"

#include "fgs_image_filter/factory.hpp"

namespace fgs {
namespace image_filter {

DynamicChangableFilter::DynamicChangableFilter(ros::NodeHandle& nh)
  : nh_(nh) {
  server_ = nh.advertiseService(
      "change_filter", &DynamicChangableFilter::ChangeFilterType, this);
  filter_ = Factory::Create(nh_);
}

void DynamicChangableFilter::Through(const cv::Mat& in, cv::Mat& out) {
  filter_->Through(in, out);
}

bool DynamicChangableFilter::ChangeFilterType(
    fgs_image_filter::FilterType::Request& req,
    fgs_image_filter::FilterType::Response& res) {
  try {
    const std::string param_name = nh_.getNamespace() + "/type";
    ros::param::set(param_name, req.filter_type);
    filter_ = Factory::Create(nh_);
  } catch (const std::exception& e) {
    ROS_WARN("%s", e.what());
    return false;
  }

  return true;
}

}
}
