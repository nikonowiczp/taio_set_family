# Set the project name
project (common)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/TaioSetFamily.c)

add_library(lib::common ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)