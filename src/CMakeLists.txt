# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (taio C)

# Include sub-projects.
add_subdirectory ("taio_lib")
add_subdirectory ("taio_console")
add_subdirectory ("taio_gui")

