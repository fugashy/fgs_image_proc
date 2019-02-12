#ifndef FGS_IMAGE_FILTER_NODELET_HPP_
#define FGS_IMAGE_FILTER_NODELET_HPP_
#include <image_transport/image_transport.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include <sensor_msgs/Image.h>

#include "fgs_image_filter/dynamic_changable_filter.hpp"

namespace fgs {
namespace image_filter {

class Nodelet : public nodelet::Nodelet {
 public:
  virtual void onInit();

 private:
  void Callback(const sensor_msgs::ImageConstPtr& msg);

  DynamicChangableFilter::Ptr filter_;

  image_transport::Subscriber sub_;
  image_transport::Publisher pub_;
};

}
}

PLUGINLIB_EXPORT_CLASS(fgs::image_filter::Nodelet, nodelet::Nodelet)
#endif
