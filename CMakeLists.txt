cmake_minimum_required(VERSION 3.10)
# set the project name
project(project C CXX)

add_subdirectory(include/json)

add_executable(project main.cpp)

target_link_libraries(project PUBLIC json)

target_include_directories(project PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include/json"
                          )

# add the executable
