CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(fsiv_opencv)
FIND_PACKAGE(OpenCV 	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

#Esto solo es necesario para Thinstation en la Uco.
link_directories(/usr/local/X11R7/lib)
LINK_LIBRARIES(Xrandr)
#---------------------------------------------


add_executable(calibration_opencv calibration_Opencv.cpp)
add_executable(practica4 practica4.cpp)

#add_executable(pract1 pract1.cc)
#add_executable(pract2 pract2.cc)
#...
