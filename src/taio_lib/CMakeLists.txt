# CMakeList.txt : CMake project for taio_lib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8 )

# Add source to this project's executable.
project(taio_lib C)
set(PROJECT_SOURCES
    "TaioSet.c"
    "TaioData.c"
    "TaioSetFamily.c"
    "TaioSetList.c"
    "SetParser.c"
    "hashmap.c"
    "TaioHashMap.c"
    "TaioAlgorithms.c"
    "SetRunner.c")
set(PROJECT_HEADERS
    "TaioSet.h"
    "TaioData.h"
    "TaioSetFamily.h"
    "TaioSetList.h"
    "SetParser.h"
    "hashmap.h"
    "TaioHashMap.h"
    "TaioAlgorithms.h"
    "SetRunner.h")
add_library (taio_lib STATIC ${PROJECT_HEADERS} ${PROJECT_SOURCES})
add_library(lib::taio_lib ALIAS taio_lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET taio_lib PROPERTY CXX_STANDARD 20)
endif()

target_include_directories( taio_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
