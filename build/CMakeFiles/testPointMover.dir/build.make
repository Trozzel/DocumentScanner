# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build

# Include any dependencies generated for this target.
include CMakeFiles/testPointMover.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/testPointMover.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testPointMover.dir/flags.make

CMakeFiles/testPointMover.dir/testPointMover.cpp.o: CMakeFiles/testPointMover.dir/flags.make
CMakeFiles/testPointMover.dir/testPointMover.cpp.o: ../testPointMover.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testPointMover.dir/testPointMover.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testPointMover.dir/testPointMover.cpp.o -c /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/testPointMover.cpp

CMakeFiles/testPointMover.dir/testPointMover.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testPointMover.dir/testPointMover.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/testPointMover.cpp > CMakeFiles/testPointMover.dir/testPointMover.cpp.i

CMakeFiles/testPointMover.dir/testPointMover.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testPointMover.dir/testPointMover.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/testPointMover.cpp -o CMakeFiles/testPointMover.dir/testPointMover.cpp.s

CMakeFiles/testPointMover.dir/CVPointMover.cpp.o: CMakeFiles/testPointMover.dir/flags.make
CMakeFiles/testPointMover.dir/CVPointMover.cpp.o: ../CVPointMover.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testPointMover.dir/CVPointMover.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testPointMover.dir/CVPointMover.cpp.o -c /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/CVPointMover.cpp

CMakeFiles/testPointMover.dir/CVPointMover.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testPointMover.dir/CVPointMover.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/CVPointMover.cpp > CMakeFiles/testPointMover.dir/CVPointMover.cpp.i

CMakeFiles/testPointMover.dir/CVPointMover.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testPointMover.dir/CVPointMover.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/CVPointMover.cpp -o CMakeFiles/testPointMover.dir/CVPointMover.cpp.s

CMakeFiles/testPointMover.dir/DSUtilities.cpp.o: CMakeFiles/testPointMover.dir/flags.make
CMakeFiles/testPointMover.dir/DSUtilities.cpp.o: ../DSUtilities.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/testPointMover.dir/DSUtilities.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testPointMover.dir/DSUtilities.cpp.o -c /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/DSUtilities.cpp

CMakeFiles/testPointMover.dir/DSUtilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testPointMover.dir/DSUtilities.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/DSUtilities.cpp > CMakeFiles/testPointMover.dir/DSUtilities.cpp.i

CMakeFiles/testPointMover.dir/DSUtilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testPointMover.dir/DSUtilities.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/DSUtilities.cpp -o CMakeFiles/testPointMover.dir/DSUtilities.cpp.s

# Object files for target testPointMover
testPointMover_OBJECTS = \
"CMakeFiles/testPointMover.dir/testPointMover.cpp.o" \
"CMakeFiles/testPointMover.dir/CVPointMover.cpp.o" \
"CMakeFiles/testPointMover.dir/DSUtilities.cpp.o"

# External object files for target testPointMover
testPointMover_EXTERNAL_OBJECTS =

testPointMover: CMakeFiles/testPointMover.dir/testPointMover.cpp.o
testPointMover: CMakeFiles/testPointMover.dir/CVPointMover.cpp.o
testPointMover: CMakeFiles/testPointMover.dir/DSUtilities.cpp.o
testPointMover: CMakeFiles/testPointMover.dir/build.make
testPointMover: /usr/local/lib/libopencv_gapi.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_stitching.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_alphamat.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_aruco.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_bgsegm.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_bioinspired.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_ccalib.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_dnn_objdetect.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_dnn_superres.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_dpm.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_face.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_freetype.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_fuzzy.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_hfs.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_img_hash.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_intensity_transform.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_line_descriptor.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_mcc.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_quality.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_rapid.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_reg.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_rgbd.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_saliency.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_sfm.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_stereo.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_structured_light.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_superres.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_surface_matching.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_tracking.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_videostab.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_viz.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_wechat_qrcode.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_xfeatures2d.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_xobjdetect.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_xphoto.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_shape.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_highgui.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_datasets.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_plot.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_text.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_ml.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_phase_unwrapping.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_optflow.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_ximgproc.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_video.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_videoio.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_dnn.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_imgcodecs.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_objdetect.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_calib3d.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_features2d.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_flann.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_photo.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_imgproc.4.5.2.dylib
testPointMover: /usr/local/lib/libopencv_core.4.5.2.dylib
testPointMover: CMakeFiles/testPointMover.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable testPointMover"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testPointMover.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testPointMover.dir/build: testPointMover
.PHONY : CMakeFiles/testPointMover.dir/build

CMakeFiles/testPointMover.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testPointMover.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testPointMover.dir/clean

CMakeFiles/testPointMover.dir/depend:
	cd /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build /Users/jorge/Cpp/Learning/OpenCVCourse/DocumentScannerProject/build/CMakeFiles/testPointMover.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testPointMover.dir/depend

