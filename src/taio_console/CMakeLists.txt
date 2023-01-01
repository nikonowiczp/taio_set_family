# CMakeList.txt : CMake project for taio_lib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8 )

# Add source to this project's executable.
project(taio_console C)
set(PROJECT_SOURCES "main.c")
add_executable (taio_console   ${PROJECT_SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET taio_console PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(taio_console lib::taio_lib)
