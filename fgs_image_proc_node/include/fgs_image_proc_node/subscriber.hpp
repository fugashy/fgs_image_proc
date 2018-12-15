#ifndef FGS_IMAGE_PROC_NODE_SUBSCRIBER_HPP_
#define FGS_IMAGE_PROC_NODE_SUBSCRIBER_HPP_
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <boost/thread.hpp>

#include "fgs_image_proc_utils/i_image_retriever.hpp"

namespace fgs {
namespace image_proc_node {

class Subscriber : public fgs::image_proc_utils::Retriever {
 public:
  explicit Subscriber(int queue_length);

  virtual cv::Mat GetImage();

 private:
  void Callback(const sensor_msgs::ImageConstPtr& msg);

  ros::Subscriber subscriber_;
  boost::mutex mutex_;
  cv::Mat image_;
};

}
}
#endif
