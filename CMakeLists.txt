cmake_minimum_required(VERSION 3.15)

project(DocumentScanner)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRECTORIES}
        ${Boost_INCLUDE_DIRS}
        DocumentScanner.h
        DSUtilities.h
        CVPointMover.h)

add_executable(documentScanner main.cpp
        DocumentScanner.cpp
        DSUtilities.cpp
        CVPointMover.cpp)
target_link_libraries(documentScanner
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES})

add_executable(testPointMover testPointMover.cpp
        CVPointMover.cpp
        DSUtilities.cpp)
target_link_libraries(testPointMover ${OpenCV_LIBS})
