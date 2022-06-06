cmake_minimum_required(VERSION 3.1)
project(insert_planner)
# set(ENABLE_TEST true)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# include cmake files in the 'cmake folder'
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(Eigen3 REQUIRED)
#find_package(fcl REQUIRED)
include(./cmake/FindFlann.cmake)

include_directories(
        include
        ${EIGEN3_INCLUDE_DIR}
        #${VTK_INCLUDE_DIRS}
)

#message(${VTK_INCLUDE_DIRS})

add_executable(insert_planner src/main.cpp)

target_link_libraries(insert_planner flann ${VTK_LIBRARIES})


if(ENABLE_TEST)
    add_executable(is_test test/insert_state_test.cpp)
    target_link_libraries(is_test gtest pthread flann)
ENDIF()
