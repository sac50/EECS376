cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#access to phidgets library


#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
rosbuild_add_library(Helper src/Path.cpp)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
rosbuild_add_executable(masterController src/masterController.cpp)
rosbuild_add_executable(velocity src/velocity.cpp)
rosbuild_add_executable(obstacle src/obstacle.cpp)
rosbuild_add_executable(steering src/steering.cpp)
rosbuild_add_executable(estop src/estop.cpp)
rosbuild_add_executable(paths src/pathsegPublisher_temp.cpp)
rosbuild_add_executable(replan src/replan.cpp)
#rosbuild_add_executable(image_cloud_sub src/image_cloud_sub.cpp)
#rosbuild_add_executable(image_cloud_sub2 src/image_cloud_sub2.cpp)
#rosbuild_add_executable(calibration src/image_cloud_sub_k.cpp)
rosbuild_add_executable(obstacleZone src/obstacle_zone.cpp)
rosbuild_add_executable(goal_zone src/goal_zone.cpp)
#rosbuild_add_executable(costmap src/costmap.cpp)
rosbuild_add_executable(goals src/goal_publisher.cpp)
#rosbuild_add_executable(x src/image_cloud_sub_x.cpp)
#rosbuild_add_executable(k src/image_cloud_sub_k.cpp)
#rosbuild_add_executable(k src/image_cloud_sub_steve2.cpp)

target_link_libraries(steering Helper)
target_link_libraries(velocity Helper)
target_link_libraries(paths Helper)
target_link_libraries(masterController Helper)
target_link_libraries(replan Helper)
#target_link_libraries(example ${PROJECT_NAME})
