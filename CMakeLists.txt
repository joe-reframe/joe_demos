cmake_minimum_required(VERSION 3.8)
project(nesting_callbacks_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(client_node src/client_in_timer.cpp)
ament_target_dependencies(client_node PUBLIC example_interfaces rclcpp)

install(
  TARGETS client_node
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}/
  INCLUDES DESTINATION include
)

ament_package()
