#include "fgs_image_filter/factory.hpp"

#include <ros/ros.h>

#include "fgs_image_filter/reconfiguable_filters.hpp"


namespace fgs {
namespace image_filter {

Interface::Ptr Factory::Create(ros::NodeHandle& nh) {
  std::string type;
  nh.param<std::string>("filter/type", type, "gaussian");

  Interface::Ptr ptr;
  if (type == "gaussian") {
    ptr.reset(new Gaussian(nh));
  } else if (type == "bilateral") {
    ptr.reset(new Bilateral(nh));
  } else {
    throw std::runtime_error("Invalid filter type.");
  }

  return ptr;
}

}
}
