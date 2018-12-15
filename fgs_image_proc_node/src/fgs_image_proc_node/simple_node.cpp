#include "fgs_image_proc_node/subscriber.hpp"
#include "fgs_image_proc_utils/viewer.hpp"

using fgs::image_proc_node::Subscriber;
using fgs::image_proc_utils::Viewer;

int main(int argc, char** argv) {
  ros::init(argc, argv, "simple_node");
  ros::NodeHandle private_nh("~");

  std::shared_ptr<Subscriber> sub;
  std::shared_ptr<Viewer> viewer;

  try {
    sub.reset(new Subscriber(1));
    viewer.reset(new Viewer("simple_node_image");

    ros::Rate rate(5);
    while (private_nh.ok()) {
      cv::Mat image = subscriber.GetImage();

      if (image) {
        viewer.Update(image);
      }

      ros::spinOnce();
      rate.sleep();
    }
  } catch (const std::exception& e) {
    ROS_FATAL("%s", e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
