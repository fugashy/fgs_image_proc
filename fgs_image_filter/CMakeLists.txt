cmake_minimum_required(VERSION 2.8.3)
project(fgs_image_filter)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  fgs_image_proc_utils
  image_transport
  message_generation
  nodelet
  std_msgs
)

generate_dynamic_reconfigure_options(
  config/Bilateral.cfg
  config/CannyEdge.cfg
  config/GammaCorrection.cfg
  config/Gaussian.cfg
)

add_service_files(
  DIRECTORY
    srv
  FILES
    ChangeChainNum.srv
    FilterType.srv)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    dynamic_reconfigure
    fgs_image_proc_utils
    image_transport
    message_runtime
    nodelet
    std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/bilateral.cpp
  src/${PROJECT_NAME}/canny_edge.cpp
  src/${PROJECT_NAME}/factory.cpp
  src/${PROJECT_NAME}/gamma_correction.cpp
  src/${PROJECT_NAME}/gaussian.cpp
  src/${PROJECT_NAME}/pass_through.cpp
  src/${PROJECT_NAME}/dynamic_changable_filter.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})

add_library(${PROJECT_NAME}_nodelet
  src/${PROJECT_NAME}/nodelet.cpp)
target_link_libraries(${PROJECT_NAME}_nodelet
  ${PROJECT_NAME}
)

add_library(${PROJECT_NAME}_chain
  src/${PROJECT_NAME}/chain.cpp)
target_link_libraries(${PROJECT_NAME}_chain
  ${catkin_LIBRARIES}
)

add_executable(${PROJECT_NAME}_chain_node
  src/${PROJECT_NAME}/chain_node.cpp)
target_link_libraries(${PROJECT_NAME}_chain_node
  ${PROJECT_NAME}_chain
)

install(TARGETS
    ${PROJECT_NAME}
    ${PROJECT_NAME}_nodelet
    ${PROJECT_NAME}_chain
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
