# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/i62fujua/Desktop/fsiv/Práctica6_P1/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/i62fujua/Desktop/fsiv/Práctica6_P1/src

# Include any dependencies generated for this target.
include CMakeFiles/traintest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/traintest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/traintest.dir/flags.make

CMakeFiles/traintest.dir/traintest.cpp.o: CMakeFiles/traintest.dir/flags.make
CMakeFiles/traintest.dir/traintest.cpp.o: traintest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i62fujua/Desktop/fsiv/Práctica6_P1/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/traintest.dir/traintest.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/traintest.dir/traintest.cpp.o -c /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/traintest.cpp

CMakeFiles/traintest.dir/traintest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/traintest.dir/traintest.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/traintest.cpp > CMakeFiles/traintest.dir/traintest.cpp.i

CMakeFiles/traintest.dir/traintest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/traintest.dir/traintest.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/traintest.cpp -o CMakeFiles/traintest.dir/traintest.cpp.s

CMakeFiles/traintest.dir/common_code.cpp.o: CMakeFiles/traintest.dir/flags.make
CMakeFiles/traintest.dir/common_code.cpp.o: common_code.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i62fujua/Desktop/fsiv/Práctica6_P1/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/traintest.dir/common_code.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/traintest.dir/common_code.cpp.o -c /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/common_code.cpp

CMakeFiles/traintest.dir/common_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/traintest.dir/common_code.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/common_code.cpp > CMakeFiles/traintest.dir/common_code.cpp.i

CMakeFiles/traintest.dir/common_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/traintest.dir/common_code.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/common_code.cpp -o CMakeFiles/traintest.dir/common_code.cpp.s

CMakeFiles/traintest.dir/lbp.cpp.o: CMakeFiles/traintest.dir/flags.make
CMakeFiles/traintest.dir/lbp.cpp.o: lbp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i62fujua/Desktop/fsiv/Práctica6_P1/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/traintest.dir/lbp.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/traintest.dir/lbp.cpp.o -c /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/lbp.cpp

CMakeFiles/traintest.dir/lbp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/traintest.dir/lbp.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/lbp.cpp > CMakeFiles/traintest.dir/lbp.cpp.i

CMakeFiles/traintest.dir/lbp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/traintest.dir/lbp.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/lbp.cpp -o CMakeFiles/traintest.dir/lbp.cpp.s

# Object files for target traintest
traintest_OBJECTS = \
"CMakeFiles/traintest.dir/traintest.cpp.o" \
"CMakeFiles/traintest.dir/common_code.cpp.o" \
"CMakeFiles/traintest.dir/lbp.cpp.o"

# External object files for target traintest
traintest_EXTERNAL_OBJECTS =

traintest: CMakeFiles/traintest.dir/traintest.cpp.o
traintest: CMakeFiles/traintest.dir/common_code.cpp.o
traintest: CMakeFiles/traintest.dir/lbp.cpp.o
traintest: CMakeFiles/traintest.dir/build.make
traintest: /usr/local/lib/libopencv_stitching.so.3.4.7
traintest: /usr/local/lib/libopencv_superres.so.3.4.7
traintest: /usr/local/lib/libopencv_videostab.so.3.4.7
traintest: /usr/local/lib/libopencv_aruco.so.3.4.7
traintest: /usr/local/lib/libopencv_bgsegm.so.3.4.7
traintest: /usr/local/lib/libopencv_bioinspired.so.3.4.7
traintest: /usr/local/lib/libopencv_ccalib.so.3.4.7
traintest: /usr/local/lib/libopencv_dnn_objdetect.so.3.4.7
traintest: /usr/local/lib/libopencv_dpm.so.3.4.7
traintest: /usr/local/lib/libopencv_face.so.3.4.7
traintest: /usr/local/lib/libopencv_freetype.so.3.4.7
traintest: /usr/local/lib/libopencv_fuzzy.so.3.4.7
traintest: /usr/local/lib/libopencv_hfs.so.3.4.7
traintest: /usr/local/lib/libopencv_img_hash.so.3.4.7
traintest: /usr/local/lib/libopencv_line_descriptor.so.3.4.7
traintest: /usr/local/lib/libopencv_optflow.so.3.4.7
traintest: /usr/local/lib/libopencv_reg.so.3.4.7
traintest: /usr/local/lib/libopencv_rgbd.so.3.4.7
traintest: /usr/local/lib/libopencv_saliency.so.3.4.7
traintest: /usr/local/lib/libopencv_stereo.so.3.4.7
traintest: /usr/local/lib/libopencv_structured_light.so.3.4.7
traintest: /usr/local/lib/libopencv_surface_matching.so.3.4.7
traintest: /usr/local/lib/libopencv_tracking.so.3.4.7
traintest: /usr/local/lib/libopencv_xfeatures2d.so.3.4.7
traintest: /usr/local/lib/libopencv_ximgproc.so.3.4.7
traintest: /usr/local/lib/libopencv_xobjdetect.so.3.4.7
traintest: /usr/local/lib/libopencv_xphoto.so.3.4.7
traintest: /usr/local/lib/libopencv_shape.so.3.4.7
traintest: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.7
traintest: /usr/local/lib/libopencv_video.so.3.4.7
traintest: /usr/local/lib/libopencv_datasets.so.3.4.7
traintest: /usr/local/lib/libopencv_plot.so.3.4.7
traintest: /usr/local/lib/libopencv_text.so.3.4.7
traintest: /usr/local/lib/libopencv_dnn.so.3.4.7
traintest: /usr/local/lib/libopencv_highgui.so.3.4.7
traintest: /usr/local/lib/libopencv_ml.so.3.4.7
traintest: /usr/local/lib/libopencv_videoio.so.3.4.7
traintest: /usr/local/lib/libopencv_imgcodecs.so.3.4.7
traintest: /usr/local/lib/libopencv_objdetect.so.3.4.7
traintest: /usr/local/lib/libopencv_calib3d.so.3.4.7
traintest: /usr/local/lib/libopencv_features2d.so.3.4.7
traintest: /usr/local/lib/libopencv_flann.so.3.4.7
traintest: /usr/local/lib/libopencv_photo.so.3.4.7
traintest: /usr/local/lib/libopencv_imgproc.so.3.4.7
traintest: /usr/local/lib/libopencv_core.so.3.4.7
traintest: CMakeFiles/traintest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/i62fujua/Desktop/fsiv/Práctica6_P1/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable traintest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/traintest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/traintest.dir/build: traintest

.PHONY : CMakeFiles/traintest.dir/build

CMakeFiles/traintest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/traintest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/traintest.dir/clean

CMakeFiles/traintest.dir/depend:
	cd /home/i62fujua/Desktop/fsiv/Práctica6_P1/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/i62fujua/Desktop/fsiv/Práctica6_P1/src /home/i62fujua/Desktop/fsiv/Práctica6_P1/src /home/i62fujua/Desktop/fsiv/Práctica6_P1/src /home/i62fujua/Desktop/fsiv/Práctica6_P1/src /home/i62fujua/Desktop/fsiv/Práctica6_P1/src/CMakeFiles/traintest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/traintest.dir/depend

