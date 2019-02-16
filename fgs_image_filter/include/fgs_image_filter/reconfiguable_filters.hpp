#include "fgs_image_filter/i_filter.hpp"

#include <mutex>

#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>

#include <fgs_image_filter/BilateralConfig.h>
#include <fgs_image_filter/CannyEdgeConfig.h>
#include <fgs_image_filter/GammaCorrectionConfig.h>
#include <fgs_image_filter/GaussianConfig.h>

using fgs_image_filter::BilateralConfig;
using fgs_image_filter::CannyEdgeConfig;
using fgs_image_filter::GammaCorrectionConfig;
using fgs_image_filter::GaussianConfig;

namespace fgs {
namespace image_filter {

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

class GammaCorrection : public Interface {
 public:
  explicit GammaCorrection(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);

 private:
  void ReconfigureCallback(GammaCorrectionConfig& config, uint32_t level);

  std::shared_ptr<dynamic_reconfigure::Server<GammaCorrectionConfig>> server_;
  GammaCorrectionConfig config_;
  std::mutex mutex_;
  cv::Mat lut_;
};

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

class PassThrough : public Interface {
 public:
  explicit PassThrough(ros::NodeHandle& nh);
  virtual void Through(const cv::Mat& in, cv::Mat& out);
};

}
}
