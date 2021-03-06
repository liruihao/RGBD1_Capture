########################################
# Ruihao Li, 2015.10
########################################

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT( rgbd_capture )


SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

SET( CMAKE_BUILD_TYPE Release )

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/../include )
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/../lib )

####    PCL    #####
find_package(PCL 1.8 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

####  opencv   #####
FIND_PACKAGE( OpenCV REQUIRED )

set(incs captureImage_generatePointCloud.h  ParameterReader.h)
set(srcs captureImage_generatePointCloud.cpp  ParameterReader.cpp)

ADD_LIBRARY(SLAM_Ruihao SHARED ${incs} ${srcs})
TARGET_LINK_LIBRARIES( SLAM_Ruihao  ${OpenCV_LIBS} ${PCL_LIBRARIES} yaml-cpp )

ADD_EXECUTABLE( Run_openni_test main.cpp )
TARGET_LINK_LIBRARIES( Run_openni_test SLAM_Ruihao )



