#include "fgs_image_filter/i_filter.hpp"

#include <mutex>

#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>

#include <fgs_image_filter/GaussianConfig.h>
#include <fgs_image_filter/BilateralConfig.h>
#include <fgs_image_filter/CannyEdgeConfig.h>

using fgs_image_filter::GaussianConfig;
using fgs_image_filter::BilateralConfig;
using fgs_image_filter::CannyEdgeConfig;

namespace fgs {
namespace image_filter {

class Gaussian : public Interface {
 public:
  explicit Gaussian(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);

 private:
  void ReconfigureCallback(GaussianConfig& config, uint32_t level);

  std::shared_ptr<dynamic_reconfigure::Server<GaussianConfig>> server_;
  GaussianConfig config_;
  std::mutex mutex_;
};

class Bilateral : public Interface {
 public:
  explicit Bilateral(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);

 private:
  void ReconfigureCallback(BilateralConfig& config, uint32_t level);

  std::shared_ptr<dynamic_reconfigure::Server<BilateralConfig>> server_;
  BilateralConfig config_;
  std::mutex mutex_;
};

class CannyEdge : public Interface {
 public:
  explicit CannyEdge(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);

 private:
  void ReconfigureCallback(CannyEdgeConfig& config, uint32_t level);

  std::shared_ptr<dynamic_reconfigure::Server<CannyEdgeConfig>> server_;
  CannyEdgeConfig config_;
  std::mutex mutex_;
};

}
}
