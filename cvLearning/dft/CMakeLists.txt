cmake_minimum_required(VERSION 2.8)
project(test CXX)
find_package(OpenCV REQUIRED)

add_executable(test main.cpp)
SET_TARGET_PROPERTIES(test PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(test ${OpenCV_LIBS})
