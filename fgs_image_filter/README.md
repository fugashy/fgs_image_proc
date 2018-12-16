# fgs_image_filter

Provide reconfiguable filter library.
Reconfigulation function is powered by ROS dynamic reconfigure class

<http://wiki.ros.org/dynamic_reconfigure>

# Filters

| name | link |
| ---- | ---- |
| gaussian | <https://en.wikipedia.org/wiki/Gaussian_filter> |
| bilateral | <https://en.wikipedia.org/wiki/Bilateral_filter> |

# How to use

  Put following code in your node.

  ```cpp
  #include "fgs_image_filter/factory.hpp"
  .
  .
  .
  // ex) rosparam set /your_node/filter/type gaussian
  FilterPtr filter = fgs::image_filter::Factory::Create(private_nh);
  .
  .
  .
  filter->Through(original_image, filtered_image);
  ```
