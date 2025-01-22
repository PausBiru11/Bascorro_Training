cmake_minimum_required(VERSION 3.8)
project(packagetraining2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#Find_Dependencies
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(ament_cmake REQUIRED)

add_executable(Server_Perkalian src/Server.cpp)
ament_target_dependencies(Server_Perkalian rclcpp example_interfaces)

add_executable(Server_Client src/Client.cpp)
ament_target_dependencies(Server_Client rclcpp example_interfaces)

install(TARGETS
 Server_Perkalian
 Server_Client
 DESTINATION lib/${PROJECT_NAME}
)
ament_package()
