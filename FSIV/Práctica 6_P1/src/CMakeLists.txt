# FSIV project
cmake_minimum_required (VERSION 3.1)
project (fsivdet)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
find_package(OpenCV 3.4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
LINK_LIBRARIES(${OpenCV_LIBS})

add_executable(traintest traintest.cpp common_code.cpp lbp.cpp)
