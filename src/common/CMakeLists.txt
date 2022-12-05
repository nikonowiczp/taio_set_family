# Set the project name
project (common)

# Add a library with the above sources
add_library(${PROJECT_NAME} 
    src/TaioSet.c
    src/TaioSetFamily.c
    src/TaioData.c
    src/TaioHashMap.c
    src/TaioSetList)

add_library(lib::common ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} HashMap::HashMap)
