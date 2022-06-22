cmake_minimum_required(VERSION 3.0.0)
project(bilateralTuning VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(
    tasksLibrary
    headers/tunableBilateral.hpp
    src/tunableBilateral.cpp
)
target_include_directories(tasksLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers")

add_executable(bilTune src/main.cpp)
target_link_libraries(bilTune ${OpenCV_LIBS} tasksLibrary)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
