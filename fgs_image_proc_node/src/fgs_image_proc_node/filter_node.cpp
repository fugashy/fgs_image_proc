#include "fgs_image_proc_node/subscriber.hpp"
#include "fgs_image_proc_utils/viewer.hpp"
#include "fgs_image_filter/factory.hpp"

using fgs::image_proc_node::Subscriber;
using fgs::image_proc_utils::Viewer;
typedef fgs::image_filter::Interface::Ptr FilterPtr;

int main(int argc, char** argv) {
  ros::init(argc, argv, "filter_node");
  ros::NodeHandle private_nh("~");

  std::shared_ptr<Subscriber> sub;
  std::shared_ptr<Viewer> viewer_origin;
  std::shared_ptr<Viewer> viewer_filtered;
  FilterPtr filter;

  try {
    sub.reset(new Subscriber(1));
    viewer_origin.reset(new Viewer("original_image"));
    viewer_filtered.reset(new Viewer("filtered_image"));
    filter = fgs::image_filter::Factory::Create(private_nh);

    ros::Rate rate(20);
    while (private_nh.ok()) {
      cv::Mat image = sub->GetImage();

      if (!image.empty()) {
        cv::Mat filtered_image;
        filter->Through(image, filtered_image);
        viewer_origin->Update(image);
        viewer_filtered->Update(filtered_image);
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
