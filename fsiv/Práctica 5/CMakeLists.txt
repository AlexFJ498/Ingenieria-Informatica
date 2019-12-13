cmake_minimum_required (VERSION 3.0)
project (fsivlbp)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
find_package(OpenCV 3.3 REQUIRED)

LINK_LIBRARIES(${OpenCV_LIBS})
#Esto solo es necesario para Thinstation en la Uco.
link_directories(/usr/local/X11R7/lib)
LINK_LIBRARIES(Xrandr)

add_executable(lbpdesc test_lbp.cpp lbp.cpp)
