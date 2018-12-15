#include "fgs_image_proc_node/subscriber.hpp"

#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>

namespace fgs {
namespace image_proc_node {

Subscriber::Subscriber(int queue_length) {
  ros::NodeHandle node_handle("");
  subscriber_ = node_handle.subscribe(
      "image_raw", queue_length, &Subscriber::Callback, this);
}

void Subscriber::Callback(const sensor_msgs::ImageConstPtr& msg) {
  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  } catch (cv_bridge::Exception& e) {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  } 
  boost::lock_guard<boost::mutex> lock(mutex_);
  image_ = cv_ptr->image;
}

cv::Mat Subscriber::GetImage() {
  boost::lock_guard<boost::mutex> lock(mutex_);
  cv::Mat out = image_.clone();
  image_ = cv::Mat();
  return out;
}

}
}
