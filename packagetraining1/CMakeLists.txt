cmake_minimum_required(VERSION 3.8)
project(packagetraining1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#Find_Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(cpp_node src/node_training.cpp)
ament_target_dependencies(cpp_node rclcpp)

add_executable(robot_news src/robot_news_station.cpp)
ament_target_dependencies(robot_news rclcpp example_interfaces)

add_executable(radio_reciave src/Radio.cpp)
ament_target_dependencies(radio_reciave rclcpp example_interfaces)

add_executable(Number_Publisher src/Number_Publisher.cpp)
ament_target_dependencies(Number_Publisher rclcpp std_msgs)

add_executable(Number_Subscriber src/Number_Subscriber.cpp)
ament_target_dependencies(Number_Subscriber rclcpp std_msgs example_interfaces) 

add_executable(Reset_Counter src/ResetCounter.cpp)
ament_target_dependencies(Reset_Counter rclcpp example_interfaces)

install(TARGETS
 cpp_node 
 robot_news
 radio_reciave
 Number_Publisher
 Number_Subscriber
 Reset_Counter
 DESTINATION lib/${PROJECT_NAME}
)
ament_package()
