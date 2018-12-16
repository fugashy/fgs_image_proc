cmake_minimum_required(VERSION 2.8.3)
project(fgs_image_proc_node)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  fgs_image_filter
  fgs_image_proc_utils
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp fgs_image_filter fgs_image_proc_utils
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/subscriber.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(${PROJECT_NAME}_simple_node
  src/${PROJECT_NAME}/simple_node.cpp)
target_link_libraries(${PROJECT_NAME}_simple_node
  ${PROJECT_NAME}
)

add_executable(${PROJECT_NAME}_filter_node
  src/${PROJECT_NAME}/filter_node.cpp)
target_link_libraries(${PROJECT_NAME}_filter_node
  ${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME}_simple_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
