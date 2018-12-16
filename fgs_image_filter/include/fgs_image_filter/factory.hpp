#ifndef FGS_IMAGE_FILTER_FACTORY_HPP_
#define FGS_IMAGE_FILTER_FACTORY_HPP_
#include "fgs_image_filter/i_filter.hpp"

namespace fgs {
namespace image_filter {

class Factory {
 public:
  static Interface::Ptr Create(ros::NodeHandle& nh);
};

}
}
#endif
