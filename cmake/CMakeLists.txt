# CMakeList.txt : CMake project for CMakeProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject")

add_library(myLibrary SHARED)

target_include_directories(myLibrary PUBLIC ./MyLibrary/)
target_sources(myLibrary PRIVATE MyLibrary/myLibrary.cpp)

# Add source to this project's executable.
add_executable (CMakeProject "CMakeProject.cpp")

target_link_libraries(CMakeProject myLibrary)

# TODO: Add tests and install targets if needed.
