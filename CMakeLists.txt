cmake_minimum_required(VERSION 3.10)
# set the project name
project(project C CXX)

add_subdirectory(include/json)
add_subdirectory(include/httplib)


add_executable(project main.cpp UMLParameter.cpp)

# add executables here
add_executable(project main.cpp)


# add threads for http library
find_package (Threads REQUIRED)

target_link_libraries(project PUBLIC Threads::Threads)

target_link_libraries(project PUBLIC json)

target_link_libraries(project PUBLIC http)



target_include_directories(project PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include/json"
                          "${PROJECT_SOURCE_DIR}/include/http"
                          )

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests Tests.cpp UMLParameter.cpp)
target_link_libraries(Tests gtest_main)
include(GoogleTest)
gtest_discover_tests(Tests)
