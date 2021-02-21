cmake_minimum_required(VERSION 3.5)
project(shutdown_node)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

#------------------------------------------------

include_directories(shutdown_node
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(shutdown_node
  src/shutdown_node.cpp
)
ament_target_dependencies(shutdown_node
  rclcpp
  std_msgs
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  shutdown_node
  DESTINATION lib/${PROJECT_NAME}
)
#--------------------------------------------------
ament_package()