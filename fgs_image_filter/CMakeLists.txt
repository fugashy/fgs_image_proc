cmake_minimum_required(VERSION 2.8.3)
project(fgs_image_filter)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  fgs_image_proc_utils
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(
  config/Gaussian.cfg
  config/Bilateral.cfg
  config/CannyEdge.cfg
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS fgs_image_proc_utils dynamic_reconfigure
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/gaussian.cpp
  src/${PROJECT_NAME}/bilateral.cpp
  src/${PROJECT_NAME}/canny_edge.cpp
  src/${PROJECT_NAME}/factory.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
