cmake_minimum_required(VERSION 3.0.0)
project(lab07 VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(
    tasksLibrary
    headers/image_stiching.hpp
    src/image_stiching.cpp
)
target_include_directories(tasksLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers")

add_library(
    panoramic_utils
    headers/panoramic_utils.hpp
    src/panoramic_utils.cpp
)
target_include_directories(panoramic_utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers")

add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
