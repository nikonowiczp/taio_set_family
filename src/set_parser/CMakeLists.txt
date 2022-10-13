# Set the project name
project (set_parser)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/SetParser.cpp)
add_library(lib::set_parser ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)