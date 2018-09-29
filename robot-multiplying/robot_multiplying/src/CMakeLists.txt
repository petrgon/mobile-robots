include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

# This will create executables of the nodes
    add_executable(multiplying_publisher src/multiplying_publisher.cpp)  
    add_executable(multiplying_subscriber src/multiplying_subscriber.cpp)    

# This will generate message header file before building the target
    add_dependencies(multiplying_publisher
        mastering_ros_demo_pkg_generate_message_cpp)  
    add_dependencies(multiplying_subscriber
        mastering_ros_demo_pkg_generate_message_cpp)

# This will link executables to the appropriate libraries
    target_link_libraries(multiplying_publisher ${catkin_LIBRARIES})
    target_link_libraries(multiplying_subscriber ${catkin_LIBRARIES})