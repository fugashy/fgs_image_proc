#ifndef FGS_IMAGE_PROC_NODE_SUBSCRIBER_HPP_
#define FGS_IMAGE_PROC_NODE_SUBSCRIBER_HPP_
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <boost/thread.hpp>

#include "fgs_image_proc_utils/retriever.hpp"

namespace {
const char* const kTopicName = "topic_name";
const char* const kQueueLength = "queue_length";
}

namespace fgs {
namespace image_proc_node {

class Subscriber : public image_proc_utils::Retriever {
 public:
  Subscriber(int queue_length);

  virtual cv::Mat GetImage() {
    boost::lock_guard<boost::mutex> lock(mutex_);
      cv::Mat out = image_.clone();
      image_ = cv::Mat()
      return out;
    }
  }

 private:
  void Callback(const sensor_msgs::ImageConstPtr& msg);

  ros::Subscriber subscriber_;
  boost::mutex mutex_;
  cv::Mat image_;
};

}
}
#endif
